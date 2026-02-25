#ifndef MOS6502_OPCODES_HEADER
#define MOS6502_OPCODES_HEADER

#include "addressing.h"

#include <stdint.h>

struct mos6502;

// Access
void mos6502_lda(struct mos6502* chip);
void mos6502_sta(struct mos6502* chip);
void mos6502_ldx(struct mos6502* chip);
void mos6502_stx(struct mos6502* chip);
void mos6502_ldy(struct mos6502* chip);
void mos6502_sty(struct mos6502* chip);
// Transfer
void mos6502_tax(struct mos6502* chip);
void mos6502_txa(struct mos6502* chip);
void mos6502_tay(struct mos6502* chip);
void mos6502_tya(struct mos6502* chip);
// Arithmetic
void mos6502_adc(struct mos6502* chip);
void mos6502_sbc(struct mos6502* chip);
void mos6502_inc(struct mos6502* chip);
void mos6502_dec(struct mos6502* chip);
void mos6502_inx(struct mos6502* chip);
void mos6502_dex(struct mos6502* chip);
void mos6502_iny(struct mos6502* chip);
void mos6502_dey(struct mos6502* chip);
// Shift
void mos6502_asl(struct mos6502* chip);
void mos6502_lsr(struct mos6502* chip);
void mos6502_rol(struct mos6502* chip);
void mos6502_ror(struct mos6502* chip);
// Bitwise
void mos6502_ora(struct mos6502* chip);
void mos6502_and(struct mos6502* chip);
void mos6502_eor(struct mos6502* chip);
void mos6502_bit(struct mos6502* chip);
// Compare
void mos6502_cmp(struct mos6502* chip);
void mos6502_cpx(struct mos6502* chip);
void mos6502_cpy(struct mos6502* chip);
// Branch
void mos6502_bcc(struct mos6502* chip);
void mos6502_bcs(struct mos6502* chip);
void mos6502_beq(struct mos6502* chip);
void mos6502_bne(struct mos6502* chip);
void mos6502_bpl(struct mos6502* chip);
void mos6502_bmi(struct mos6502* chip);
void mos6502_bvc(struct mos6502* chip);
void mos6502_bvs(struct mos6502* chip);
// Jump
void mos6502_jmp(struct mos6502* chip);
void mos6502_jsr(struct mos6502* chip);
void mos6502_rts(struct mos6502* chip);
void mos6502_brk(struct mos6502* chip);
void mos6502_rti(struct mos6502* chip);
// Stack
void mos6502_pha(struct mos6502* chip);
void mos6502_pla(struct mos6502* chip);
void mos6502_php(struct mos6502* chip);
void mos6502_plp(struct mos6502* chip);
void mos6502_txs(struct mos6502* chip);
void mos6502_tsx(struct mos6502* chip);
// Flags
void mos6502_clc(struct mos6502* chip);
void mos6502_sec(struct mos6502* chip);
void mos6502_cli(struct mos6502* chip);
void mos6502_sei(struct mos6502* chip);
void mos6502_cld(struct mos6502* chip);
void mos6502_sed(struct mos6502* chip);
void mos6502_clv(struct mos6502* chip);
// Other
void mos6502_nop(struct mos6502* chip);
// Illegal
void mos6502_illegal_nop(struct mos6502* chip);
void mos6502_illegal_shy(struct mos6502* chip);
void mos6502_illegal_stp(struct mos6502* chip);
void mos6502_illegal_shx(struct mos6502* chip);
void mos6502_illegal_slo(struct mos6502* chip);
void mos6502_illegal_anc(struct mos6502* chip);
void mos6502_illegal_rla(struct mos6502* chip);
void mos6502_illegal_sre(struct mos6502* chip);
void mos6502_illegal_alr(struct mos6502* chip);
void mos6502_illegal_rra(struct mos6502* chip);
void mos6502_illegal_arr(struct mos6502* chip);
void mos6502_illegal_sax(struct mos6502* chip);
void mos6502_illegal_xaa(struct mos6502* chip);
void mos6502_illegal_ahx(struct mos6502* chip);
void mos6502_illegal_tas(struct mos6502* chip);
void mos6502_illegal_lax(struct mos6502* chip);
void mos6502_illegal_las(struct mos6502* chip);
void mos6502_illegal_dcp(struct mos6502* chip);
void mos6502_illegal_axs(struct mos6502* chip);
void mos6502_illegal_isc(struct mos6502* chip);
void mos6502_illegal_sbc(struct mos6502* chip);

