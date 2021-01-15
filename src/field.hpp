#ifndef _FIELD_H
#define _FIELD_H

#include <string>
#include <vector>

#include "types.hpp"

class Field {
   protected:
    OpcodeInfo *opcode_info_ptr;

    uint32_t get_reg_4bit(const std::string reg) const;
    uint32_t get_cond_4bit(const std::string opcode) const;
    uint32_t get_ftype(const std::string opcode) const;
    uint32_t get_op_2bit(const std::string opcode) const;

   public:
    Field(OpcodeInfo *opcode_info_ptr);
    virtual ~Field();

    virtual void input(std::vector<std::string> asmcode_v) = 0;
    virtual uint32_t output() = 0;
    virtual void clear_field() = 0;
    virtual void show_field() = 0;
};

#endif
