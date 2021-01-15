#ifndef _MEMORY_FIELD_H
#define _MEMORY_FIELD_H

#include <string>
#include <vector>

#include "field.hpp"
#include "types.hpp"

class MemoryField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 6bit
    uint32_t rn;     // 4bit
    uint32_t rd;     // 4bit
    uint32_t src2;   // 12bit

    uint32_t get_iflag_1bit(const std::string src2) const;
    uint32_t get_uflag_1bit(const std::string operand_src2) const;
    uint32_t get_bflag_1bit(const std::string operand_src2) const;
    uint32_t get_lflag_1bit(const std::string operand_src2) const;
    std::tuple<uint32_t, uint32_t> get_pwflag(const std::string adr) const;
    uint32_t get_funct_6bit(const std::string opcode, const std::string adr) const;
    uint32_t get_funct_6bit_ext(const std::string opcode, const std::string adr) const;

    uint32_t get_op2_2bit(const std::string opcode) const;
    uint32_t get_src2_12bit_imm(const std::string operand_src2) const;
    uint32_t get_src2_12bit_reg(const std::string operand_src2) const;
    uint32_t get_src2_12bit_imm_ext(const std::string opcode, const std::string operand_src2) const;
    uint32_t get_src2_12bit_reg_ext(const std::string opcode, const std::string operand_src2) const;

    uint32_t to_imm(std::string operand_src2, int n_bit) const;
    std::vector<std::string> adr_to_operands(std::string adr) const;

   public:
    MemoryField(OpcodeInfo *opcode_info_ptr);
    ~MemoryField();

    void input(std::vector<std::string> asmcode_v, int current_line_num=-1) override;
    uint32_t output() override;
    void clear_field() override;
    void show_field() override;
};

#endif
