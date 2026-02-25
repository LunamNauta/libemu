#include "../../include/mos6502/memory.h"
#include "../../include/mos6502/mos6502.h"

#include <stdio.h> // TODO: Remove

void mos6502_stack_push8(struct mos6502* chip, uint8_t val){
    *(--chip->sp) = val;
}
void mos6502_stack_push16(struct mos6502* chip, uint16_t val){
    *(--chip->sp) = (val & 0xff00) >> 8;
    *(--chip->sp) = val & 0x00ff;
}
uint8_t mos6502_stack_pop8(struct mos6502* chip){
    return *(chip->sp++);
}
uint16_t mos6502_stack_pop16(struct mos6502* chip){
    return *(chip->sp++) | (*(chip->sp++) << 8);
}

uint8_t mos6502_fetch_opcode(struct mos6502* chip){
    return *chip->pc++;
}