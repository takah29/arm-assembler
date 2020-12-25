#include "multiplication_field.hpp"

#include <bitset>

#include "utility.hpp"

MultiplicationField::MultiplicationField(OpcodeInfo *opcode_info)
    : Field(opcode_info), cond(0), op(0), funct(0), rd(0), ra(0), rm(0), rn(0) {}
MultiplicationField::~MultiplicationField() {}

uint32_t MultiplicationField::get_sflag_1bit(const std::string opcode) const { return opcode_info->at(opcode).at("S"); }

uint32_t MultiplicationField::get_cmd_3bit(const std::string opcode) const { return opcode_info->at(opcode).at("cmd"); }

uint32_t MultiplicationField::get_funct_6bit(const std::string opcode) const {
    auto cmd = get_cmd_3bit(opcode);
    auto sflag = get_sflag_1bit(opcode);
    return sflag | (cmd << 1) | (0b00 << 4);
}

void MultiplicationField::input(std::vector<std::string> asmcode_v) {
    auto opcode = asmcode_v[0];
    std::vector<std::string> operands(asmcode_v.begin() + 1, asmcode_v.end());
    cond = get_cond_4bit(opcode);
    op = get_op_2bit(opcode);

    auto ftype = get_ftype(opcode);
    switch (ftype) {
        case 5:  // Type5: Opcode Rd, Rn, Rm
            funct = get_funct_6bit(opcode);
            rd = get_reg_4bit(operands[0]);
            ra = 0b0000;
            rm = get_reg_4bit(operands[2]);
            rn = get_reg_4bit(operands[1]);
            break;
        case 6:  // Type6: Opcode Rd, Rn, Rm, Ra
            funct = get_funct_6bit(opcode);
            rd = get_reg_4bit(operands[0]);
            ra = get_reg_4bit(operands[3]);
            rm = get_reg_4bit(operands[2]);
            rn = get_reg_4bit(operands[1]);
            break;
        default:
            throw std::runtime_error("Unsupported format type.");
    }
}

uint32_t MultiplicationField::output() {
    return rn | (c << 4) | (rm << 8) | (ra << 12) | (rd << 16) | (funct << 20) | (op << 26) | (cond << 28);
}

void MultiplicationField::clear_field() { cond = op = funct = rd = ra = rm = rn = 0; }

void MultiplicationField::show_field() {
    std::cout << "cond = " << std::bitset<4>(cond) << ", op = " << std::bitset<2>(op)
              << ", funct = " << std::bitset<6>(funct) << ", rd = " << std::bitset<4>(rd)
              << ", ra = " << std::bitset<4>(ra) << ", rm = " << std::bitset<4>(rm) << ", c = " << std::bitset<4>(c)
              << ", rn = " << std::bitset<4>(rn) << std::endl;
}