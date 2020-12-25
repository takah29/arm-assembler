#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "field.hpp"
#include "types.hpp"

class Assembler {
   public:
    Assembler();
    ~Assembler();

    uint32_t convert(std::string asmcode, const bool debug_flag);

   private:
    inline static const OpcodeInfo opcodebase_info{{"and", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0000}}},
                                                   {"eor", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0001}}},
                                                   {"sub", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0010}}},
                                                   {"rsb", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0011}}},
                                                   {"add", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0100}}},
                                                   {"adc", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0101}}},
                                                   {"sbc", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0110}}},
                                                   {"rsc", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b0111}}},
                                                   {"tst", {{"ftype", 2}, {"op", 0b00}, {"cmd", 0b1000}}},
                                                   {"teq", {{"ftype", 2}, {"op", 0b00}, {"cmd", 0b1001}}},
                                                   {"cmp", {{"ftype", 2}, {"op", 0b00}, {"cmd", 0b1010}}},
                                                   {"cmn", {{"ftype", 2}, {"op", 0b00}, {"cmd", 0b1011}}},
                                                   {"orr", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b1100}}},
                                                   {"mov", {{"ftype", 3}, {"op", 0b00}, {"cmd", 0b1101}, {"sh", 0b00}}},
                                                   {"lsl", {{"ftype", 4}, {"op", 0b00}, {"cmd", 0b1101}, {"sh", 0b00}}},
                                                   {"lsr", {{"ftype", 4}, {"op", 0b00}, {"cmd", 0b1101}, {"sh", 0b01}}},
                                                   {"asr", {{"ftype", 4}, {"op", 0b00}, {"cmd", 0b1101}, {"sh", 0b10}}},
                                                   {"rrx", {{"ftype", 4}, {"op", 0b00}, {"cmd", 0b1101}, {"sh", 0b11}}},
                                                   {"ror", {{"ftype", 4}, {"op", 0b00}, {"cmd", 0b1101}, {"sh", 0b11}}},
                                                   {"bic", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b1110}}},
                                                   {"mvn", {{"ftype", 1}, {"op", 0b00}, {"cmd", 0b1111}}},
                                                   {"mul", {{"ftype", 5}, {"op", 0b00}, {"cmd", 0b000}}},
                                                   {"mla", {{"ftype", 6}, {"op", 0b00}, {"cmd", 0b001}}},
                                                   {"umull", {{"ftype", 6}, {"op", 0b00}, {"cmd", 0b100}}},
                                                   {"umlal", {{"ftype", 6}, {"op", 0b00}, {"cmd", 0b101}}},
                                                   {"smull", {{"ftype", 6}, {"op", 0b00}, {"cmd", 0b110}}},
                                                   {"smlal", {{"ftype", 6}, {"op", 0b00}, {"cmd", 0b111}}},
                                                   {"str", {{"ftype", 7}, {"op", 0b01}, {"B", 0b0}, {"L", 0b0}}},
                                                   {"ldr", {{"ftype", 7}, {"op", 0b01}, {"B", 0b0}, {"L", 0b1}}},
                                                   {"strb", {{"ftype", 7}, {"op", 0b01}, {"B", 0b1}, {"L", 0b0}}},
                                                   {"ldrb", {{"ftype", 7}, {"op", 0b01}, {"B", 0b1}, {"L", 0b1}}},
                                                   {"strh", {{"ftype", 7}, {"op", 0b00}, {"op2", 0b01}, {"L", 0b0}}},
                                                   {"ldrh", {{"ftype", 7}, {"op", 0b00}, {"op2", 0b01}, {"L", 0b1}}},
                                                   {"strsb", {{"ftype", 7}, {"op", 0b00}, {"op2", 0b10}, {"L", 0b1}}},
                                                   {"ldrsh", {{"ftype", 7}, {"op", 0b00}, {"op2", 0b11}, {"L", 0b1}}},
                                                   {"b", {{"ftype", 8}, {"op", 0b10}, {"L", 0b0}}},
                                                   {"bl", {{"ftype", 8}, {"op", 0b10}, {"L", 0b1}}}};
    inline static const std::unordered_map<std::string, uint32_t> cond_info{
        {"eq", 0b0000}, {"ne", 0b0001}, {"cs", 0b0010}, {"hs", 0b0010}, {"cc", 0b0011}, {"lo", 0b0011},
        {"mi", 0b0100}, {"pl", 0b0101}, {"vs", 0b0110}, {"vc", 0b0111}, {"hi", 0b1000}, {"ls", 0b1001},
        {"ge", 0b1010}, {"lt", 0b1011}, {"gt", 0b1100}, {"le", 0b1101}, {"al", 0b1110}};
    OpcodeInfo opcode_info;

    std::vector<std::string> tokenize(const std::string asmcode);
    std::vector<std::string> split_operands(const std::string operandes, const size_t n_operands);
    std::tuple<std::string, std::string> split_opcode(std::string opcode);

    std::array<Field *, 4> fields;
};

#endif