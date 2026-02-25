#ifndef MOS6502_MEMORY_HEADER
#define MOS6502_MEMORY_HEADER

#include <stdint.h>

struct mos6502;

void mos6502_stack_push8(struct mos6502* chip, uint8_t val);
void mos6502_stack_push16(struct mos6502* chip, uint16_t val);
uint8_t mos6502_stack_pop8(struct mos6502* chip);
uint16_t mos6502_stack_pop16(struct mos6502* chip);

uint8_t mos6502_fetch_opcode(struct mos6502* chip);

#endif