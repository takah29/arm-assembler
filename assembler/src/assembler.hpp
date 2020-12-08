#include <string>
#include <vector>

class Assembler {
   public:
    Assembler();
    ~Assembler();

    uint32_t convert(const std::string asmcode);

   private:
    std::vector<std::string> tokenize(const std::string asmcode);

    uint32_t get_op_2bit(std::string opcode);
    uint32_t get_cond_4bit(std::string opcode);
    uint32_t get_cmd_4bit(std::string opcode);
    uint32_t get_reg_4bit(std::string reg);
    uint32_t get_iflag_1bit(std::string src2);
    uint32_t get_sflag_1bit(std::string opcode);
    uint32_t get_rot_4bit(std::string src2);
    uint32_t get_imm8_8bit(std::string src2);
    uint32_t get_shamt5_5bit(std::string src2);
    uint32_t get_sh_2bit(std::string src2);

    /* Data Processing Instructions */
    uint32_t _and(std::string opcode, std::vector<std::string> operands);
    uint32_t _eor(std::string opcode, std::vector<std::string> operands);
    uint32_t _sub(std::string opcode, std::vector<std::string> operands);
    uint32_t _rsb(std::string opcode, std::vector<std::string> operands);
    uint32_t _add(std::string opcode, std::vector<std::string> operands);
    uint32_t _adc(std::string opcode, std::vector<std::string> operands);
    uint32_t _sbc(std::string opcode, std::vector<std::string> operands);
    uint32_t _rsc(std::string opcode, std::vector<std::string> operands);
    uint32_t _tst(std::string opcode, std::vector<std::string> operands);
    uint32_t _teq(std::string opcode, std::vector<std::string> operands);
    uint32_t _cmp(std::string opcode, std::vector<std::string> operands);
    uint32_t _cmn(std::string opcode, std::vector<std::string> operands);
    uint32_t _orr(std::string opcode, std::vector<std::string> operands);
    uint32_t _mov(std::string opcode, std::vector<std::string> operands);
    uint32_t _lsl(std::string opcode, std::vector<std::string> operands);
    uint32_t _lsr(std::string opcode, std::vector<std::string> operands);
    uint32_t _asr(std::string opcode, std::vector<std::string> operands);
    uint32_t _rrx(std::string opcode, std::vector<std::string> operands);
    uint32_t _ror(std::string opcode, std::vector<std::string> operands);
    uint32_t _bic(std::string opcode, std::vector<std::string> operands);
    uint32_t _mvn(std::string opcode, std::vector<std::string> operands);
    uint32_t _mul(std::string opcode, std::vector<std::string> operands);  // MUL, UMULL, SMULL
    uint32_t _mla(std::string opcode, std::vector<std::string> operands);  // MLA, UMLAL, SMLAL

    /* Memory Instructions*/
    uint32_t _str(std::string opcode, std::vector<std::string> operands);
    uint32_t _ldr(std::string opcode, std::vector<std::string> operands);

    /* Branch Instructions */
    uint32_t _b(std::string opcode, std::vector<std::string> operands);
    uint32_t _bl(std::string opcode, std::vector<std::string> operands);

    /* Unknown Instruction */
    uint32_t _unk(std::string opcode, std::vector<std::string> operands);
};
