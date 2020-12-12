# armv4 assembler for small instruction set

## サポート命令

以下の37命令をサポートする

* データ処理命令
  * AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, LSL, LSR, ASR, RRX, ROR, BIC, MVN
* データ処理命令（乗算）
  * MUL, MLA, UMULL, UMLAL, SMULL, SMLAL
* メモリ命令
  * STR, LDR, STRB, LDRB, STRH, LDRH, LDRSB, LDRSH
* 分岐命令
  * B, BL

## 命令フォーマット

* データ処理命令
  * Type1: \<*Mnemonic*\> Rd, Rn, Src2
    * AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, ORR, BIC, MVN
  * Type2: \<*Mnemonic*\> Rn, Src2
    * TST, TEQ, CMP, CMN
  * Type3: \<*Mnemonic*\> Rd, Src2
    * MOV
  * Type4: \<*Mnemonic*\> Rd, Rm, Rs/shamt5
    * LSL, LSR, ASR, RRX, ROR
* 乗算命令
  * Type5: \<*Mnemonic*\> Rd, Rn, Rm
    * MUL
  * Type6: \<*Mnemonic*\> Rd, Rn, Rm, Ra
    * MLA, UMULL, UMLAL, SMULL, SMLAL
* メモリ命令
  * Type7: \<*Mnemonic*\> Rd, Adr
    * STR, LDR, STRB, LDRB, STRH, LDRH, LDRSB, LDRSH
  * Adr Type
    * [Rn, $\pm$Src2] (offset)
    * [Rn, $\pm$Src2]! (preindex)
    * [Rn], $\pm$Src2 (postindex)
* 分岐命令
  * Type8: \<*Mnemonic*\> label
    * B, BL
