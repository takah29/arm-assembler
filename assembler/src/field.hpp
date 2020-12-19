#ifndef _FIELD_H
#define _FIELD_H

#include <string>
#include <vector>

#include "types.hpp"

class Field {
   public:
    Field();
    virtual ~Field();

    virtual void input(std::vector<std::string> asmcode_v);
    virtual uint32_t output();
};

class DataProcessingField : public Field {
   public:
    DataProcessingField();
    ~DataProcessingField();

    void input(std::vector<std::string> asmcode_v);
    uint32_t output();

   private:
    uint32_t cond;   // 4bit
    uint32_t op;     // 2bit
    uint32_t funct;  // 6bit
    uint32_t rn;     // 4bit
    uint32_t rd;     // 4bit
    uint32_t src2;   // 12bit
};

class MultiplicationField : public Field {
   public:
    MultiplicationField();
    ~MultiplicationField();

    void input(std::vector<std::string> asmcode_v);
    uint32_t output();

   private:
    uint32_t cond;              // 4bit
    uint32_t op;                // 2bit
    uint32_t funct;             // 6bit
    uint32_t rd;                // 4bit
    uint32_t ra;                // 4bit
    uint32_t rm;                // 4bit
    const uint32_t c = 0b1001;  // 4bit
    uint32_t rn;                // 4bit
};

#endif
