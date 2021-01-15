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

## Requirements

* clang 9.0 (C++17)

## Usage

```text
$ make
$ ./assembler test/input/input_testcode.txt -d
main sub r0, r15, r15     -> cond = 1110, op = 00, funct = 000100, rn = 1111, rd = 0000, src2 = 000000001111
add r2, r0, #5            -> cond = 1110, op = 00, funct = 101000, rn = 0000, rd = 0010, src2 = 000000000101
add r3, r0, #12           -> cond = 1110, op = 00, funct = 101000, rn = 0000, rd = 0011, src2 = 000000001100
sub r7, r3, #9            -> cond = 1110, op = 00, funct = 100100, rn = 0011, rd = 0111, src2 = 000000001001
orr r4, r7, r2            -> cond = 1110, op = 00, funct = 011000, rn = 0111, rd = 0100, src2 = 000000000010
and r5, r3, r4            -> cond = 1110, op = 00, funct = 000000, rn = 0011, rd = 0101, src2 = 000000000100
add r5, r5, r4            -> cond = 1110, op = 00, funct = 001000, rn = 0101, rd = 0101, src2 = 000000000100
subs r8, r5, r7           -> cond = 1110, op = 00, funct = 000101, rn = 0101, rd = 1000, src2 = 000000000111
beq end                   -> cond = 0000, op = 10, funct = 10, imm24 = 000000000000000000001100
subs r8, r3, r4           -> cond = 1110, op = 00, funct = 000101, rn = 0011, rd = 1000, src2 = 000000000100
bge around                -> cond = 1010, op = 10, funct = 10, imm24 = 000000000000000000000000
add r5, r0, #0            -> cond = 1110, op = 00, funct = 101000, rn = 0000, rd = 0101, src2 = 000000000000
around subs r8, r7, r2    -> cond = 1110, op = 00, funct = 000101, rn = 0111, rd = 1000, src2 = 000000000010
addlt r7, r5, #1          -> cond = 1011, op = 00, funct = 101000, rn = 0101, rd = 0111, src2 = 000000000001
sub r7, r7, r2            -> cond = 1110, op = 00, funct = 000100, rn = 0111, rd = 0111, src2 = 000000000010
str r7, [r3, #84]         -> cond = 1110, op = 01, funct = 011000, rn = 0011, rd = 0111, src2 = 000001010100
ldr r2, [r0, #96]         -> cond = 1110, op = 01, funct = 011001, rn = 0000, rd = 0010, src2 = 000001100000
add r15, r15, r0          -> cond = 1110, op = 00, funct = 001000, rn = 1111, rd = 1111, src2 = 000000000000
add r2, r0, #14           -> cond = 1110, op = 00, funct = 101000, rn = 0000, rd = 0010, src2 = 000000001110
b end                     -> cond = 1110, op = 10, funct = 10, imm24 = 000000000000000000000001
add r2, r0, #13           -> cond = 1110, op = 00, funct = 101000, rn = 0000, rd = 0010, src2 = 000000001101
add r2, r0, #10           -> cond = 1110, op = 00, funct = 101000, rn = 0000, rd = 0010, src2 = 000000001010
end str r2, [r0, #100]    -> cond = 1110, op = 01, funct = 011000, rn = 0000, rd = 0010, src2 = 000001100100
```

```text
$ cat output.txt
11100000010011110000000000001111
11100010100000000010000000000101
11100010100000000011000000001100
11100010010000110111000000001001
11100001100001110100000000000010
11100000000000110101000000000100
11100000100001010101000000000100
11100000010101011000000000000111
00001010000000000000000000001100
11100000010100111000000000000100
10101010000000000000000000000000
11100010100000000101000000000000
11100000010101111000000000000010
10110010100001010111000000000001
11100000010001110111000000000010
11100101100000110111000001010100
11100101100100000010000001100000
11100000100011111111000000000000
11100010100000000010000000001110
11101010000000000000000000000001
11100010100000000010000000001101
11100010100000000010000000001010
11100101100000000010000001100100
```

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

## References

* [ARMv5 Architecture Reference Manual](https://developer.arm.com/documentation/ddi0100/i)