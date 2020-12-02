#include "assembler.hpp"

#include <string>
#include <vector>

Assembler::Assembler() {
    dataproc_insts = {{"AND", "EOR", "SUB", "RSB", "ADD", "ADC", "SBC", "RSC", "TST",
                       "TEQ", "CMP", "CMN", "ORR", "MOV", "LSL", "LSR", "ASR", "RRX",
                       "ROR", "BIC", "MVN", "MUL", "MLA", "UMU", "UML", "SMU", "SML"}};
    memory_insts = {{"STR", "LDR"}};
    branch_insts = {{"B", "BL"}};
    branch_instructions = {{"B", "BL"}};
}
Assembler::~Assembler() {}

std::string Assembler::convert(const std::string asmcode) {
    auto tokens = tokenize(asmcode);
    std::string opcode = tokens[0];

    return asmcode;
}

std::vector<std::string> Assembler::tokenize(const std::string asmcode) {
    std::vector<std::string> tokens{};
    size_t left_pos = 0, right_pos = 0;
    bool in_brackets = false;

    for (size_t i = 1; i < asmcode.size(); i++) {
        if (in_brackets == true) continue;

        if (asmcode[i] == ' ') {
            if (asmcode[i - 1] == ',') {
                right_pos = left_pos = i;
            } else if (asmcode[i - 1] != ' ') {
                right_pos = i;
                tokens.push_back(asmcode.substr(left_pos, right_pos - left_pos));
                left_pos = i;
            }
        } else if (asmcode[i] == '[' or asmcode[i] == '{') {
            in_brackets = true;
            left_pos = right_pos = i;
        } else if (asmcode[i] == ']' or asmcode[i] == '}') {
            in_brackets = false;
            right_pos = i;
            tokens.push_back(asmcode.substr(left_pos, right_pos - left_pos + 1));
            left_pos = i;
        } else if (asmcode[i] == ',') {
            right_pos = i;
            tokens.push_back(asmcode.substr(left_pos, right_pos - left_pos));
            left_pos = i;
        } else if (asmcode[i] != ' ' and asmcode[i - 1] == ' ') {
            left_pos = right_pos = i;
        }
    }

    tokens.push_back(asmcode.substr(left_pos, asmcode.size() - left_pos + 1));

    return tokens;
}
