#ifndef _MULTIPLICATION_FIELD_H
#define _MULTIPLICATION_FIELD_H

#include <string>
#include <unordered_map>
#include <vector>

#include "field.hpp"
#include "types.hpp"

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

#endif
