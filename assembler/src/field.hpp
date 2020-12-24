#ifndef _FIELD_H
#define _FIELD_H

#include <string>
#include <unordered_map>
#include <vector>

#include "types.hpp"

class Field {
   protected:
    OpcodeInfo *opcode_info;

    uint32_t get_reg_4bit(const std::string reg) const;

   public:
    Field(OpcodeInfo *opcode_info);
    virtual ~Field();

    virtual void input(std::vector<std::string> asmcode_v) = 0;
    virtual uint32_t output() = 0;
    virtual void clear_field() = 0;
};

class DataProcessingField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 6bit
    uint32_t rn;     // 4bit
    uint32_t rd;     // 4bit
    uint32_t src2;   // 12bit

    uint32_t get_iflag_1bit(const std::string opcode, const std::string src2) const;
    uint32_t get_sflag_1bit(const std::string opcode) const;
    uint32_t get_cond_4bit(const std::string opcode) const;
    uint32_t get_cmd_4bit(const std::string opcode) const;
    constexpr uint32_t get_op_2bit() const;
    uint32_t get_funct_6bit(const std::string opcode, const std::string src2) const;

    uint32_t get_shamt5_5bit(const std::string opcode, const std::string src2) const;
    uint32_t get_sh_2bit(const std::string opcode) const;
    uint32_t get_src2_12bit_imm(const std::string src2) const;
    uint32_t get_src2_12bit_reg_shimm(const std::string opcode, const std::string src2) const;
    uint32_t get_src2_12bit_shreg(const std::string opcode, const std::vector<std::string> operands) const;
    uint32_t get_src2_12bit(const std::string opcode, const std::vector<std::string> operands) const;

    uint32_t encode_imm32(const uint32_t imm32) const;

   public:
    DataProcessingField(OpcodeInfo *opcode_info);
    ~DataProcessingField();

    void input(std::vector<std::string> asmcode_v) override;
    uint32_t output() override;
    void clear_field() override;
};

class MultiplicationField : public Field {
    uint32_t cond;              // 4bit
    uint32_t op;                // 2bit
    uint32_t funct;             // 6bit
    uint32_t rd;                // 4bit
    uint32_t ra;                // 4bit
    uint32_t rm;                // 4bit
    const uint32_t c = 0b1001;  // 4bit
    uint32_t rn;                // 4bit

   public:
    MultiplicationField(OpcodeInfo *opcode_info);
    ~MultiplicationField();

    void input(std::vector<std::string> asmcode_v) override;
    uint32_t output() override;
};

class MemoryField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 6bit
    uint32_t rn;     // 4bit
    uint32_t rd;     // 4bit
    uint32_t src2;   // 12bit

   public:
    MemoryField(OpcodeInfo *opcode_info);
    ~MemoryField();

    void input(std::vector<std::string> asmcode_v) override;
    uint32_t output() override;
};

class BranchField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 2bit
    uint32_t imm24;  // 24bit

   public:
    BranchField(OpcodeInfo *opcode_info);
    ~BranchField();

    void input(std::vector<std::string> asmcode_v) override;
    uint32_t output() override;
};

#endif
