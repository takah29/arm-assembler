#include "branch_field.hpp"

#include <bitset>
#include <cmath>
#include <iostream>

BranchField::BranchField(OpcodeInfo *opcode_info_ptr, LabelInfo *label_info_ptr)
    : Field(opcode_info_ptr), label_info_ptr(label_info_ptr), cond(0), op(0), funct(0), imm24(0) {}
BranchField::~BranchField() {}

uint32_t BranchField::get_lflag_1bit(const std::string opcode) const { return opcode_info_ptr->at(opcode).at("L"); }

uint32_t BranchField::get_funct_2bit(const std::string opcode) const {
    auto lflag = get_lflag_1bit(opcode);
    return lflag | (0b1 << 1);
}

uint32_t BranchField::get_imm24_24bit(std::string label, int current_line_num) const {
    int label_num = label_info_ptr->at(label);
    int32_t d = label_num - current_line_num - 2;
    if (!(-pow(2, 23) <= d and d <= pow(2, 23) - 1)) {
        throw std::runtime_error("The branch is too far away.");
    }
    return d & 0x00ffffff;
}

void BranchField::input(std::vector<std::string> asmcode_v, int current_line_num) {
    auto opcode = asmcode_v[0];
    auto label = asmcode_v[1];
    cond = get_cond_4bit(opcode);
    op = get_op_2bit(opcode);

    auto ftype = get_ftype(opcode);
    if (ftype == 8) {  // Type8: Opcode Label
        funct = get_funct_2bit(opcode);
        if (current_line_num == -1) {
            imm24 = 0b0;
        } else {
            imm24 = get_imm24_24bit(label, current_line_num);
        }
    } else {
        throw std::runtime_error("Unsupported format type.");
    }
}

uint32_t BranchField::output() { return imm24 | (funct << 24) | (op << 26) | (cond << 28); }

void BranchField::clear_field() { cond = op = funct = imm24 = 0; }

void BranchField::show_field() {
    std::cout << "cond = " << std::bitset<4>(cond) << ", op = " << std::bitset<2>(op)
              << ", funct = " << std::bitset<2>(funct) << ", imm24 = " << std::bitset<24>(imm24) << std::endl;
}