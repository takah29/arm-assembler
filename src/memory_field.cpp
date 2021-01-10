#include "memory_field.hpp"

#include <bitset>
#include <cmath>
#include <regex>

#include "utility.hpp"

MemoryField::MemoryField(OpcodeInfo *opcode_info)
    : Field(opcode_info), cond(0), op(0), funct(0), rn(0), rd(0), src2(0) {}
MemoryField::~MemoryField() {}

uint32_t MemoryField::get_iflag_1bit(const std::string operand_src2) const {
    uint32_t ret = 0;
    if (operand_src2[0] == '#') {
        ret = 0b1;
    } else if (operand_src2[0] == 'r' or operand_src2[1] == 'r') {
        ret = 0b0;
    } else {
        throw std::runtime_error("unsupported description.");
    }
    return ret;
}

uint32_t MemoryField::get_uflag_1bit(const std::string operand_src2) const {
    uint32_t ret = 0;
    if (operand_src2[0] == '#' or operand_src2[0] == 'r') {  // plus case: src2 = "#<num>" or "r<reg_num>"
        ret = 0b1;
    } else if (operand_src2[0] == '-' or operand_src2[1] == '-') {  // minus case: src2 = "-r<reg_num>" or "#-<num>"
        ret = 0b0;
    } else {
        throw std::runtime_error("unsupported description.");
    }
    return ret;
}

uint32_t MemoryField::get_bflag_1bit(const std::string opcode) const { return opcode_info->at(opcode).at("B"); }

uint32_t MemoryField::get_lflag_1bit(const std::string opcode) const { return opcode_info->at(opcode).at("L"); }

uint32_t MemoryField::get_funct_6bit(const std::string opcode, const std::string adr) const {
    // Get B and L flags
    auto b = get_bflag_1bit(opcode);
    auto l = get_lflag_1bit(opcode);

    // Get p and w flags
    auto pos = adr.find_last_of(']');
    uint32_t p = 0, w = 0;
    if (pos == adr.size() - 1) {  // offset
        p = 0b1;
        w = 0b0;
    } else if (adr[pos + 1] == '!') {  // preindex
        p = 0b1;
        w = 0b1;

    } else if (adr[pos + 1] == ',') {  // postindex
        p = 0b0;
        w = 0b0;
    } else {
        throw std::runtime_error("unsupported description.");
    }

    // Get iber and u flags
    auto adr_operands = adr_to_operands(adr);

    uint32_t iber = 0, u = 0;
    if (adr_operands.size() == 2) {  // case: [rn, +-src2]
        auto operand_src2 = adr_operands[1];
        iber = (~get_iflag_1bit(operand_src2)) & 0x00000001;
        u = get_uflag_1bit(operand_src2);
    } else if (adr_operands.size() == 1 and p == 0b1 and w == 0b0) {  // case: [rn]
        iber = 0b0;
        u = 0b1;
    } else {
        throw std::runtime_error("unsupported description.");
    }

    return l | (w << 1) | (b << 2) | (u << 3) | (p << 4) | (iber << 5);
}

uint32_t MemoryField::get_src2_12bit_imm(const std::string operand_src2) const {
    uint32_t src2 = 0;

    auto to_imm12 = [](std::string operand_src2, int n) {
        uint32_t imm12 = 0;
        if (operand_src2.substr(n, 2) == "0x") {
            imm12 = std::stoull(operand_src2.substr(1), nullptr, 16);
        } else {
            imm12 = std::stoul(operand_src2.substr(1));
        }

        if (imm12 > (std::pow(2, 12) - 1)) {
            throw std::runtime_error("an integer value that cannot be expressed in 12 bits.");
        }
        return imm12;
    };

    if (operand_src2[1] == '-') {  // case sub: src2 = #-<num>
        src2 = to_imm12(operand_src2, 2);
    } else {  // case add: src2 = #<num>
        src2 = to_imm12(operand_src2, 1);
    }

    return src2;
}

uint32_t MemoryField::get_src2_12bit_reg(const std::string operand_src2) const {
    // Shift operator is not supported, so shamt5 and sh fields are 0
    uint32_t src2 = 0;

    if (operand_src2[0] == '-') {  // case sub: src2 = -r<num>
        src2 = get_reg_4bit(operand_src2.substr(1));
    } else {  // case add: src2 = r<num>
        src2 = get_reg_4bit(operand_src2);
    }

    return src2;
};

std::vector<std::string> MemoryField::adr_to_operands(const std::string adr) const {
    auto operands_str = std::regex_replace(adr, std::regex(R"(\[|\]|!)"), "");
    return split_reg(operands_str, ", ");
}

void MemoryField::input(std::vector<std::string> asmcode_v) {
    auto opcode = asmcode_v[0];
    std::vector<std::string> operands(asmcode_v.begin() + 1, asmcode_v.end());
    cond = get_cond_4bit(opcode);
    op = get_op_2bit(opcode);

    auto ftype = get_ftype(opcode);
    if (ftype == 7) {
        if (op == 0b01) {  // Opcode Rd, [Rn, +-Src2]
            funct = get_funct_6bit(opcode, operands.back());
            rn = get_reg_4bit(operands[0]);

            auto adr_operands = adr_to_operands(operands.back());
            rd = get_reg_4bit(adr_operands[0]);

            if (funct >> 5 == 0) {  // immediate
                src2 = (adr_operands.size() == 2) ? get_src2_12bit_imm(adr_operands[1]) : 0b0;
            } else {  // register
                src2 = get_src2_12bit_reg(adr_operands[1]);
            }
        } else if (op == 0b00) {
        } else {
            throw std::runtime_error("unsupported op.");
        }
    } else {
        throw std::runtime_error("unsupported format type.");
    }
}

uint32_t MemoryField::output() { return src2 | (rd << 12) | (rn << 16) | (funct << 20) | (op << 26) | (cond << 28); }

void MemoryField::clear_field() { cond = op = funct = rn = rd = src2 = 0; }

void MemoryField::show_field() {
    std::cout << "cond = " << std::bitset<4>(cond) << ", op = " << std::bitset<2>(op)
              << ", funct = " << std::bitset<6>(funct) << ", rn = " << std::bitset<4>(rn)
              << ", rd = " << std::bitset<4>(rd) << ", src2 = " << std::bitset<12>(src2) << std::endl;
}