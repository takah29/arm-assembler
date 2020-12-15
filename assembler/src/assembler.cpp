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
    auto tokens = tokenize(asmcode);

    std::string opcode = tokens[0];
    if (opcode.size() > 5) {
        throw std::runtime_error("opcode string is too long.");
    }

    if (debug_flag) {
        std::cout << tokens[0];
        for (size_t i = 1; i < tokens.size(); i++) {
            std::cout << " | " << tokens[i];
        }
        std::cout << std::endl;
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
    auto pos = asmcode.find_first_of(' ');
    auto opcode = asmcode.substr(0, pos);
    auto operands = asmcode.substr(pos + 1);
    auto opcode_base = opcode.substr(0, 3);

    std::vector<std::string> tokens;
    auto ftype = Assembler::opcode_info_map.at(opcode_base).at("ftype");

    switch (ftype) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default:
            break;
    }
    return tokens;
}

std::vector<std::string> Assembler::split_operands(const std::string operandes, const size_t n_operands) {
    std::vector<std::string> result;
    auto inds = find_all(operandes, ",");
    for (size_t i = 0; i < n_operands - 1; i++) {
        result.push_back(operandes.substr(inds[i], inds[i + 1] - inds[i]));
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

/* Data Processing Instructions */
uint32_t Assembler::_and(std::string opcode, [[maybe_unused]] std::vector<std::string> operands) {
    auto [opcode_base, opcode_ext] = split_opcode(opcode);
    auto rd = operands[0];
    auto rn = operands[1];
    std::vector<std::string> src2(operands.begin() + 2, operands.end());

    // auto rd_bits = get_reg_4bit(rd);
    // auto rn_bits = get_reg_4bit(rn);
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