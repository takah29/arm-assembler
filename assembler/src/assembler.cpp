#include "assembler.hpp"

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

Assembler::Assembler() {}
Assembler::~Assembler() {}

uint32_t Assembler::convert(std::string asmcode) {
    std::transform(asmcode.begin(), asmcode.end(), asmcode.begin(), ::tolower);
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];

    auto opcode_ = opcode.substr(0, 3);
    assert(opcode_.size() > 5);

    std::vector<std::string> operands(tokens.begin() + 1, tokens.end());

    uint32_t machine_code;
    if (opcode_ == "and") {
        machine_code = _and(opcode, operands);
    } else if (opcode_ == "eor") {
        machine_code = _eor(opcode, operands);
    } else if (opcode_ == "sub") {
        machine_code = _sub(opcode, operands);
    } else if (opcode_ == "rsb") {
        machine_code = _rsb(opcode, operands);
    } else if (opcode_ == "add") {
        machine_code = _add(opcode, operands);
    } else if (opcode_ == "adc") {
        machine_code = _adc(opcode, operands);
    } else if (opcode_ == "sbc") {
        machine_code = _sbc(opcode, operands);
    } else if (opcode_ == "rsc") {
        machine_code = _rsc(opcode, operands);
    } else if (opcode_ == "tst") {
        machine_code = _tst(opcode, operands);
    } else if (opcode_ == "teq") {
        machine_code = _teq(opcode, operands);
    } else if (opcode_ == "cmp") {
        machine_code = _cmp(opcode, operands);
    } else if (opcode_ == "cmn") {
        machine_code = _cmn(opcode, operands);
    } else if (opcode_ == "orr") {
        machine_code = _orr(opcode, operands);
    } else if (opcode_ == "mov") {
        machine_code = _mov(opcode, operands);
    } else if (opcode_ == "lsl") {
        machine_code = _lsl(opcode, operands);
    } else if (opcode_ == "lsr") {
        machine_code = _lsr(opcode, operands);
    } else if (opcode_ == "asr") {
        machine_code = _asr(opcode, operands);
    } else if (opcode_ == "rrx") {
        machine_code = _rrx(opcode, operands);
    } else if (opcode_ == "ror") {
        machine_code = _ror(opcode, operands);
    } else if (opcode_ == "bic") {
        machine_code = _bic(opcode, operands);
    } else if (opcode_ == "mvn") {
        machine_code = _mvn(opcode, operands);
    } else if (opcode_ == "mul" or opcode_ == "umu" or opcode_ == "smu") {
        machine_code = _mul(opcode, operands);
    } else if (opcode_ == "mla" or opcode_ == "uml" or opcode_ == "sml") {
        machine_code = _mla(opcode, operands);
    } else if (opcode_ == "str") {
        machine_code = _str(opcode, operands);
    } else if (opcode_ == "ldr") {
        machine_code = _ldr(opcode, operands);
    } else if (opcode_ == "b") {
        machine_code = _b(opcode, operands);
    } else if (opcode_ == "bl") {
        machine_code = _bl(opcode, operands);
    } else {
        machine_code = _unk(opcode, operands);
    }

    return machine_code;
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
uint32_t Assembler::_and(std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    if (opcode.size() == 3) {
    } else if (opcode.size() == 4) {
    } else {
    }
    return 0;
};  // not inplemented
uint32_t Assembler::_eor([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_sub([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_rsb([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_add([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_adc([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_sbc([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_rsc([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_tst([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_teq([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_cmp([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_cmn([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_orr([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_mov([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_lsl([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_lsr([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_asr([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_rrx([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_ror([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_bic([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_mvn([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_mul([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_mla([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented

/* Memory Instructions*/
uint32_t Assembler::_str([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_ldr([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented

/* Branch Instructions */
uint32_t Assembler::_b([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented
uint32_t Assembler::_bl([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented

/* Unknown Instruction */
uint32_t Assembler::_unk([[maybe_unused]] std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    return 0;
};  // not inplemented