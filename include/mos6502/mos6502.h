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
void mos6502_process_arithmetic(struct mos6502* chip, uint8_t instruction, uint8_t* memory);
void mos6502_process_shift(struct mos6502* chip, uint8_t instruction, uint8_t* memory);
void mos6502_process_bitwise(struct mos6502* chip, uint8_t instruction, uint8_t* memory);
void mos6502_process_compare(struct mos6502* chip, uint8_t instruction, uint8_t* memory);
void mos6502_process_branch(struct mos6502* chip, uint8_t instruction, uint8_t* memory);
void mos6502_process_jump(struct mos6502* chip, uint8_t instruction, uint8_t* memory);
void mos6502_process_stack(struct mos6502* chip, uint8_t instruction);
void mos6502_process_flags(struct mos6502* chip, uint8_t instruction);
void mos6502_process_illegal(struct mos6502* chip, uint8_t instruction, uint8_t* memory);

void mos6502_tick(struct mos6502* chip){
    if (chip->remaining_cycles != 0){
        chip->remaining_cycles--;
        chip->current_cycles++;
        return;
    }

    struct mos6502_opcode opcode = mos6502_next_opcode(chip);
    chip->remaining_cycles = opcode.cycles;

    if (opcode.instruction <= MOS6502_STY) return mos6502_process_access(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
    if (opcode.instruction <= MOS6502_TYA) return mos6502_process_transfer(chip, opcode.instruction);
    if (opcode.instruction <= MOS6502_DEY) return mos6502_process_arithmetic(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
    if (opcode.instruction <= MOS6502_ROR) return mos6502_process_shift(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
    if (opcode.instruction <= MOS6502_BIT) return mos6502_process_bitwise(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
    if (opcode.instruction <= MOS6502_CPY) return mos6502_process_compare(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
    if (opcode.instruction <= MOS6502_BVS) return mos6502_process_branch(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
    if (opcode.instruction <= MOS6502_RTI) return mos6502_process_jump(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
    if (opcode.instruction <= MOS6502_TSX) return mos6502_process_stack(chip, opcode.instruction);
    if (opcode.instruction <= MOS6502_CLV) return mos6502_process_flags(chip, opcode.instruction);
    if (opcode.instruction == MOS6502_NOP) return;
    return mos6502_process_illegal(chip, opcode.instruction, mos6502_fetch_memory(chip, opcode.address_mode));
}

#endif