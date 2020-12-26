#include "assembler.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "data_processing_field.hpp"
#include "memory_field.hpp"
#include "multiplication_field.hpp"
#include "utility.hpp"

Assembler::Assembler() {
    // 命令ニモニックと条件ニモニックの定義からオペコード情報を定義
    for (auto &x : opcodebase_info) {
        auto ftype = x.second.at("ftype");
        // 基本命令の登録
        opcode_info[x.first] = x.second;
        opcode_info[x.first]["cond"] = cond_info.at("al");

        if (ftype == 2) {
            // TST, TEQ, CMP, CMNは無条件にS = 1
            opcode_info[x.first]["S"] = 0b1;
        } else if (1 <= ftype and ftype <= 6) {
            opcode_info[x.first]["S"] = 0b0;

            // 基本命令のS命令を登録
            opcode_info[x.first + 's'] = x.second;
            opcode_info[x.first + 's']["cond"] = cond_info.at("al");
            opcode_info[x.first + 's']["S"] = 0b1;
        }

        for (auto &y : cond_info) {
            // 条件命令の登録
            auto opcode_ex = x.first + y.first;
            opcode_info[opcode_ex] = x.second;
            opcode_info[opcode_ex]["cond"] = y.second;

            if (ftype == 2) {
                // TST, TEQ, CMP, CMNは無条件にS = 1
                opcode_info[opcode_ex]["S"] = 0b1;
            } else if (1 <= ftype and ftype <= 6) {
                opcode_info[opcode_ex]["S"] = 0b0;

                // 条件命令のS命令を登録
                opcode_info[opcode_ex + 's'] = x.second;
                opcode_info[opcode_ex + 's']["cond"] = cond_info.at("al");
                opcode_info[opcode_ex + 's']["S"] = 0b1;
            }
        }
    }

    // Fieldクラスの設定
    fields[0] = new DataProcessingField(&opcode_info);
    fields[1] = new MultiplicationField(&opcode_info);
    fields[2] = new MemoryField(&opcode_info);
}

Assembler::~Assembler() {
    delete fields[0];
    delete fields[1];
    delete fields[2];
}

uint32_t Assembler::convert(std::string asmcode, const bool debug_flag) {
    std::transform(asmcode.begin(), asmcode.end(), asmcode.begin(), ::tolower);
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];
    if (opcode.size() == 0 or 5 < opcode.size()) {
        throw std::runtime_error("Invalied opecode length.");
    }

    uint32_t machine_code = 0;
    auto ftype = opcode_info.at(opcode).at("ftype");
    if (1 <= ftype and ftype <= 4) {
        fields[0]->input(tokens);
        fields[0]->show_field();
        machine_code = fields[0]->output();
    } else if (5 <= ftype and ftype <= 6) {
        fields[1]->input(tokens);
        fields[1]->show_field();
        machine_code = fields[1]->output();
    } else {
        throw std::runtime_error("unsupported format type.");
    }

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
