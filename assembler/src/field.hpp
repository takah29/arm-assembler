#ifndef _FIELD_H
#define _FIELD_H

#include <string>
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

#endif