// Access
#define MOS6502_LDA 0x00
#define MOS6502_STA 0x01
#define MOS6502_LDX 0x02
#define MOS6502_STX 0x03
#define MOS6502_LDY 0x04
#define MOS6502_STY 0x05
// Transfer
#define MOS6502_TAX 0x06
#define MOS6502_TXA 0x07
#define MOS6502_TAY 0x08
#define MOS6502_TYA 0x09
// Arithmetic
#define MOS6502_ADC 0x0a
#define MOS6502_SBC 0x0b
#define MOS6502_INC 0x0c
#define MOS6502_DEC 0x0d
#define MOS6502_INX 0x0e
#define MOS6502_DEX 0x0f
#define MOS6502_INY 0x10
#define MOS6502_DEY 0x11
// Shift
#define MOS6502_ASL 0x12
#define MOS6502_LSR 0x13
#define MOS6502_ROL 0x14
#define MOS6502_ROR 0x15
// Bitwise
#define MOS6502_ORA 0x16
#define MOS6502_AND 0x17
#define MOS6502_EOR 0x18
#define MOS6502_BIT 0x19
// Compare
#define MOS6502_CMP 0x1a
#define MOS6502_CPX 0x1b
#define MOS6502_CPY 0x1c
// Branch 
#define MOS6502_BCC 0x1d
#define MOS6502_BCS 0x1e
#define MOS6502_BEQ 0x1f
#define MOS6502_BNE 0x20
#define MOS6502_BPL 0x21
#define MOS6502_BMI 0x22
#define MOS6502_BVC 0x23
#define MOS6502_BVS 0x24
// Jump
#define MOS6502_JMP 0x25
#define MOS6502_JSR 0x26
#define MOS6502_RTS 0x27
#define MOS6502_BRK 0x28
#define MOS6502_RTI 0x29
// Stack
#define MOS6502_PHA 0x2a
#define MOS6502_PLA 0x2b
#define MOS6502_PHP 0x2c
#define MOS6502_PLP 0x2d
#define MOS6502_TXS 0x2e
#define MOS6502_TSX 0x2f
// Flags
#define MOS6502_CLC 0x30
#define MOS6502_SEC 0x31
#define MOS6502_CLI 0x32
#define MOS6502_SEI 0x33
#define MOS6502_CLD 0x34
#define MOS6502_SED 0x35
#define MOS6502_CLV 0x36
// Other
#define MOS6502_NOP 0x37
// Illegal
#define MOS6502_ILLEGAL_NOP 0x38
#define MOS6502_ILLEGAL_SHY 0x39
#define MOS6502_ILLEGAL_STP 0x3a
#define MOS6502_ILLEGAL_SHX 0x3b
#define MOS6502_ILLEGAL_SLO 0x3c
#define MOS6502_ILLEGAL_ANC 0x3d
#define MOS6502_ILLEGAL_RLA 0x3e
#define MOS6502_ILLEGAL_SRE 0x3f
#define MOS6502_ILLEGAL_ALR 0x40
#define MOS6502_ILLEGAL_RRA 0x41
#define MOS6502_ILLEGAL_ARR 0x42
#define MOS6502_ILLEGAL_SAX 0x43
#define MOS6502_ILLEGAL_XAA 0x44
#define MOS6502_ILLEGAL_AHX 0x45
#define MOS6502_ILLEGAL_TAS 0x46
#define MOS6502_ILLEGAL_LAX 0x47
#define MOS6502_ILLEGAL_LAS 0x48
#define MOS6502_ILLEGAL_DCP 0x49
#define MOS6502_ILLEGAL_AXS 0x4a
#define MOS6502_ILLEGAL_ISC 0x4b
#define MOS6502_ILLEGAL_SBC 0x4c

struct mos6502_opcode{
    void (*handler)(struct mos6502*);
    uint16_t instruction : 7;
    uint16_t address_mode : 4;
    uint16_t cycles : 4;
};

