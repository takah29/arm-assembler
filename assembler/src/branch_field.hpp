#ifndef _BRANCH_FIELD_H
#define _BRANCH_FIELD_H

#include <string>
#include <unordered_map>
#include <vector>

#include "field.hpp"
#include "types.hpp"

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
