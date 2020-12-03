#include "assembler.hpp"

#include <algorithm>
#include <string>
#include <vector>

Assembler::Assembler() {}
Assembler::~Assembler() {}

std::string Assembler::convert(const std::string asmcode) {
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];
    auto opcode_ = opcode.substr(0, 3);
    std::vector<std::string> operands(tokens.begin() + 1, tokens.end());

    if (opcode_ == "and") {
        _and(opcode, operands);
    } else if (opcode_ == "eor") {
        _and(opcode_, operands);
    }

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

/* Data Processing Instructions */
uint32_t Assembler::_and(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_eor(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_sub(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_rsb(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_add(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_adc(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_sbc(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_rsc(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_tst(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_teq(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_cmp(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_cmn(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_orr(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_mov(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_lsl(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_lsr(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_asr(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_rrx(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_ror(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_bic(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_mvn(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_mul(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_mla(std::string opcode, std::vector<std::string> operands) { return 0; };

/* Memory Instructions*/
uint32_t Assembler::_str(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_ldr(std::string opcode, std::vector<std::string> operands) { return 0; };

/* Branch Instructions */
uint32_t Assembler::_b(std::string opcode, std::vector<std::string> operands) { return 0; };
uint32_t Assembler::_bl(std::string opcode, std::vector<std::string> operands) { return 0; };