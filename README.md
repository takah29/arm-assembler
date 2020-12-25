# armv4 assembler

## Support Instructions

* Data Processing
  * AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, LSL, LSR, ASR, RRX, ROR, BIC, MVN
* Mulitiplication
  * MUL, MLA, UMULL, UMLAL, SMULL, SMLAL
* Memory
  * STR, LDR, STRB, LDRB, STRH, LDRH, LDRSB, LDRSH
* Branch
  * B, BL

## Instruction Format

* Data Processing
  * Type1: *Opcode* Rd, Rn, Src2
    * AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, ORR, BIC, MVN
  * Type2: *Opcode* Rn, Src2
    * TST, TEQ, CMP, CMN
  * Type3: *Opcode* Rd, Src2
    * MOV
  * Type4: *Opcode* Rd, Rm, Rs/shamt5
    * LSL, LSR, ASR, RRX, ROR
* Multiplication
  * Type5: *Opcode* Rd, Rn, Rm
    * MUL
  * Type6: *Opcode* Rd, Rn, Rm, Ra
    * MLA, UMULL, UMLAL, SMULL, SMLAL
* Memory
  * Type7: *Opcode* Rd, [Rn, &plusmn;Src2]
    * STR, LDR, STRB, LDRB, STRH, LDRH, LDRSB, LDRSH
  * IdxMode
    * [Rn, &plusmn;Src2] (offset)
    * [Rn, &plusmn;Src2]! (preindex)
    * [Rn], &plusmn;Src2 (postindex)
* Branch
  * Type8: *Opcode* label
    * B, BL
