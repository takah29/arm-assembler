#include "field.hpp"

#include "utility.hpp"

Field::Field(OpcodeInfo *opcode_info_ptr) : opcode_info_ptr(opcode_info_ptr) {}
Field::~Field() {}

bool Field::is_register_str(std::string s) const { return s[0] == 'r' or s[0] == 'p' or s[0] == 'l' or s[0] == 's'; }

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

uint32_t Field::get_cond_4bit(const std::string opcode) const { return opcode_info_ptr->at(opcode).at("cond"); }

uint32_t Field::get_ftype(const std::string opcode) const { return opcode_info_ptr->at(opcode).at("ftype"); }

uint32_t Field::get_op_2bit(const std::string opcode) const { return opcode_info_ptr->at(opcode).at("op"); }

uint32_t Field::get_src2_12bit_reg_shift(const std::string src2) const {
    auto src2_split = split_reg(src2, ", | ");
    uint32_t rm = 0, sh = 0;

    if (src2_split.size() == 1) {
        if (is_register_str(src2_split[0])) {
            return get_reg_4bit(src2_split[0]);
        } else {
            throw std::runtime_error("unsupported description.");
        }
    } else if (src2_split.size() == 3) {
        rm = get_reg_4bit(src2_split[0]);

        if (src2_split[1] == "lsl") {
            sh = 0b00;
        } else if (src2_split[1] == "lsr") {
            sh = 0b01;
        } else if (src2_split[1] == "asr") {
            sh = 0b10;
        } else if (src2_split[1] == "ror") {
            sh = 0b11;
        } else {
            throw std::runtime_error("wrong number of elements in src2");
        }
    }

    if (src2_split[2][0] == '#') {
        uint32_t shamt5 = std::stoul(src2_split[2].substr(1)) % 32;
        return rm | (0b0 << 4) | (sh << 5) | (shamt5 << 7);
    } else if (is_register_str(src2_split[2])) {
        uint32_t rs = get_reg_4bit(src2_split[2]);
        return rm | (0b1 << 4) | (sh << 5) | (0b0 << 7) | (rs << 8);
    } else {
        throw std::runtime_error("unsupported description.");
    }
}
