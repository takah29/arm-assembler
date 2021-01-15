#ifndef _BRANCH_FIELD_H
#define _BRANCH_FIELD_H

#include <string>
#include <vector>

#include "field.hpp"
#include "types.hpp"

class BranchField : public Field {
    LabelInfo *label_info_ptr;

    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 2bit
    uint32_t imm24;  // 24bit

    uint32_t get_lflag_1bit(const std::string opcode) const;
    uint32_t get_funct_2bit(const std::string opcode) const;

   public:
    BranchField(OpcodeInfo *opcode_info_ptr, LabelInfo *label_info_ptr);
    ~BranchField();

    void input(std::vector<std::string> asmcode_v) override;
    uint32_t output() override;
    void clear_field() override;
    void show_field() override;
};

#endif
