#include "assembler.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

Assembler::Assembler() {}
Assembler::~Assembler() {}

uint32_t Assembler::convert(std::string asmcode) {
    std::transform(asmcode.begin(), asmcode.end(), asmcode.begin(), ::tolower);
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];
    if (opcode.size() > 5) {
        throw std::runtime_error("opcode string is too long.");
    }

    auto opcode_base = opcode.substr(0, 3);

    std::vector<std::string> operands(tokens.begin() + 1, tokens.end());

    uint32_t machine_code;
    if (opcode_base == "and") {
        machine_code = _and(opcode, operands);
    } else if (opcode_base == "eor") {
        machine_code = _eor(opcode, operands);
    } else if (opcode_base == "sub") {
        machine_code = _sub(opcode, operands);
    } else if (opcode_base == "rsb") {
        machine_code = _rsb(opcode, operands);
    } else if (opcode_base == "add") {
        machine_code = _add(opcode, operands);
    } else if (opcode_base == "adc") {
        machine_code = _adc(opcode, operands);
    } else if (opcode_base == "sbc") {
        machine_code = _sbc(opcode, operands);
    } else if (opcode_base == "rsc") {
        machine_code = _rsc(opcode, operands);
    } else if (opcode_base == "tst") {
        machine_code = _tst(opcode, operands);
    } else if (opcode_base == "teq") {
        machine_code = _teq(opcode, operands);
    } else if (opcode_base == "cmp") {
        machine_code = _cmp(opcode, operands);
    } else if (opcode_base == "cmn") {
        machine_code = _cmn(opcode, operands);
    } else if (opcode_base == "orr") {
        machine_code = _orr(opcode, operands);
    } else if (opcode_base == "mov") {
        machine_code = _mov(opcode, operands);
    } else if (opcode_base == "lsl") {
        machine_code = _lsl(opcode, operands);
    } else if (opcode_base == "lsr") {
        machine_code = _lsr(opcode, operands);
    } else if (opcode_base == "asr") {
        machine_code = _asr(opcode, operands);
    } else if (opcode_base == "rrx") {
        machine_code = _rrx(opcode, operands);
    } else if (opcode_base == "ror") {
        machine_code = _ror(opcode, operands);
    } else if (opcode_base == "bic") {
        machine_code = _bic(opcode, operands);
    } else if (opcode_base == "mvn") {
        machine_code = _mvn(opcode, operands);
    } else if (opcode_base == "mul" or opcode_base == "umu" or opcode_base == "smu") {
        machine_code = _mul(opcode, operands);
    } else if (opcode_base == "mla" or opcode_base == "uml" or opcode_base == "sml") {
        machine_code = _mla(opcode, operands);
    } else if (opcode_base == "str") {
        machine_code = _str(opcode, operands);
    } else if (opcode_base == "ldr") {
        machine_code = _ldr(opcode, operands);
    } else if (opcode_base == "b") {
        machine_code = _b(opcode, operands);
    } else if (opcode_base == "bl") {
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

uint32_t Assembler::get_cond_4bit(const std::string opcode_ext) const { return condition_map.at(opcode_ext); }

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