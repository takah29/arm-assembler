#include "field.hpp"

Field::Field(OpcodeInfo *opcode_info) : opcode_info(opcode_info) {}
Field::~Field() {}

uint32_t Field::get_reg_4bit(const std::string reg) const {
    if (reg == "pc") {
        return 15;
    } else if (reg == "lr") {
        return 14;
    } else if (reg == "sp") {
        return 13;
    }

    uint32_t reg_num = std::stoi(reg.substr(1, 2));
    if (reg_num < 16) {
        return reg_num;
    } else {
        throw std::runtime_error("Invalied register number.");
    }
}

uint32_t Field::get_cond_4bit(const std::string opcode) const { return opcode_info->at(opcode).at("cond"); }