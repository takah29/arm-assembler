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
    virtual void show_field() = 0;
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
