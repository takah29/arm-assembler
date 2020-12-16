#include "assembler.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "utility.hpp"

Assembler::Assembler() {}
Assembler::~Assembler() {}

uint32_t Assembler::convert(std::string asmcode, const bool debug_flag) {
    std::transform(asmcode.begin(), asmcode.end(), asmcode.begin(), ::tolower);
    // TODO: スペースの数を1つにする処理を追加する
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];
    if (opcode.size() > 5) {
        throw std::runtime_error("opcode string is too long.");
    }

    if (debug_flag) {
        print(tokens);
    }

    auto opcode_base = opcode.substr(0, 3);

    std::vector<std::string> operands(tokens.begin() + 1, tokens.end());

    uint32_t machine_code = 0;
    return machine_code;
}

std::vector<std::string> Assembler::tokenize(const std::string asmcode) {
    auto pos = asmcode.find_first_of(' ');
    auto opcode = asmcode.substr(0, pos);

    auto operands = asmcode.substr(pos + 1);
    operands = replace_all(operands, "  ", " ");

    auto opcode_base = opcode.substr(0, 3);

    std::vector<std::string> tokens{opcode};

    // TODO: operandsからnopを判定するようにする
    if (opcode_base == "nop") {
        return tokens;
    }

    auto ftype = Assembler::opcode_info_map.at(opcode_base).at("ftype");

    std::vector<std::string> operands_v;
    switch (ftype) {
        case 1:
            operands_v = split_operands(operands, 3);
            break;
        case 2:
            operands_v = split_operands(operands, 2);
            break;
        case 3:
            operands_v = split_operands(operands, 2);
            break;
        case 4:
            operands_v = split_operands(operands, 3);
            break;
        case 5:
            operands_v = split_operands(operands, 3);
            break;
        case 6:
            operands_v = split_operands(operands, 4);
            break;
        case 7:
            operands_v = split_operands(operands, 2);
            break;
        case 8:
            operands_v = split_operands(operands, 1);
            break;
        default:
            throw std::runtime_error("undefined format type.");
    }
    tokens.insert(tokens.end(), operands_v.begin(), operands_v.end());
    return tokens;
}

std::vector<std::string> Assembler::split_operands(const std::string operands, const size_t n_operands) {
    std::vector<std::string> result;
    std::string elem = "";
    size_t count_args = 0;

    for (size_t i = 0; i < operands.size(); i++) {
        if (operands[i] != ',' and operands[i] != ' ') {
            elem += operands[i];
        } else if (operands[i] == ',') {
            result.emplace_back(elem);
            elem.clear();
            if (++count_args == n_operands - 1) {
                result.emplace_back(operands.substr(i + 2));
                break;
            }
        }
    }

    return result;
}

/**
 * opcodeの文字列を命令部と条件部に分割する
 * example1: "ADDEQ" -> ("ADD", "EQ")
 * example2: "ADDS" -> ("ADD", "S")
 */
std::tuple<std::string, std::string> Assembler::split_opcode(std::string opcode) {
    std::tuple<std::string, std::string> ret;
    if (opcode.size() <= 3) {
        ret = std::make_tuple(opcode, "");
    } else {
        ret = std::make_tuple(opcode.substr(0, 3), opcode.substr(3));
    }

    return ret;
}

uint32_t Assembler::get_cond_4bit(const std::string opcode_ext) const { return cond_map.at(opcode_ext); }
uint32_t Assembler::get_reg_4bit(const std::string reg) const { return reg[1] - '0'; }
uint32_t Assembler::get_iflag_1bit(const std::vector<std::string> src2) const { return 0; }
