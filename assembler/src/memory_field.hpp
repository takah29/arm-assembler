#ifndef _MEMORY_FIELD_H
#define _MEMORY_FIELD_H

#include <string>
#include <unordered_map>
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

   public:
    MemoryField(OpcodeInfo *opcode_info);
    ~MemoryField();

    void input(std::vector<std::string> asmcode_v) override;
    uint32_t output() override;
};

#endif
