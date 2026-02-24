#ifndef MOS6502_MOS6502_HEADER
#define MOS6502_MOS6502_HEADER

#include "opcodes.h"

#include <stdint.h>
#include <string.h>

struct mos6502{
    uint8_t a;
    uint8_t x;
    uint8_t y;
    union{
        uint8_t c : 1;
        uint8_t z : 1;
        uint8_t i : 1;
        uint8_t d : 1;
        uint8_t b : 1;
        uint8_t reserved : 1;
        uint8_t v : 1;
        uint8_t n : 1;
    };
    uint16_t pc;
    uint16_t sp;

    uint8_t* mem;
    uint16_t mlen;

    size_t current_cycles;
    uint8_t remaining_cycles;

    uint8_t bus_residue;
};

void mos6502_init(struct mos6502* chip, uint8_t* memory, uint16_t mlen){
    memset(chip, 0, sizeof(struct mos6502));
    chip->reserved = 1;
    chip->mem = memory;
    chip->mlen = mlen;
}

struct mos6502_opcode mos6502_next_opcode(struct mos6502* chip){
    if (chip->pc >= chip->mlen) return mos6502_opcodes[chip->bus_residue];
    return mos6502_opcodes[chip->mem[chip->pc++]];
}

uint8_t* mos6502_fetch_memory(struct mos6502* chip, uint8_t address_mode);

void mos6502_process_access(struct mos6502* chip, uint8_t instruction, uint8_t* memory){
    uint8_t result;
    switch (instruction){
        case MOS6502_LDA: chip->a = *memory; result = chip->a; break;
        case MOS6502_STA: *memory = chip->a; break;
        case MOS6502_LDX: chip->x = *memory; result = chip->x; break;
        case MOS6502_STX: *memory = chip->x; break;
        case MOS6502_LDY: chip->y = *memory; result = chip->y; break;
        case MOS6502_STY: *memory = chip->y; break;
    }
    chip->z = result == 0;
    chip->n = result & 0x80;
}
void mos6502_process_transfer(struct mos6502* chip, uint8_t instruction){
    uint8_t result;
    switch (instruction){
        case MOS6502_TAX: chip->x = chip->a; result = chip->x; break;
        case MOS6502_TXA: chip->a = chip->x; result = chip->a; break;
        case MOS6502_TAY: chip->y = chip->a; result = chip->y; break;
        case MOS6502_TYA: chip->a = chip->y; result = chip->a; break;
    }
    chip->z = result == 0;
    chip->n = result & 0x80;
}

void mos6502_tick(struct mos6502* chip){
    if (chip->remaining_cycles != 0){
        chip->remaining_cycles--;
        chip->current_cycles++;
        return;
    }

    struct mos6502_opcode opcode = mos6502_next_opcode(chip);
    uint8_t* memory = mos6502_fetch_memory(chip, opcode.address_mode);
    chip->remaining_cycles = opcode.cycles;

}

#endif