#include "data_processing_field.hpp"

#include <bitset>

#include "utility.hpp"

DataProcessingField::DataProcessingField(OpcodeInfo *opcode_info_ptr)
    : Field(opcode_info_ptr), cond(0), op(0), funct(0), rn(0), rd(0), src2(0) {}
DataProcessingField::~DataProcessingField() {}

uint32_t DataProcessingField::get_iflag_1bit(const std::string opcode, const std::string src2) const {
    uint32_t ret = 0;
    auto cmd = opcode_info_ptr->at(opcode).at("cmd");
    if (cmd == 0b1101 and opcode.substr(0, 3) != "mov") {
        ret = 0b0;
    } else {
        ret = (src2[0] == '#') ? 0b1 : 0b0;
    }
    return ret;
}

uint32_t DataProcessingField::get_sflag_1bit(const std::string opcode) const {
    return opcode_info_ptr->at(opcode).at("S");
}

uint32_t DataProcessingField::get_cmd_4bit(const std::string opcode) const {
    return opcode_info_ptr->at(opcode).at("cmd");
}

uint32_t DataProcessingField::get_funct_6bit(const std::string opcode, const std::string src2) const {
    auto iflag = get_iflag_1bit(opcode, src2);
    auto cmd = get_cmd_4bit(opcode);
    auto sflag = get_sflag_1bit(opcode);
    auto funct = sflag | (cmd << 1) | (iflag << 5);
    return funct;
}

uint32_t DataProcessingField::get_shamt5_5bit(const std::string opcode, const std::string src2) const {
    uint32_t ret = 0;
    auto cmd = opcode_info_ptr->at(opcode).at("cmd");
    if (cmd == 0b1101 and src2[0] == '#') {
        ret = std::stoi(src2.substr(1));
    } else {
        ret = 0b00000;
    }
    return ret;
}

uint32_t DataProcessingField::get_sh_2bit(const std::string opcode) const {
    uint32_t ret = 0;
    auto cmd = opcode_info_ptr->at(opcode).at("cmd");
    if (cmd == 0b1101) {
        ret = opcode_info_ptr->at(opcode).at("sh");
    } else {
        ret = 0b00;
    }

    return ret;
}

uint32_t DataProcessingField::get_src2_12bit_imm(const std::string src2) const {
    uint32_t imm32 = 0;
    if (src2.substr(1, 2) == "0x") {
        imm32 = std::stoull(src2.substr(1), nullptr, 16);
    } else {
        imm32 = std::stoul(src2.substr(1));
    }
    return encode_imm32(imm32);
}

uint32_t DataProcessingField::get_src2_12bit_shimm(const std::string opcode,
                                                   const std::vector<std::string> operands) const {
    auto src2 = operands.back();
    auto rm = operands[1];
    uint32_t shamt5 = get_shamt5_5bit(opcode, src2);
    uint32_t sh = get_sh_2bit(opcode);
    uint32_t rm_ = get_reg_4bit(rm);
    return rm_ | (0b0 << 4) | (sh << 5) | (shamt5 << 7);
}

uint32_t DataProcessingField::get_src2_12bit_shreg(const std::string opcode,
                                                   const std::vector<std::string> operands) const {
    auto src2 = operands.back();
    auto rm = operands[1];
    uint32_t rs = get_reg_4bit(src2);
    uint32_t sh = get_sh_2bit(opcode);
    uint32_t rm_ = get_reg_4bit(rm);
    return rm_ | (0b1 << 4) | (sh << 5) | (0b0 << 7) | (rs << 8);
}

uint32_t DataProcessingField::get_src2_12bit_type123(const std::vector<std::string> operands) const {
    uint32_t ret = 0;
    auto src2 = operands.back();
    if (src2[0] == '#') {
        ret = get_src2_12bit_imm(src2);
    } else if (is_register_str(src2)) {
        ret = get_src2_12bit_reg_shift(src2);
    } else {
        throw std::runtime_error("unsupported description.");
    }
    return ret;
}

uint32_t DataProcessingField::get_src2_12bit_type4(const std::string opcode,
                                                   const std::vector<std::string> operands) const {
    uint32_t ret = 0;
    auto src2 = operands.back();
    if (src2[0] == '#') {
        ret = get_src2_12bit_shimm(opcode, operands);
    } else if (is_register_str(src2)) {
        ret = get_src2_12bit_shreg(opcode, operands);
    } else {
        throw std::runtime_error("unsupported description.");
    }
    return ret;
}

uint32_t DataProcessingField::encode_imm32(const uint32_t imm32) const {
    // rot(4bit), imm8(8bit)にエンコードできない数値が入力された場合はエラー
    uint32_t rot4 = 0, imm8 = 0;
    uint32_t mask8 = 0b11111111;

    for (size_t i = 0; i < 16; i++) {
        auto shift_mask8 = rotr(mask8, 2 * i);
        if ((imm32 & shift_mask8) == imm32) {
            rot4 = i;
            imm8 = rotl(imm32, 2 * i);
            return imm8 | (rot4 << 8);
        }
    }

    throw std::runtime_error("cannot encode the immediate.");
}

void DataProcessingField::input(std::vector<std::string> asmcode_v, [[maybe_unused]] int current_line_num) {
    auto opcode = asmcode_v[0];
    std::vector<std::string> operands(asmcode_v.begin() + 1, asmcode_v.end());
    cond = get_cond_4bit(opcode);
    op = get_op_2bit(opcode);

    auto ftype = get_ftype(opcode);
    switch (ftype) {
        case 1:  // Type1: Opcode Rd, Rn, Src2
            funct = get_funct_6bit(opcode, operands[2]);
            rn = get_reg_4bit(operands[1]);
            rd = get_reg_4bit(operands[0]);
            src2 = get_src2_12bit_type123(operands);
            break;
        case 2:  // Type2: Opcode Rn, Src2
            funct = get_funct_6bit(opcode, operands[1]);
            rn = get_reg_4bit(operands[0]);
            rd = 0b0000;
            src2 = get_src2_12bit_type123(operands);
            break;
        case 3:  // Type3: Opcode Rd, Src2
            funct = get_funct_6bit(opcode, operands[1]);
            rn = 0b0000;
            rd = get_reg_4bit(operands[0]);
            src2 = get_src2_12bit_type123(operands);
            break;
        case 4:  // Type4: Opcode Rd, Rm, Rs/shamt5
            funct = get_funct_6bit(opcode, operands[2]);
            rn = 0b0000;
            rd = get_reg_4bit(operands[0]);
            src2 = get_src2_12bit_type4(opcode, operands);
            break;
        default:
            throw std::runtime_error("unsupported format type.");
    }
}

uint32_t DataProcessingField::output() {
    return src2 | (rd << 12) | (rn << 16) | (funct << 20) | (op << 26) | (cond << 28);
}

void DataProcessingField::clear_field() { cond = op = funct = rn = rd = src2 = 0; }

void DataProcessingField::show_field() {
    std::cout << "cond = " << std::bitset<4>(cond) << ", op = " << std::bitset<2>(op)
              << ", funct = " << std::bitset<6>(funct) << ", rn = " << std::bitset<4>(rn)
              << ", rd = " << std::bitset<4>(rd) << ", src2 = " << std::bitset<12>(src2) << std::endl;
}