#ifndef MOS6502_MOS6502_HEADER
#define MOS6502_MOS6502_HEADER

#include "opcodes.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MOS6502_NEGATIVE  0b10000000
#define MOS6502_OVERFLOW  0b01000000
#define MOS6502_BREAK     0b00010000
#define MOS6502_DECIMAL   0b00001000
#define MOS6502_INTERRUPT 0b00000100
#define MOS6502_ZERO      0b00000010
#define MOS6502_CARRY     0b00000001

struct mos6502{
    // Registers
    uint8_t a;
    uint8_t x;
    uint8_t y;
    union{
        uint8_t ps;
        struct{
            uint8_t n : 1;
            uint8_t o : 1;
            uint8_t r : 1;
            uint8_t b : 1;
            uint8_t d : 1;
            uint8_t i : 1;
            uint8_t z : 1;
            uint8_t c : 1;
        };
    };
    uint8_t* pc;
    uint8_t* sp;

    // Implementation logic
    uint8_t remaining_cycles;
    size_t current_cycle;

    uint8_t* memory;
    uint16_t addr;

    struct mos6502_opcode opcode_info;
    uint16_t operand;

    bool stopped;
};

void mos6502_init(struct mos6502* chip, uint8_t* memory);
void mos6502_reset(struct mos6502* chip);

void mos6502_cycle(struct mos6502* chip);

#endif