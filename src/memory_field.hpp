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
    uint32_t get_funct_6bit(const std::string opcode, const std::string adr) const;

   public:
    MemoryField(OpcodeInfo *opcode_info);
    ~MemoryField();

    void input(std::vector<std::string> asmcode_v) override;
    uint32_t output() override;
    void clear_field() override;
    void show_field() override;
};

#endif