static const struct mos6502_opcode mos6502_opcodes[256] = {
    // Access
    // LDA
    [0xa9] = {mos6502_lda, MOS6502_LDA, MOS6502_IMMEDIATE, 2},
    [0xa5] = {mos6502_lda, MOS6502_LDA, MOS6502_ZEROPAGE,  3},
    [0xb5] = {mos6502_lda, MOS6502_LDA, MOS6502_ZEROPAGEX, 4},
    [0xad] = {mos6502_lda, MOS6502_LDA, MOS6502_ABSOLUTE,  4},
    [0xbd] = {mos6502_lda, MOS6502_LDA, MOS6502_ABSOLUTEX, 4},
    [0xb9] = {mos6502_lda, MOS6502_LDA, MOS6502_ABSOLUTEY, 4},
    [0xa1] = {mos6502_lda, MOS6502_LDA, MOS6502_INDIRECTX, 6},
    [0xb1] = {mos6502_lda, MOS6502_LDA, MOS6502_INDIRECTY, 5},
    // STA
    [0x85] = {mos6502_sta, MOS6502_STA, MOS6502_ZEROPAGE,  3},
    [0x95] = {mos6502_sta, MOS6502_STA, MOS6502_ZEROPAGEX, 4},
    [0x8d] = {mos6502_sta, MOS6502_STA, MOS6502_ABSOLUTE,  4},
    [0x9d] = {mos6502_sta, MOS6502_STA, MOS6502_ABSOLUTEX, 5},
    [0x99] = {mos6502_sta, MOS6502_STA, MOS6502_ABSOLUTEY, 5},
    [0x81] = {mos6502_sta, MOS6502_STA, MOS6502_INDIRECTX, 6},
    [0x91] = {mos6502_sta, MOS6502_STA, MOS6502_INDIRECTY, 6},
    // LDX
    [0xa2] = {mos6502_ldx, MOS6502_LDX, MOS6502_IMMEDIATE, 2},
    [0xa6] = {mos6502_ldx, MOS6502_LDX, MOS6502_ZEROPAGE,  3},
    [0xb6] = {mos6502_ldx, MOS6502_LDX, MOS6502_ZEROPAGEY, 4},
    [0xae] = {mos6502_ldx, MOS6502_LDX, MOS6502_ABSOLUTE,  4},
    [0xbe] = {mos6502_ldx, MOS6502_LDX, MOS6502_ABSOLUTEY, 4},
    // STX
    [0x86] = {mos6502_stx, MOS6502_STX, MOS6502_ZEROPAGE,  3},
    [0x96] = {mos6502_stx, MOS6502_STX, MOS6502_ZEROPAGEY, 4},
    [0x8e] = {mos6502_stx, MOS6502_STX, MOS6502_ABSOLUTE,  4},
    // LDY
    [0xa0] = {mos6502_ldy, MOS6502_LDY, MOS6502_IMMEDIATE, 2},
    [0xa4] = {mos6502_ldy, MOS6502_LDY, MOS6502_ZEROPAGE,  3},
    [0xb4] = {mos6502_ldy, MOS6502_LDY, MOS6502_ZEROPAGEX, 4},
    [0xac] = {mos6502_ldy, MOS6502_LDY, MOS6502_ABSOLUTE,  4},
    [0xbc] = {mos6502_ldy, MOS6502_LDY, MOS6502_ABSOLUTEX, 4},
    // STY
    [0x84] = {mos6502_sty, MOS6502_STY, MOS6502_ZEROPAGE,  3},
    [0x94] = {mos6502_sty, MOS6502_STY, MOS6502_ZEROPAGEX, 4},
    [0x8c] = {mos6502_sty, MOS6502_STY, MOS6502_ABSOLUTE,  4},

    // Transfer
    [0xaa] = {mos6502_tax, MOS6502_TAX, MOS6502_IMPLICIT, 2},
    [0x8a] = {mos6502_txa, MOS6502_TXA, MOS6502_IMPLICIT, 2},
    [0xa8] = {mos6502_tay, MOS6502_TAY, MOS6502_IMPLICIT, 2},
    [0x98] = {mos6502_tya, MOS6502_TYA, MOS6502_IMPLICIT, 2},

    // Arithmetic
    // ADC
    [0x69] = {mos6502_adc, MOS6502_ADC, MOS6502_IMMEDIATE, 2},
    [0x65] = {mos6502_adc, MOS6502_ADC, MOS6502_ZEROPAGE,  3},
    [0x75] = {mos6502_adc, MOS6502_ADC, MOS6502_ZEROPAGEX, 4},
    [0x6d] = {mos6502_adc, MOS6502_ADC, MOS6502_ABSOLUTE,  4},
    [0x7d] = {mos6502_adc, MOS6502_ADC, MOS6502_ABSOLUTEX, 4},
    [0x79] = {mos6502_adc, MOS6502_ADC, MOS6502_ABSOLUTEY, 4},
    [0x61] = {mos6502_adc, MOS6502_ADC, MOS6502_INDIRECTX, 6},
    [0x71] = {mos6502_adc, MOS6502_ADC, MOS6502_INDIRECTY, 5},
    // SBC
    [0xe9] = {mos6502_sbc, MOS6502_SBC, MOS6502_IMMEDIATE, 2},
    [0xe5] = {mos6502_sbc, MOS6502_SBC, MOS6502_ZEROPAGE,  3},
    [0xf5] = {mos6502_sbc, MOS6502_SBC, MOS6502_ZEROPAGEX, 4},
    [0xed] = {mos6502_sbc, MOS6502_SBC, MOS6502_ABSOLUTE,  4},
    [0xfd] = {mos6502_sbc, MOS6502_SBC, MOS6502_ABSOLUTEX, 4},
    [0xf9] = {mos6502_sbc, MOS6502_SBC, MOS6502_ABSOLUTEY, 4},
    [0xe1] = {mos6502_sbc, MOS6502_SBC, MOS6502_INDIRECTX, 6},
    [0xf1] = {mos6502_sbc, MOS6502_SBC, MOS6502_INDIRECTY, 5},
    // INC / DEC
    [0xe6] = {mos6502_inc, MOS6502_INC, MOS6502_ZEROPAGE,  5},
    [0xf6] = {mos6502_inc, MOS6502_INC, MOS6502_ZEROPAGEX, 6},
    [0xee] = {mos6502_inc, MOS6502_INC, MOS6502_ABSOLUTE,  6},
    [0xfe] = {mos6502_inc, MOS6502_INC, MOS6502_ABSOLUTEX, 7},
    [0xc6] = {mos6502_dec, MOS6502_DEC, MOS6502_ZEROPAGE,  5},
    [0xd6] = {mos6502_dec, MOS6502_DEC, MOS6502_ZEROPAGEX, 6},
    [0xce] = {mos6502_dec, MOS6502_DEC, MOS6502_ABSOLUTE,  6},
    [0xde] = {mos6502_dec, MOS6502_DEC, MOS6502_ABSOLUTEX, 7},
    // Register Increments
    [0xe8] = {mos6502_inx, MOS6502_INX, MOS6502_IMPLICIT, 2},
    [0xca] = {mos6502_dex, MOS6502_DEX, MOS6502_IMPLICIT, 2},
    [0xc8] = {mos6502_iny, MOS6502_INY, MOS6502_IMPLICIT, 2},
    [0x88] = {mos6502_dey, MOS6502_DEY, MOS6502_IMPLICIT, 2},

    // Shifts
    // ASL
    [0x0a] = {mos6502_asl, MOS6502_ASL, MOS6502_ACCUMULATOR, 2},
    [0x06] = {mos6502_asl, MOS6502_ASL, MOS6502_ZEROPAGE,    5},
    [0x16] = {mos6502_asl, MOS6502_ASL, MOS6502_ZEROPAGEX,   6},
    [0x0e] = {mos6502_asl, MOS6502_ASL, MOS6502_ABSOLUTE,    6},
    [0x1e] = {mos6502_asl, MOS6502_ASL, MOS6502_ABSOLUTEX,   7},
    // LSR
    [0x4a] = {mos6502_lsr, MOS6502_LSR, MOS6502_ACCUMULATOR, 2},
    [0x46] = {mos6502_lsr, MOS6502_LSR, MOS6502_ZEROPAGE,    5},
    [0x56] = {mos6502_lsr, MOS6502_LSR, MOS6502_ZEROPAGEX,   6},
    [0x4e] = {mos6502_lsr, MOS6502_LSR, MOS6502_ABSOLUTE,    6},
    [0x5e] = {mos6502_lsr, MOS6502_LSR, MOS6502_ABSOLUTEX,   7},
    // ROL
    [0x2a] = {mos6502_rol, MOS6502_ROL, MOS6502_ACCUMULATOR, 2},
    [0x26] = {mos6502_rol, MOS6502_ROL, MOS6502_ZEROPAGE,    5},
    [0x36] = {mos6502_rol, MOS6502_ROL, MOS6502_ZEROPAGEX,   6},
    [0x2e] = {mos6502_rol, MOS6502_ROL, MOS6502_ABSOLUTE,    6},
    [0x3e] = {mos6502_rol, MOS6502_ROL, MOS6502_ABSOLUTEX,   7},
    // ROR
    [0x6a] = {mos6502_ror, MOS6502_ROR, MOS6502_ACCUMULATOR, 2},
    [0x66] = {mos6502_ror, MOS6502_ROR, MOS6502_ZEROPAGE,    5},
    [0x76] = {mos6502_ror, MOS6502_ROR, MOS6502_ZEROPAGEX,   6},
    [0x6e] = {mos6502_ror, MOS6502_ROR, MOS6502_ABSOLUTE,    6},
    [0x7e] = {mos6502_ror, MOS6502_ROR, MOS6502_ABSOLUTEX,   7},

    // Bitwise / Logic
    [0x29] = {mos6502_and, MOS6502_AND, MOS6502_IMMEDIATE, 2},
    [0x25] = {mos6502_and, MOS6502_AND, MOS6502_ZEROPAGE,  3},
    [0x35] = {mos6502_and, MOS6502_AND, MOS6502_ZEROPAGEX, 4},
    [0x2d] = {mos6502_and, MOS6502_AND, MOS6502_ABSOLUTE,  4},
    [0x3d] = {mos6502_and, MOS6502_AND, MOS6502_ABSOLUTEX, 4},
    [0x39] = {mos6502_and, MOS6502_AND, MOS6502_ABSOLUTEY, 4},
    [0x21] = {mos6502_and, MOS6502_AND, MOS6502_INDIRECTX, 6},
    [0x31] = {mos6502_and, MOS6502_AND, MOS6502_INDIRECTY, 5},
    
    [0x09] = {mos6502_ora, MOS6502_ORA, MOS6502_IMMEDIATE, 2},
    [0x05] = {mos6502_ora, MOS6502_ORA, MOS6502_ZEROPAGE,  3},
    [0x15] = {mos6502_ora, MOS6502_ORA, MOS6502_ZEROPAGEX, 4},
    [0x0d] = {mos6502_ora, MOS6502_ORA, MOS6502_ABSOLUTE,  4},
    [0x1d] = {mos6502_ora, MOS6502_ORA, MOS6502_ABSOLUTEX, 4},
    [0x19] = {mos6502_ora, MOS6502_ORA, MOS6502_ABSOLUTEY, 4},
    [0x01] = {mos6502_ora, MOS6502_ORA, MOS6502_INDIRECTX, 6},
    [0x11] = {mos6502_ora, MOS6502_ORA, MOS6502_INDIRECTY, 5},

    [0x49] = {mos6502_eor, MOS6502_EOR, MOS6502_IMMEDIATE, 2},
    [0x45] = {mos6502_eor, MOS6502_EOR, MOS6502_ZEROPAGE,  3},
    [0x55] = {mos6502_eor, MOS6502_EOR, MOS6502_ZEROPAGEX, 4},
    [0x4d] = {mos6502_eor, MOS6502_EOR, MOS6502_ABSOLUTE,  4},
    [0x5d] = {mos6502_eor, MOS6502_EOR, MOS6502_ABSOLUTEX, 4},
    [0x59] = {mos6502_eor, MOS6502_EOR, MOS6502_ABSOLUTEY, 4},
    [0x41] = {mos6502_eor, MOS6502_EOR, MOS6502_INDIRECTX, 6},
    [0x51] = {mos6502_eor, MOS6502_EOR, MOS6502_INDIRECTY, 5},

    [0x24] = {mos6502_bit, MOS6502_BIT, MOS6502_ZEROPAGE, 3},
    [0x2c] = {mos6502_bit, MOS6502_BIT, MOS6502_ABSOLUTE, 4},

    // Compare
    [0xc9] = {mos6502_cmp, MOS6502_CMP, MOS6502_IMMEDIATE, 2},
    [0xc5] = {mos6502_cmp, MOS6502_CMP, MOS6502_ZEROPAGE,  3},
    [0xd5] = {mos6502_cmp, MOS6502_CMP, MOS6502_ZEROPAGEX, 4},
    [0xcd] = {mos6502_cmp, MOS6502_CMP, MOS6502_ABSOLUTE,  4},
    [0xdd] = {mos6502_cmp, MOS6502_CMP, MOS6502_ABSOLUTEX, 4},
    [0xd9] = {mos6502_cmp, MOS6502_CMP, MOS6502_ABSOLUTEY, 4},
    [0xc1] = {mos6502_cmp, MOS6502_CMP, MOS6502_INDIRECTX, 6},
    [0xd1] = {mos6502_cmp, MOS6502_CMP, MOS6502_INDIRECTY, 5},
    
    [0xe0] = {mos6502_cpx, MOS6502_CPX, MOS6502_IMMEDIATE, 2},
    [0xe4] = {mos6502_cpx, MOS6502_CPX, MOS6502_ZEROPAGE,  3},
    [0xec] = {mos6502_cpx, MOS6502_CPX, MOS6502_ABSOLUTE,  4},
    
    [0xc0] = {mos6502_cpy, MOS6502_CPY, MOS6502_IMMEDIATE, 2},
    [0xc4] = {mos6502_cpy, MOS6502_CPY, MOS6502_ZEROPAGE,  3},
    [0xcc] = {mos6502_cpy, MOS6502_CPY, MOS6502_ABSOLUTE,  4},

    // Branching
    [0x90] = {mos6502_bcc, MOS6502_BCC, MOS6502_RELATIVE, 2},
    [0xb0] = {mos6502_bcs, MOS6502_BCS, MOS6502_RELATIVE, 2},
    [0xf0] = {mos6502_beq, MOS6502_BEQ, MOS6502_RELATIVE, 2},
    [0xd0] = {mos6502_bne, MOS6502_BNE, MOS6502_RELATIVE, 2},
    [0x10] = {mos6502_bpl, MOS6502_BPL, MOS6502_RELATIVE, 2},
    [0x30] = {mos6502_bmi, MOS6502_BMI, MOS6502_RELATIVE, 2},
    [0x50] = {mos6502_bvc, MOS6502_BVC, MOS6502_RELATIVE, 2},
    [0x70] = {mos6502_bvs, MOS6502_BVS, MOS6502_RELATIVE, 2},

    // Jump / Control
    [0x4c] = {mos6502_jmp, MOS6502_JMP, MOS6502_ABSOLUTE, 3},
    [0x6c] = {mos6502_jmp, MOS6502_JMP, MOS6502_INDIRECT, 5},
    [0x20] = {mos6502_jsr, MOS6502_JSR, MOS6502_ABSOLUTE, 6},
    [0x60] = {mos6502_rts, MOS6502_RTS, MOS6502_IMPLICIT, 6},
    [0x00] = {mos6502_brk, MOS6502_BRK, MOS6502_IMPLICIT, 7},
    [0x40] = {mos6502_rti, MOS6502_RTI, MOS6502_IMPLICIT, 6},

    // Stack
    [0x48] = {mos6502_pha, MOS6502_PHA, MOS6502_IMPLICIT, 3},
    [0x68] = {mos6502_pla, MOS6502_PLA, MOS6502_IMPLICIT, 4},
    [0x08] = {mos6502_php, MOS6502_PHP, MOS6502_IMPLICIT, 3},
    [0x28] = {mos6502_plp, MOS6502_PLP, MOS6502_IMPLICIT, 4},
    [0x9a] = {mos6502_txs, MOS6502_TXS, MOS6502_IMPLICIT, 2},
    [0xba] = {mos6502_tsx, MOS6502_TSX, MOS6502_IMPLICIT, 2},

    // Flags
    [0x18] = {mos6502_clc, MOS6502_CLC, MOS6502_IMPLICIT, 2},
    [0x38] = {mos6502_sec, MOS6502_SEC, MOS6502_IMPLICIT, 2},
    [0x58] = {mos6502_cli, MOS6502_CLI, MOS6502_IMPLICIT, 2},
    [0x78] = {mos6502_sei, MOS6502_SEI, MOS6502_IMPLICIT, 2},
    [0xd8] = {mos6502_cld, MOS6502_CLD, MOS6502_IMPLICIT, 2},
    [0xf8] = {mos6502_sed, MOS6502_SED, MOS6502_IMPLICIT, 2},
    [0xb8] = {mos6502_clv, MOS6502_CLV, MOS6502_IMPLICIT, 2},

    // NOP
    [0xea] = {mos6502_nop, MOS6502_NOP, MOS6502_IMPLICIT, 2},

    // Illegal
    // NOP (Illegal variants)
    [0x04] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGE,  2},
    [0x0c] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ABSOLUTE,  2},
    [0x14] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGEX, 2},
    [0x1c] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ABSOLUTEX, 2},
    [0x34] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGEX, 2},
    [0x3c] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ABSOLUTEX, 2},
    [0x44] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGE,  2},
    [0x54] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGEX, 2},
    [0x5c] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ABSOLUTEX, 2},
    [0x64] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGE,  2},
    [0x74] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGEX, 2},
    [0x7c] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ABSOLUTEX, 2},
    [0x80] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMMEDIATE, 2},
    [0xd4] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGEX, 2},
    [0xdc] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ABSOLUTEX, 2},
    [0xf4] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ZEROPAGEX, 2},
    [0xfc] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_ABSOLUTEX, 2},
    [0x82] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMMEDIATE, 2},
    [0x89] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMMEDIATE, 2},
    [0xc2] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMMEDIATE, 2},
    [0xe2] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMMEDIATE, 2},
    [0x1a] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMPLICIT,  2},
    [0x3a] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMPLICIT,  2},
    [0x5a] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMPLICIT,  2},
    [0x7a] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMPLICIT,  2},
    [0xda] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMPLICIT,  2},
    [0xfa] = {mos6502_illegal_nop, MOS6502_ILLEGAL_NOP, MOS6502_IMPLICIT,  2},
    // SHY / SHX
    [0x9c] = {mos6502_illegal_shy, MOS6502_ILLEGAL_SHY, MOS6502_ABSOLUTEX, 5}, 
    [0x9e] = {mos6502_illegal_shx, MOS6502_ILLEGAL_SHX, MOS6502_ABSOLUTEY, 5}, 
    // STP (Halt/Kil)
    [0x02] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x12] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x22] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x32] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x42] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x52] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x62] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x72] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0x92] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0xb2] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0xd2] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    [0xf2] = {mos6502_illegal_stp, MOS6502_ILLEGAL_STP, MOS6502_IMPLICIT, 0},
    // SLO (ASL + ORA)
    [0x03] = {mos6502_illegal_slo, MOS6502_ILLEGAL_SLO, MOS6502_INDIRECTX, 8}, 
    [0x07] = {mos6502_illegal_slo, MOS6502_ILLEGAL_SLO, MOS6502_ZEROPAGE,  5}, 
    [0x0f] = {mos6502_illegal_slo, MOS6502_ILLEGAL_SLO, MOS6502_ABSOLUTE,  6}, 
    [0x13] = {mos6502_illegal_slo, MOS6502_ILLEGAL_SLO, MOS6502_INDIRECTY, 8}, 
    [0x17] = {mos6502_illegal_slo, MOS6502_ILLEGAL_SLO, MOS6502_ZEROPAGEX, 6}, 
    [0x1b] = {mos6502_illegal_slo, MOS6502_ILLEGAL_SLO, MOS6502_ABSOLUTEY, 7}, 
    [0x1f] = {mos6502_illegal_slo, MOS6502_ILLEGAL_SLO, MOS6502_ABSOLUTEX, 7}, 
    // ANC
    [0x0b] = {mos6502_illegal_anc, MOS6502_ILLEGAL_ANC, MOS6502_IMMEDIATE, 2}, 
    [0x2b] = {mos6502_illegal_anc, MOS6502_ILLEGAL_ANC, MOS6502_IMMEDIATE, 2}, 
    // RLA (ROL + AND)
    [0x23] = {mos6502_illegal_rla, MOS6502_ILLEGAL_RLA, MOS6502_INDIRECTX, 8}, 
    [0x27] = {mos6502_illegal_rla, MOS6502_ILLEGAL_RLA, MOS6502_ZEROPAGE,  5}, 
    [0x2f] = {mos6502_illegal_rla, MOS6502_ILLEGAL_RLA, MOS6502_ABSOLUTE,  6}, 
    [0x33] = {mos6502_illegal_rla, MOS6502_ILLEGAL_RLA, MOS6502_INDIRECTY, 8}, 
    [0x37] = {mos6502_illegal_rla, MOS6502_ILLEGAL_RLA, MOS6502_ZEROPAGEX, 6}, 
    [0x3b] = {mos6502_illegal_rla, MOS6502_ILLEGAL_RLA, MOS6502_ABSOLUTEY, 7}, 
    [0x3f] = {mos6502_illegal_rla, MOS6502_ILLEGAL_RLA, MOS6502_ABSOLUTEX, 7}, 
    // SRE (LSR + EOR)
    [0x43] = {mos6502_illegal_sre, MOS6502_ILLEGAL_SRE, MOS6502_INDIRECTX, 8}, 
    [0x47] = {mos6502_illegal_sre, MOS6502_ILLEGAL_SRE, MOS6502_ZEROPAGE,  5}, 
    [0x4f] = {mos6502_illegal_sre, MOS6502_ILLEGAL_SRE, MOS6502_ABSOLUTE,  6}, 
    [0x53] = {mos6502_illegal_sre, MOS6502_ILLEGAL_SRE, MOS6502_INDIRECTY, 8}, 
    [0x57] = {mos6502_illegal_sre, MOS6502_ILLEGAL_SRE, MOS6502_ZEROPAGEX, 6}, 
    [0x5b] = {mos6502_illegal_sre, MOS6502_ILLEGAL_SRE, MOS6502_ABSOLUTEY, 7}, 
    [0x5f] = {mos6502_illegal_sre, MOS6502_ILLEGAL_SRE, MOS6502_ABSOLUTEX, 7}, 
    // ALR (AND + LSR)
    [0x4b] = {mos6502_illegal_alr, MOS6502_ILLEGAL_ALR, MOS6502_IMMEDIATE, 2}, 
    // RRA (ROR + ADC)
    [0x63] = {mos6502_illegal_rra, MOS6502_ILLEGAL_RRA, MOS6502_INDIRECTX, 8}, 
    [0x67] = {mos6502_illegal_rra, MOS6502_ILLEGAL_RRA, MOS6502_ZEROPAGE,  5}, 
    [0x6f] = {mos6502_illegal_rra, MOS6502_ILLEGAL_RRA, MOS6502_ABSOLUTE,  6}, 
    [0x73] = {mos6502_illegal_rra, MOS6502_ILLEGAL_RRA, MOS6502_INDIRECTY, 8}, 
    [0x77] = {mos6502_illegal_rra, MOS6502_ILLEGAL_RRA, MOS6502_ZEROPAGEX, 6}, 
    [0x7b] = {mos6502_illegal_rra, MOS6502_ILLEGAL_RRA, MOS6502_ABSOLUTEY, 7}, 
    [0x7f] = {mos6502_illegal_rra, MOS6502_ILLEGAL_RRA, MOS6502_ABSOLUTEX, 7},
    // ARR (AND + ROR)
    [0x6b] = {mos6502_illegal_arr, MOS6502_ILLEGAL_ARR, MOS6502_IMMEDIATE, 2}, 
    // SAX (A AND X -> M)
    [0x83] = {mos6502_illegal_sax, MOS6502_ILLEGAL_SAX, MOS6502_INDIRECTX, 6}, 
    [0x87] = {mos6502_illegal_sax, MOS6502_ILLEGAL_SAX, MOS6502_ZEROPAGE,  3}, 
    [0x8f] = {mos6502_illegal_sax, MOS6502_ILLEGAL_SAX, MOS6502_ABSOLUTE,  4}, 
    [0x97] = {mos6502_illegal_sax, MOS6502_ILLEGAL_SAX, MOS6502_ZEROPAGEY, 4}, 
    // XAA / AHX / TAS
    [0x8b] = {mos6502_illegal_xaa, MOS6502_ILLEGAL_XAA, MOS6502_IMMEDIATE, 2}, // Note: No confirmation on the cycle count
    [0x93] = {mos6502_illegal_ahx, MOS6502_ILLEGAL_AHX, MOS6502_INDIRECTY, 6}, // Note: No confirmation on the cycle count
    [0x9f] = {mos6502_illegal_ahx, MOS6502_ILLEGAL_AHX, MOS6502_ABSOLUTEY, 5}, // Note: No confirmation on the cycle count
    [0x9b] = {mos6502_illegal_tas, MOS6502_ILLEGAL_TAS, MOS6502_ABSOLUTEY, 5}, // Note: No confirmation on the cycle count
    // LAX (LDA + LDX)
    [0xa3] = {mos6502_illegal_lax, MOS6502_ILLEGAL_LAX, MOS6502_INDIRECTX, 6}, 
    [0xa7] = {mos6502_illegal_lax, MOS6502_ILLEGAL_LAX, MOS6502_ZEROPAGE,  3}, 
    [0xab] = {mos6502_illegal_lax, MOS6502_ILLEGAL_LAX, MOS6502_IMMEDIATE, 2}, // Note: No confirmation on the cycle count
    [0xaf] = {mos6502_illegal_lax, MOS6502_ILLEGAL_LAX, MOS6502_ABSOLUTE,  4}, 
    [0xb3] = {mos6502_illegal_lax, MOS6502_ILLEGAL_LAX, MOS6502_INDIRECTY, 5}, // Note: No confirmation on the cycle count
    [0xb7] = {mos6502_illegal_lax, MOS6502_ILLEGAL_LAX, MOS6502_ZEROPAGEY, 4}, 
    [0xbf] = {mos6502_illegal_lax, MOS6502_ILLEGAL_LAX, MOS6502_ABSOLUTEY, 4}, // Note: No confirmation on the cycle count
    // LAS
    [0xbb] = {mos6502_illegal_las, MOS6502_ILLEGAL_LAS, MOS6502_ABSOLUTEY, 4}, // Note: No confirmation on the cycle count
    // DCP (DEC + CMP)
    [0xc3] = {mos6502_illegal_dcp, MOS6502_ILLEGAL_DCP, MOS6502_INDIRECTX, 8}, 
    [0xc7] = {mos6502_illegal_dcp, MOS6502_ILLEGAL_DCP, MOS6502_ZEROPAGE,  5}, 
    [0xcf] = {mos6502_illegal_dcp, MOS6502_ILLEGAL_DCP, MOS6502_ABSOLUTE,  6}, 
    [0xd3] = {mos6502_illegal_dcp, MOS6502_ILLEGAL_DCP, MOS6502_INDIRECTY, 8}, 
    [0xd7] = {mos6502_illegal_dcp, MOS6502_ILLEGAL_DCP, MOS6502_ZEROPAGEX, 6}, 
    [0xdb] = {mos6502_illegal_dcp, MOS6502_ILLEGAL_DCP, MOS6502_ABSOLUTEY, 7}, 
    [0xdf] = {mos6502_illegal_dcp, MOS6502_ILLEGAL_DCP, MOS6502_ABSOLUTEX, 7},
    // AXS
    [0xcb] = {mos6502_illegal_axs, MOS6502_ILLEGAL_AXS, MOS6502_IMMEDIATE, 2}, 
    // ISC (INC + SBC)
    [0xe3] = {mos6502_illegal_isc, MOS6502_ILLEGAL_ISC, MOS6502_INDIRECTX, 8}, 
    [0xe7] = {mos6502_illegal_isc, MOS6502_ILLEGAL_ISC, MOS6502_ZEROPAGE,  5}, 
    [0xef] = {mos6502_illegal_isc, MOS6502_ILLEGAL_ISC, MOS6502_ABSOLUTE,  6}, 
    [0xf3] = {mos6502_illegal_isc, MOS6502_ILLEGAL_ISC, MOS6502_INDIRECTY, 8}, 
    [0xf7] = {mos6502_illegal_isc, MOS6502_ILLEGAL_ISC, MOS6502_ZEROPAGEX, 6}, 
    [0xfb] = {mos6502_illegal_isc, MOS6502_ILLEGAL_ISC, MOS6502_ABSOLUTEY, 7}, 
    [0xff] = {mos6502_illegal_isc, MOS6502_ILLEGAL_ISC, MOS6502_ABSOLUTEX, 7},
    // SBC (Illegal Duplicate)
    [0xeb] = {mos6502_illegal_sbc, MOS6502_ILLEGAL_SBC, MOS6502_IMMEDIATE, 2},
};

#endif