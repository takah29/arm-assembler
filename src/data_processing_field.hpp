#ifndef _DATA_PROCESSING_FIELD_H
#define _DATA_PROCESSING_FIELD_H

#include <string>
#include <vector>

#include "field.hpp"
#include "types.hpp"

class DataProcessingField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 6bit
    uint32_t rn;     // 4bit
    uint32_t rd;     // 4bit
    uint32_t src2;   // 12bit

    uint32_t get_iflag_1bit(const std::string opcode, const std::string src2) const;
    uint32_t get_sflag_1bit(const std::string opcode) const;
    uint32_t get_cmd_4bit(const std::string opcode) const;
    uint32_t get_funct_6bit(const std::string opcode, const std::string src2) const;

    uint32_t get_shamt5_5bit(const std::string opcode, const std::string src2) const;
    uint32_t get_sh_2bit(const std::string opcode) const;
    uint32_t get_src2_12bit_imm(const std::string src2) const;
    uint32_t get_src2_12bit_shimm(const std::string opcode, const std::vector<std::string> operands) const;
    uint32_t get_src2_12bit_shreg(const std::string opcode, const std::vector<std::string> operands) const;
    uint32_t get_src2_12bit(const std::string opcode, const std::vector<std::string> operands) const;
    uint32_t get_src2_12bit_type123(const std::vector<std::string> operands) const;
    uint32_t get_src2_12bit_type4(const std::string opcode, const std::vector<std::string> operands) const;

    uint32_t encode_imm32(const uint32_t imm32) const;

   public:
    DataProcessingField(OpcodeInfo *opcode_info_ptr);
    ~DataProcessingField();

    void input(std::vector<std::string> asmcode_v, int current_line_num = -1) override;
    uint32_t output() override;
    void clear_field() override;
    void show_field() override;
};

#endif
