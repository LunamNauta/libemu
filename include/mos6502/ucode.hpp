#ifndef LIBEMU_MOS6502_UCODE_HEADER
#define LIBEMU_MOS6502_UCODE_HEADER

#include <cstdint>

namespace libemu::mos6502{

// TODO: After dummy reads, run command?

// Timing logic: https://www.zimmers.net/anonftp/pub/cbm/documents/chipdata/64doc
// Instructions: https://www.nesdev.org/wiki/Instruction_reference

#define MOS6502_ACCUMULATOR(cmd) ucode::ACCUMULATOR, ucode::READ_VALUE,  cmd
#define MOS6502_IMPLIED(cmd)     ucode::IMPLIED,     ucode::READ_VALUE,  cmd
#define MOS6502_IMMEDIATE(cmd)   ucode::IMMEDIATE,   ucode::FETCH_VALUE, cmd

#define MOS6502_ABSOLUTE_RD(cmd) ucode::MEMORY_BUS, ucode::FETCH_ADDR_LOW, ucode::FETCH_ADDR_HIGH, ucode::READ_ADDR, cmd
#define MOS6502_ABSOLUTE_RW(cmd) ucode::MEMORY_BUS, ucode::FETCH_ADDR_LOW, ucode::FETCH_ADDR_HIGH, ucode::READ_ADDR, ucode::WRITE_ADDR, cmd, ucode::WRITE_ADDR
#define MOS6502_ABSOLUTE_WR(cmd) ucode::MEMORY_BUS, ucode::FETCH_ADDR_LOW, ucode::FETCH_ADDR_HIGH, cmd,              ucode::WRITE_ADDR

#define MOS6502_ZEROPAGE_RD(cmd) ucode::MEMORY_BUS, ucode::FETCH_ADDR, ucode::READ_ADDR, cmd
#define MOS6502_ZEROPAGE_RW(cmd) ucode::MEMORY_BUS, ucode::FETCH_ADDR, ucode::READ_ADDR, ucode::WRITE_ADDR, cmd, ucode::WRITE_ADDR
#define MOS6502_ZEROPAGE_WR(cmd) ucode::MEMORY_BUS, ucode::FETCH_ADDR, cmd,              ucode::WRITE_ADDR

#define MOS6502_ZEROPAGEI_RD(cmd, reg) ucode::MEMORY_BUS, ucode::FETCH_ADDR, ucode::ADDR_P##reg, ucode::READ_ADDR, cmd
#define MOS6502_ZEROPAGEI_RW(cmd, reg) ucode::MEMORY_BUS, ucode::FETCH_ADDR, ucode::ADDR_P##reg, ucode::READ_ADDR, ucode::WRITE_ADDR, cmd, ucode::WRITE_ADDR
#define MOS6502_ZEROPAGEI_WR(cmd, reg) ucode::MEMORY_BUS, ucode::FETCH_ADDR, ucode::ADDR_P##reg, cmd,              ucode::WRITE_ADDR

#define MOS6502_ABSOLUTEI_RD(cmd, reg) ucode::MEMORY_BUS, ucode::FETCH_ADDR_LOW, ucode::FETCH_ADDR_HIGH_P##reg, ucode::READ_ADDR,     ucode::PUNISH_PAGE, ucode::READ_ADDR,  cmd
#define MOS6502_ABSOLUTEI_RW(cmd, reg) ucode::MEMORY_BUS, ucode::FETCH_ADDR_LOW, ucode::FETCH_ADDR_HIGH_P##reg, ucode::READ_ADDR_FIX, ucode::READ_ADDR,   ucode::WRITE_ADDR, cmd, ucode::WRITE_ADDR
#define MOS6502_ABSOLUTEI_WR(cmd, reg) ucode::MEMORY_BUS, ucode::FETCH_ADDR_LOW, ucode::FETCH_ADDR_HIGH_P##reg, ucode::READ_ADDR_FIX, cmd,                ucode::WRITE_ADDR

#define MOS6502_INDIRECTX_RD(cmd) ucode::MEMORY_BUS, ucode::FETCH_POINTER, ucode::ADDR_PX, ucode::FETCH_EFF_ADDR_LOW, ucode::FETCH_EFF_ADDR_HIGH, ucode::READ_ADDR, cmd
#define MOS6502_INDIRECTX_RW(cmd) ucode::MEMORY_BUS, ucode::FETCH_POINTER, ucode::ADDR_PX, ucode::FETCH_EFF_ADDR_LOW, ucode::FETCH_EFF_ADDR_HIGH, ucode::READ_ADDR, ucode::WRITE_ADDR, cmd, ucode::WRITE_ADDR
#define MOS6502_INDIRECTX_WR(cmd) ucode::MEMORY_BUS, ucode::FETCH_POINTER, ucode::ADDR_PX, ucode::FETCH_EFF_ADDR_LOW, ucode::FETCH_EFF_ADDR_HIGH, cmd,              ucode::WRITE_ADDR

#define MOS6502_INDIRECTY_RD(cmd) ucode::MEMORY_BUS, ucode::FETCH_POINTER, ucode::FETCH_EFF_ADDR_LOW, ucode::FETCH_EFF_ADDR_HIGH_PY, ucode::READ_ADDR,     ucode::PUNISH_PAGE, ucode::READ_ADDR, cmd
#define MOS6502_INDIRECTY_RW(cmd) ucode::MEMORY_BUS, ucode::FETCH_POINTER, ucode::FETCH_EFF_ADDR_LOW, ucode::FETCH_EFF_ADDR_HIGH_PY, ucode::READ_ADDR_FIX, ucode::READ_ADDR,   ucode::WRITE_ADDR, cmd, ucode::WRITE_ADDR
#define MOS6502_INDIRECTY_WR(cmd) ucode::MEMORY_BUS, ucode::FETCH_POINTER, ucode::FETCH_EFF_ADDR_LOW, ucode::FETCH_EFF_ADDR_HIGH_PY, ucode::READ_ADDR_FIX, cmd,                ucode::WRITE_ADDR

enum class ucode : std::uint8_t{
    FETCH_OPCODE,
    
