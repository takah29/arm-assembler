#include "field.hpp"

Field::Field(OpcodeInfo *opcode_info) : opcode_info(opcode_info) {}
Field::~Field() {}

uint32_t Field::get_reg_4bit(const std::string reg) const {
    uint32_t reg_num = std::stoi(reg.substr(1, 2));
    if (reg_num < 16) {
        return reg_num;
    } else {
        throw std::runtime_error("Invalied register number.");
    }
}

DataProcessingField::DataProcessingField(OpcodeInfo *opcode_info)
    : Field(opcode_info), cond(0), op(0), funct(0), rn(0), rd(0), src2(0) {}
DataProcessingField::~DataProcessingField() {}

uint32_t DataProcessingField::get_iflag_1bit(const std::string src2) const { return (src2[0] == '#') ? 0b1 : 0b0; }

uint32_t DataProcessingField::get_sflag_1bit(const std::string opcode) const { return opcode_info->at(opcode).at("S"); }

uint32_t DataProcessingField::get_cond_4bit(const std::string opcode) const {
    return opcode_info->at(opcode).at("cond");
}

uint32_t DataProcessingField::get_cmd_4bit(const std::string opcode) const { return opcode_info->at(opcode).at("cmd"); }

constexpr uint32_t DataProcessingField::get_op_2bit() const { return 0b00; }

uint32_t DataProcessingField::get_funct_6bit(const std::string opcode, const std::string src2) const {
    auto iflag = get_iflag_1bit(src2);
    auto cmd = get_cmd_4bit(opcode);
    auto sflag = get_sflag_1bit(opcode);
    auto funct = sflag | (cmd << 1) | (iflag << 5);
    return funct;
};

uint32_t DataProcessingField::get_src2_12bit(const std::string src2) const {}

void DataProcessingField::input(std::vector<std::string> asmcode_v) {
    auto opcode = asmcode_v[0];
    std::vector<std::string> operands(asmcode_v.begin() + 1, asmcode_v.end());
    cond = opcode_info->at(opcode).at("cond");
    op = 0b00;

    auto ftype = opcode_info->at(opcode).at("ftype");
    switch (ftype) {
        case 1:  // Type1: Opcode Rd, Rn, Src2
            funct = get_funct_6bit(opcode, operands[2]);
            rn = get_reg_4bit(operands[1]);
            rd = get_reg_4bit(operands[0]);
            src2 = get_src2_12bit(operands[2]);
            break;
        case 2:  // Type2: Opcode Rn, Src2
            break;
        case 3:  // Type3: Opcode Rd, Src2
            break;
        case 4:  // Type4: Opcode Rd, Rm, Rs/shamt5
            break;
        default:
            throw std::runtime_error("Unsupported format type.");
    }
}

uint32_t DataProcessingField::output() {
    uint32_t field = src2 | (rd << 12) | (rn << 16) | (funct << 20) | (op << 26) | (cond << 28);
    return field;
}
