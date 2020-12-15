#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

class Assembler {
   public:
    Assembler();
    ~Assembler();

    uint32_t convert(std::string asmcode, const bool debug_flag);

   private:
    inline static const std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> opcode_info_map{
        {"and", {{"ftype", 1}, {"cmd", 0b0000}}},
        {"eor", {{"ftype", 1}, {"cmd", 0b0001}}},
        {"sub", {{"ftype", 1}, {"cmd", 0b0010}}},
        {"rsb", {{"ftype", 1}, {"cmd", 0b0011}}},
        {"add", {{"ftype", 1}, {"cmd", 0b0100}}},
        {"adc", {{"ftype", 1}, {"cmd", 0b0101}}},
        {"sbc", {{"ftype", 1}, {"cmd", 0b0110}}},
        {"rsc", {{"ftype", 1}, {"cmd", 0b0111}}},
        {"tst", {{"ftype", 2}, {"cmd", 0b1000}}},
        {"teq", {{"ftype", 2}, {"cmd", 0b1001}}},
        {"cmp", {{"ftype", 2}, {"cmd", 0b1010}}},
        {"cmn", {{"ftype", 2}, {"cmd", 0b1011}}},
        {"orr", {{"ftype", 1}, {"cmd", 0b1100}}},
        {"mov", {{"ftype", 3}, {"cmd", 0b1101}}},
        {"lsl", {{"ftype", 4}, {"cmd", 0b1101}}},
        {"lsr", {{"ftype", 4}, {"cmd", 0b1101}}},
        {"asr", {{"ftype", 4}, {"cmd", 0b1101}}},
        {"rrx", {{"ftype", 4}, {"cmd", 0b1101}}},
        {"ror", {{"ftype", 4}, {"cmd", 0b1101}}},
        {"bic", {{"ftype", 1}, {"cmd", 0b1110}}},
        {"mvn", {{"ftype", 1}, {"cmd", 0b1111}}},
        {"mul", {{"ftype", 5}, {"cmd", 0b000}}},
        {"mla", {{"ftype", 6}, {"cmd", 0b001}}},
        {"umu", {{"ftype", 6}, {"cmd", 0b100}}},
        {"uml", {{"ftype", 6}, {"cmd", 0b101}}},
        {"smu", {{"ftype", 6}, {"cmd", 0b110}}},
        {"sml", {{"ftype", 6}, {"cmd", 0b111}}},
        {"str", {{"ftype", 7}, {"L", 0b0}}},
        {"ldr", {{"ftype", 7}, {"L", 0b1}}},
        {"b",   {{"ftype", 8}, {"L", 0b0}}},
        {"bl",  {{"ftype", 8}, {"L", 0b1}}}};
    inline static const std::unordered_map<std::string, uint32_t> cond_map{
        {"eq", 0b0000}, {"ne", 0b0001}, {"cs", 0b0010}, {"hs", 0b0010}, {"cc", 0b0011}, {"lo", 0b0011},
        {"mi", 0b0100}, {"pl", 0b0101}, {"vs", 0b0110}, {"vc", 0b0111}, {"hi", 0b1000}, {"ls", 0b1001},
        {"ge", 0b1010}, {"lt", 0b1011}, {"gt", 0b1100}, {"le", 0b1101}, {"al", 0b1110}};

    std::vector<std::string> tokenize(const std::string asmcode);
    std::vector<std::string> split_operands(const std::string operandes, const size_t n_operands);
    std::tuple<std::string, std::string> split_opcode(std::string opcode);

    uint32_t get_cond_4bit(const std::string opcode_ext) const;
    uint32_t get_reg_4bit(const std::string reg) const;
    uint32_t get_iflag_1bit(const std::vector<std::string> src2) const;
    uint32_t get_sflag_1bit(const std::string opcode) const;
    uint32_t get_rot_4bit(const std::vector<std::string> src2) const;
    uint32_t get_imm8_8bit(const std::vector<std::string> src2) const;
    uint32_t get_shamt5_5bit(const std::vector<std::string> src2) const;
    uint32_t get_sh_2bit(const std::vector<std::string> src2) const;
    uint32_t get_ibarflag_1bit(const std::vector<std::string> src2) const;

    /* Data Processing Instructions */
    uint32_t _and(std::string opcode, std::vector<std::string> operands);  // AND Rd, Rn, Src2
    uint32_t _eor(std::string opcode, std::vector<std::string> operands);  // EOR Rd, Rn, Src2
    uint32_t _sub(std::string opcode, std::vector<std::string> operands);  // SUB Rd, Rn, Src2
    uint32_t _rsb(std::string opcode, std::vector<std::string> operands);  // RSB Rd, Rn, Src2
    uint32_t _add(std::string opcode, std::vector<std::string> operands);  // ADD Rd, Rn, Src2
    uint32_t _adc(std::string opcode, std::vector<std::string> operands);  // ADC Rd, Rn, Src2
    uint32_t _sbc(std::string opcode, std::vector<std::string> operands);  // ABC Rd, Rn, Src2
    uint32_t _rsc(std::string opcode, std::vector<std::string> operands);  // RSC Rd, Rn, Src2
    uint32_t _tst(std::string opcode, std::vector<std::string> operands);  // TST Rn, Src2
    uint32_t _teq(std::string opcode, std::vector<std::string> operands);  // TEQ Rn, Src2
    uint32_t _cmp(std::string opcode, std::vector<std::string> operands);  // CMP Rn, Src2
    uint32_t _cmn(std::string opcode, std::vector<std::string> operands);  // CMN Rn, Src2
    uint32_t _orr(std::string opcode, std::vector<std::string> operands);  // ORR Rd, Rn, Src2
    uint32_t _mov(std::string opcode, std::vector<std::string> operands);  // MOV Rd, Src2
    uint32_t _lsl(std::string opcode, std::vector<std::string> operands);  // LSL Rd, Rm, Rs/shamt5
    uint32_t _lsr(std::string opcode, std::vector<std::string> operands);  // LSR Rd, Rm, Rs/shamt5
    uint32_t _asr(std::string opcode, std::vector<std::string> operands);  // ASR Rd, Rm, Rs/shamt5
    uint32_t _rrx(std::string opcode, std::vector<std::string> operands);  // RRX Rd, Rm, Rs/shamt5
    uint32_t _ror(std::string opcode, std::vector<std::string> operands);  // ROR Rd, Rm, Rs/shamt5
    uint32_t _bic(std::string opcode, std::vector<std::string> operands);  // BIC Rd, Rn, Src2
    uint32_t _mvn(std::string opcode, std::vector<std::string> operands);  // MVN Rd, Rn, Src2
    uint32_t _mul(std::string opcode, std::vector<std::string> operands);  // MUL Rd, Rn, Rm, (Ra)
    uint32_t _mla(std::string opcode, std::vector<std::string> operands);  // MLA Rd, Rn, Rm, Ra

    /* Memory Instructions*/
    uint32_t _str(std::string opcode, std::vector<std::string> operands);  // STR Rd, [Rn, +-Src2]
    uint32_t _ldr(std::string opcode, std::vector<std::string> operands);  // LDR Rd, [Rn, +-Src2]

    /* Branch Instructions */
    uint32_t _b(std::string opcode, std::vector<std::string> operands);   // B label
    uint32_t _bl(std::string opcode, std::vector<std::string> operands);  // BL label

    /* Unknown Instruction */
    uint32_t _unk(std::string opcode, std::vector<std::string> operands);
};

#endif