    ADDRESS_SPACE_BEGIN, // Dummy value

    ACCUMULATOR,
    IMPLIED,
    IMMEDIATE,
    MEMORY_BUS,

    PRE_INSTRUCTIONS_BEGIN, // Dummy value

    FETCH_VALUE,
    FETCH_ADDR,
    FETCH_ADDR_LOW,
    FETCH_ADDR_HIGH_PX,
    FETCH_ADDR_HIGH_PY,
    FETCH_ADDR_HIGH,

    FETCH_POINTER,
    FETCH_EFF_ADDR_LOW,
    FETCH_EFF_ADDR_HIGH_PY,
    FETCH_EFF_ADDR_HIGH,

    FETCH_RESET_LOW,
    FETCH_RESET_HIGH,

    PUNISH_PAGE,

    ADDR_PX,
    ADDR_PY,
    READ_VALUE,
    READ_ADDR_FIX,
    READ_ADDR,

    WRITE_ADDR,

    PUSH_STACK,
    POP_STACK,

    PUNISH_BRANCH,

    INSTRUCTIONS_BEGIN, // Dummy value

    LDA, STA, LDX, STX, LDY, STY,
    TAX, TXA, TAY, TYA,
    ADC, SBC, INC, DEC, INX, DEX, INY, DEY,
    ASL, LSR, ROL, ROR,
    AND, ORA, EOR, BIT,
    CMP, CPX, CPY,
    BCC, BCS, BEQ, BNE, BPL, BMI, BVC, BVS,
    JMP, JSR, RTS, BRK, RTI,
    PHA, PLA, PHP, PLP, TXS, TSX,
    CLC, SEC, CLI, SEI, CLD, SED, CLV,
    NOP
};

static const ucode reset_instructions[8] = {
    ucode::NOP, // Reset hold
    ucode::NOP, // Start state
    ucode::PUSH_STACK,
    ucode::PUSH_STACK,
    ucode::PUSH_STACK,
    ucode::FETCH_RESET_LOW,
    ucode::FETCH_RESET_HIGH
};

static const ucode instructions[256][8] = {
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    { MOS6502_INDIRECTX_RD(ucode::ADC) },
    {},
    {},
    {},
    { MOS6502_ZEROPAGE_RD(ucode::ADC) },
    {},
    {},
    {},
    { MOS6502_IMMEDIATE(ucode::ADC) },
    {},
    {},
    {},
    { MOS6502_ABSOLUTE_RD(ucode::ADC) },
    {},
    {},
    {},
    { MOS6502_INDIRECTY_RD(ucode::ADC) },
    {},
    {},
    {},
    { MOS6502_ZEROPAGEI_RD(ucode::ADC, X) },
    {},
    {},
    {},
    { MOS6502_ABSOLUTEI_RD(ucode::ADC, Y) },
    {},
    {},
    {},
    { MOS6502_ABSOLUTEI_RD(ucode::ADC, X) },
    {},
    {},
    {},
    { MOS6502_INDIRECTX_WR(ucode::STA) },
    {},
    {},
    { MOS6502_ZEROPAGE_WR(ucode::STY) },
    { MOS6502_ZEROPAGE_WR(ucode::STA) },
    { MOS6502_ZEROPAGE_WR(ucode::STX) },
    {},
    {},
    {},
    { MOS6502_IMPLIED(ucode::TXA) },
    {},
    { MOS6502_ABSOLUTE_WR(ucode::STY) },
    { MOS6502_ABSOLUTE_WR(ucode::STA) },
    { MOS6502_ABSOLUTE_WR(ucode::STX) },
    {},
    {},
    { MOS6502_INDIRECTY_WR(ucode::STA) },
    {},
    {},
    { MOS6502_ZEROPAGEI_WR(ucode::STX, X) },
    { MOS6502_ZEROPAGEI_WR(ucode::STA, X) },
    { MOS6502_ZEROPAGEI_WR(ucode::STX, Y) },
    {},
    { MOS6502_IMPLIED(ucode::TYA) },
    { MOS6502_ABSOLUTEI_WR(ucode::STA, Y) },
    {},
    {},
    {},
    { MOS6502_ABSOLUTEI_WR(ucode::STA, X) },
    {},
    {},
    { MOS6502_IMMEDIATE(ucode::LDY) },
    { MOS6502_INDIRECTX_RD(ucode::LDA) },
    { MOS6502_IMMEDIATE(ucode::LDX) },
    {},
    { MOS6502_ZEROPAGE_RD(ucode::LDY) },
    { MOS6502_ZEROPAGE_RD(ucode::LDA) },
    { MOS6502_ZEROPAGE_RD(ucode::LDX) },
    {},
    { MOS6502_IMPLIED(ucode::TAY) },
    { MOS6502_IMMEDIATE(ucode::LDA) },
    { MOS6502_IMPLIED(ucode::TAX) },
    {},
    { MOS6502_ABSOLUTE_RD(ucode::LDY) },
    { MOS6502_ABSOLUTE_RD(ucode::LDA) },
    { MOS6502_ABSOLUTE_RD(ucode::LDX) },
    {},
    {},
    { MOS6502_INDIRECTY_RD(ucode::LDA) },
    {},
    {},
    { MOS6502_ZEROPAGEI_RD(ucode::LDY, X) },
    { MOS6502_ZEROPAGEI_RD(ucode::LDA, X) },
    { MOS6502_ZEROPAGEI_RD(ucode::LDX, Y) },
    {},
    {},
    { MOS6502_ABSOLUTEI_RD(ucode::LDA, Y)},
    {},
    {},
    { MOS6502_ABSOLUTEI_RD(ucode::LDY, X) },
    { MOS6502_ABSOLUTEI_RD(ucode::LDA, X) },
    { MOS6502_ABSOLUTEI_RD(ucode::LDX, Y) },
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {}
};

}

#endif