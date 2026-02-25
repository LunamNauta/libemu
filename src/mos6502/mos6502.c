#include "../../include/mos6502/mos6502.h"
#include "../../include/mos6502/memory.h"
#include "../../include/mos6502/opcodes.h"

#include <string.h>

void mos6502_init(struct mos6502* chip, uint8_t* memory){
    memset(chip, 0, sizeof(struct mos6502));
    chip->memory = memory;
    chip->stopped = true;
}
void mos6502_reset(struct mos6502* chip){
    chip->a = 0;
    chip->x = 0;
    chip->y = 0;
    chip->sp = chip->memory + 0x01ff;
    uint16_t pc_addr = chip->memory[0xfffc] | (chip->memory[0xfffd] << 8);
    chip->pc = &chip->memory[pc_addr];
    chip->ps = 0x34;

    chip->stopped = false;
}

void mos6502_cycle(struct mos6502* chip){
    if (chip->stopped) return;
    if (chip->remaining_cycles){
        chip->remaining_cycles--;
        chip->current_cycle++;
        return;
    }

    if (chip->opcode_info.handler != NULL){
        chip->opcode_info.handler(chip);
    }

    uint8_t opcode = mos6502_fetch_opcode(chip);
    chip->opcode_info = mos6502_opcodes[opcode];
    chip->remaining_cycles = chip->opcode_info.cycles;
}