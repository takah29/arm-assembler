#ifndef _FIELD_H
#define _FIELD_H

#include <string>
#include <vector>

#include "types.hpp"

class Field {
   public:
    virtual ~Field();

    virtual void input(std::vector<std::string> asmcode_v);
    virtual uint32_t output();
};

class DataProcessingField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 6bit
    uint32_t rn;     // 4bit
    uint32_t rd;     // 4bit
    uint32_t src2;   // 12bit

   public:
    DataProcessingField();
    ~DataProcessingField();

    void input(std::vector<std::string> asmcode_v);
    uint32_t output();
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
    MultiplicationField();
    ~MultiplicationField();

    void input(std::vector<std::string> asmcode_v);
    uint32_t output();
};

class MemoryField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 6bit
    uint32_t rn;     // 4bit
    uint32_t rd;     // 4bit
    uint32_t src2;   // 12bit

   public:
    MemoryField();
    ~MemoryField();

    void input(std::vector<std::string> asmcode_v);
    uint32_t output();
};

class BranchField : public Field {
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 2bit
    uint32_t imm24;  // 24bit

   public:
    BranchField();
    ~BranchField();

    void input(std::vector<std::string> asmcode_v);
    uint32_t output();
};

#endif
