#include "assembler.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include "branch_field.hpp"
#include "data_processing_field.hpp"
#include "memory_field.hpp"
#include "multiplication_field.hpp"
#include "utility.hpp"

Assembler::Assembler(bool debug_flag) : debug_flag(debug_flag) {
    initialize();
    set_fields();
}

Assembler::Assembler(std::vector<std::string> assemblies, bool debug_flag)
    : assemblies(assemblies), debug_flag(debug_flag) {
    normalize(assemblies);
    initialize();
    build_label_info(assemblies);
    set_fields();
}

Assembler::~Assembler() {
    delete fields[0];
    delete fields[1];
    delete fields[2];
    delete fields[3];
}

uint32_t Assembler::convert(std::string asmcode, int current_line_num) {
    asmcode = unit_space(strip(asmcode));
    std::transform(asmcode.begin(), asmcode.end(), asmcode.begin(), ::tolower);
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];
    if (opcode.size() == 0 or 5 < opcode.size()) {
        throw std::runtime_error("Invalied opecode length.");
    }

    auto ftype = opcode_info.at(opcode).at("ftype");
    auto num = [&]() {
        int n;
        if (1 <= ftype and ftype <= 4) {
            n = 0;
        } else if (5 <= ftype and ftype <= 6) {
            n = 1;
        } else if (ftype == 7) {
            n = 2;
        } else if (ftype == 8) {
            n = 3;
        } else {
            n = -1;
        }
        return n;
    }();

    uint32_t machine_code = 0;
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    if (0 <= num and num < 4) {
        fields[num]->input(tokens, current_line_num);
        if (debug_flag) {
            std::cout << std::setw(25) << asmcode << " -> ";
            fields[num]->show_field();
        }
        machine_code = fields[num]->output();
    } else {
        throw std::runtime_error("unsupported format type.");
    }

    return machine_code;
}

std::vector<uint32_t> Assembler::convert_all() {
    std::vector<uint32_t> result;
    for (size_t i = 0; i < assemblies.size(); i++) {
        result.emplace_back(convert(assemblies[i], i));
    }

    return result;
}

void Assembler::initialize() {
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
}

void Assembler::set_fields() {
    // Fieldクラスの設定
    fields[0] = new DataProcessingField(&opcode_info);
    fields[1] = new MultiplicationField(&opcode_info);
    fields[2] = new MemoryField(&opcode_info);
    fields[3] = new BranchField(&opcode_info, &label_info);
}

void Assembler::build_label_info(const std::vector<std::string> assemblies) {
    for (size_t num = 0; num < assemblies.size(); num++) {
        set_label(assemblies[num], num);
    }
}

std::vector<std::string> Assembler::tokenize(std::string asmcode) {
    auto pos = asmcode.find_first_of(' ');
    auto token = asmcode.substr(0, pos);
    std::string opcode;
    if (opcode_info.find(token) == opcode_info.end()) {
        asmcode = asmcode.substr(pos + 1);
        pos = asmcode.find_first_of(' ');
        opcode = asmcode.substr(0, pos);
    } else {
        opcode = token;
    }
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

void Assembler::set_label(std::string asmcode, int num) {
    std::transform(asmcode.begin(), asmcode.end(), asmcode.begin(), ::tolower);

    auto pos = asmcode.find_first_of(' ');
    auto token = asmcode.substr(0, pos);
    if (opcode_info.find(token) == opcode_info.end()) {
        label_info[token] = num;
    }
}

void Assembler::normalize(std::vector<std::string> &assemblies) {
    auto f = [](std::string x) { return unit_space(strip(x)); };
    transform(assemblies.begin(), assemblies.end(), assemblies.begin(), f);
}
