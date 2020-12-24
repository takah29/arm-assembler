#include "multiplication_field.hpp"

#include <bitset>

#include "utility.hpp"

MultiplicationField::MultiplicationField(OpcodeInfo *opcode_info)
    : Field(opcode_info), cond(0), op(0), funct(0), rd(0), ra(0), rm(0), rn(0) {}
MultiplicationField::~MultiplicationField() {}

void MultiplicationField::input(std::vector<std::string> asmcode_v) {
    auto opcode = asmcode_v[0];
    std::vector<std::string> operands(asmcode_v.begin() + 1, asmcode_v.end());
    cond = get_cond_4bit(opcode);
    op = 0b00;
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