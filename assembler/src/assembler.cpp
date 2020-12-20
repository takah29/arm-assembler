#include "assembler.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "utility.hpp"

Assembler::Assembler() {
    // 命令ニモニックと条件ニモニックの定義からオペコード情報を定義
    for (auto &x : opcodebase_info) {
        // 基本命令の登録
        opcode_info[x.first] = x.second;
        opcode_info[x.first]["cond"] = cond_info.at("al");
        opcode_info[x.first]["S"] = 0b0;

        // S命令の登録
        opcode_info[x.first + 's'] = x.second;
        opcode_info[x.first + 's']["cond"] = cond_info.at("al");
        opcode_info[x.first + 's']["S"] = 0b1;

        for (auto &y : cond_info) {
            // 条件命令の登録
            // TST, TEQ, CMP, CMNは無条件にS = 1
            auto new_key = x.first + y.first;
            opcode_info[new_key] = x.second;
            opcode_info[new_key]["cond"] = y.second;
            if (x.second.at("ftype") != 2) {
                opcode_info[new_key]["S"] = 0b0;
            } else {
                opcode_info[new_key]["S"] = 0b1;
            }

            // 条件命令 + S命令の登録
            if (x.second.at("ftype") != 2) {
                opcode_info[new_key + 's'] = x.second;
                opcode_info[new_key + 's']["cond"] = y.second;
                opcode_info[new_key + 's']["S"] = 0b1;
            }
        }
    }
}

Assembler::~Assembler() {}

uint32_t Assembler::convert(std::string asmcode, const bool debug_flag) {
    std::transform(asmcode.begin(), asmcode.end(), asmcode.begin(), ::tolower);
    // TODO: スペースの数を1つにする処理を追加する
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];
    if (opcode.size() == 0 or 5 < opcode.size()) {
        throw std::runtime_error("Invalied opecode length.");
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
    std::vector<std::string> tokens{opcode};

    // TODO: operandsからnopを判定するようにする
    if (opcode.substr(0, 3) == "nop") {
        return tokens;
    }

    auto ftype = Assembler::opcode_info.at(opcode).at("ftype");

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

    if (n_operands == 1) {
        result.emplace_back(operands);
        return result;
    }

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
