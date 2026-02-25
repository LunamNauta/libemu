#include "../../include/mos6502/addressing.h"
#include "../../include/mos6502/mos6502.h"

#include <stdbool.h>
#include <stddef.h>

#include <stdio.h> // TODO: Remove

uint8_t* mos6502_address_access(struct mos6502* chip){
    uint8_t page = ((chip->pc - chip->memory - 1) & 0xff00) >> 8;
    uint8_t instruction = chip->opcode_info.instruction;
    bool page_crossed = false;
    uint8_t* value;

    switch (chip->opcode_info.address_mode){
        case MOS6502_IMPLICIT: return NULL;
        case MOS6502_ACCUMULATOR: return &chip->a;
        case MOS6502_IMMEDIATE: return chip->pc++;
        case MOS6502_ZEROPAGE:{
            uint8_t addr = *chip->pc++;
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_ZEROPAGEX:{
            uint8_t addr = (*chip->pc++) + chip->x;
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_ZEROPAGEY:{
            uint8_t addr = (*chip->pc++) + chip->y;
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_RELATIVE:{
            uint8_t uoffset = *chip->pc++;
            int8_t offset = (uoffset & 0x80) != 0 ? -((int8_t)(~uoffset+1)) : uoffset;
            uint16_t addr = (chip->pc - chip->memory) + offset;
            if (((addr & 0xff00) >> 8) != page) page_crossed = true;
            value = chip->pc + offset; // TODO: Is this addressing correct? Or is it -1 or 1?
            break;
        }
        case MOS6502_ABSOLUTE:{
            uint16_t addr = ((uint16_t)(*chip->pc++)) | (((uint16_t)(*chip->pc++)) << 8);
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_ABSOLUTEX:{
            uint16_t addr = ((uint16_t)(*chip->pc++)) | (((uint16_t)(*chip->pc++)) << 8) + chip->x;
            if (((addr & 0xff00) >> 8) != page) page_crossed = true;
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_ABSOLUTEY:{
            uint16_t addr = ((uint16_t)(*chip->pc++)) | (((uint16_t)(*chip->pc++)) << 8) + chip->y;
            if (((addr & 0xff00) >> 8) != page) page_crossed = true;
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_INDIRECT:{
            uint16_t tmp_addr = ((uint16_t)(*chip->pc++)) | (((uint16_t)(*chip->pc++)) << 8);
            uint16_t addr_low = chip->memory[tmp_addr];
            if ((tmp_addr & 0x00ff) == 0x00ff) tmp_addr ^= 0x00ff;
            else tmp_addr++;
            uint16_t addr_high = chip->memory[tmp_addr];
            uint16_t addr = addr_low | (addr_high << 8);
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_INDIRECTX:{
            uint8_t tmp_addr = (*chip->pc++) + chip->x;
            uint16_t addr = ((uint16_t)chip->memory[tmp_addr]) | (((uint16_t)chip->memory[tmp_addr + 1]) << 8);
            value = &chip->memory[addr];
            break;
        }
        case MOS6502_INDIRECTY:{
            uint8_t tmp_addr = *chip->pc++;
            uint16_t addr = ((uint16_t)chip->memory[tmp_addr]) | (((uint16_t)chip->memory[tmp_addr + 1]) << 8);
            if (((addr & 0xff00) >> 8) != page) page_crossed = true;
            value = &chip->memory[addr];
            break;
        }
        default: return NULL;
    }

    if (!page_crossed) return value;

    switch (instruction){
        case MOS6502_ADC: chip->remaining_cycles++; break;
        case MOS6502_AND: chip->remaining_cycles++; break;
        case MOS6502_BCC: chip->remaining_cycles++; break;
        case MOS6502_BCS: chip->remaining_cycles++; break;
        case MOS6502_BEQ: chip->remaining_cycles++; break;
        case MOS6502_BMI: chip->remaining_cycles++; break;
        case MOS6502_BNE: chip->remaining_cycles++; break;
        case MOS6502_BPL: chip->remaining_cycles++; break;
        case MOS6502_BVC: chip->remaining_cycles++; break;
        case MOS6502_CMP: chip->remaining_cycles++; break;
        case MOS6502_EOR: chip->remaining_cycles++; break;
        case MOS6502_LDA: chip->remaining_cycles++; break;
        case MOS6502_LDX: chip->remaining_cycles++; break;
        case MOS6502_LDY: chip->remaining_cycles++; break;
        case MOS6502_ORA: chip->remaining_cycles++; break;
        case MOS6502_SBC: chip->remaining_cycles++; break;
    }

    return value;
}