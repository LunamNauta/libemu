#include "../../include/mos6502/opcodes.h"
#include "../../include/mos6502/addressing.h"
#include "../../include/mos6502/memory.h"
#include "../../include/mos6502/mos6502.h"

#include <stdio.h> // TODO: Remove

// Access
void mos6502_lda(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand;
}
void mos6502_sta(struct mos6502* chip){
    *mos6502_address_access(chip) = chip->a;
}
void mos6502_ldx(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->x = chip->operand;
}
void mos6502_stx(struct mos6502* chip){
    *mos6502_address_access(chip) = chip->x;
}
void mos6502_ldy(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->y = chip->operand;   
}
void mos6502_sty(struct mos6502* chip){
    *mos6502_address_access(chip) = chip->y;
}
// Transfer
void mos6502_tax(struct mos6502* chip){
    chip->operand = chip->a;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->x = chip->operand;
}
void mos6502_txa(struct mos6502* chip){
    chip->operand = chip->x;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand;
}
void mos6502_tay(struct mos6502* chip){
    chip->operand = chip->a;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->y = chip->operand;
}
void mos6502_tya(struct mos6502* chip){
    chip->operand = chip->y;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand; 
}
// Arithmetic
void mos6502_adc(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = chip->a + (*mem) + chip->c;
    chip->c = chip->operand > 0xff;
    chip->z = chip->operand == 0;
    chip->o = ((chip->operand ^ chip->a) & (chip->operand ^ (*mem)) & 0x80) != 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand;
}
void mos6502_sbc(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = chip->a + (~(*mem)) + chip->c;
    chip->c = chip->operand > 0xff;
    chip->z = chip->operand == 0;
    chip->o = ((chip->operand ^ chip->a) & (chip->operand ^ (*mem)) & 0x80) != 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand;
}
void mos6502_inc(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = (*mem) + 1;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    *mem = chip->operand; 
}
void mos6502_dec(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = (*mem) - 1;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    *mem = chip->operand;    
}
void mos6502_inx(struct mos6502* chip){
    chip->operand = chip->x + 1;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->x = chip->operand;
}
void mos6502_dex(struct mos6502* chip){
    chip->operand = chip->x - 1;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->x = chip->operand;
}
void mos6502_iny(struct mos6502* chip){
    chip->operand = chip->y + 1;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->y = chip->operand;
}
void mos6502_dey(struct mos6502* chip){
    chip->operand = chip->y - 1;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->y = chip->operand;
}
// Shift
void mos6502_asl(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = (*mem) << 1;
    chip->c = (chip->operand & 0x80) != 0;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    *mem = chip->operand;
}
void mos6502_lsr(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = (*mem) >> 1;
    chip->c = chip->operand & 0x01;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    *mem = chip->operand;  
}
void mos6502_rol(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = (*mem) << 1;
    chip->operand |= (((*mem) & 0x80) >> 7);
    chip->c = (chip->operand & 0x80) != 0;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    *mem = chip->operand;   
}
void mos6502_ror(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = (*mem) >> 1;
    chip->operand |= (((*mem) & 0x01) << 7);
    chip->c = chip->operand & 0x01;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    *mem = chip->operand;   
}
// Bitwise
void mos6502_ora(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->operand |= chip->a;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand;
}
void mos6502_and(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->operand &= chip->a;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand;  
}
void mos6502_eor(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->operand ^= chip->a;
    chip->z = chip->operand == 0;
    chip->n = (chip->operand & 0x80) != 0;
    chip->a = chip->operand;
}
void mos6502_bit(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->z = chip->operand == 0;
    chip->o = chip->operand & 0x40;
    chip->n = (chip->operand & 0x80) != 0;
}
// Compare
void mos6502_cmp(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->c = chip->a >= chip->operand;
    chip->z = chip->a == chip->operand;
    chip->n = chip->a < chip->operand;
}
void mos6502_cpx(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->c = chip->x >= chip->operand;
    chip->z = chip->x == chip->operand;
    chip->n = chip->x < chip->operand;  
}
void mos6502_cpy(struct mos6502* chip){
    chip->operand = *mos6502_address_access(chip);
    chip->c = chip->y >= chip->operand;
    chip->z = chip->y == chip->operand;
    chip->n = chip->y < chip->operand;  
}
// Branch
void mos6502_bcc(struct mos6502* chip){
    if (chip->c){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
void mos6502_bcs(struct mos6502* chip){
    if (!chip->c){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
void mos6502_beq(struct mos6502* chip){
    if (!chip->z){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
void mos6502_bne(struct mos6502* chip){
    if (chip->z){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
void mos6502_bpl(struct mos6502* chip){
    if (chip->n){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
void mos6502_bmi(struct mos6502* chip){
    if (!chip->n){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
void mos6502_bvc(struct mos6502* chip){
    if (chip->o){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
void mos6502_bvs(struct mos6502* chip){
    if (!chip->o){
        chip->pc++;
        return;
    }
    chip->remaining_cycles++;
    chip->pc = mos6502_address_access(chip);
}
// Jump
void mos6502_jmp(struct mos6502* chip){
    uint8_t* mem = mos6502_address_access(chip);
    chip->operand = ((uint16_t)(*mem)) | ((uint16_t)((*mem) << 8));
    chip->pc = chip->memory + chip->operand;
}
void mos6502_jsr(struct mos6502* chip){
    mos6502_stack_push16(chip, chip->pc - chip->memory + 1);
    chip->pc = mos6502_address_access(chip);
}
void mos6502_rts(struct mos6502* chip){
    chip->operand = mos6502_stack_pop16(chip);
    chip->pc = chip->memory + chip->operand + 1;
}
void mos6502_brk(struct mos6502* chip){
    mos6502_stack_push16(chip, chip->pc - chip->memory);
    mos6502_stack_push8(chip, chip->ps | MOS6502_BREAK);
    chip->i = 1;
    chip->pc++;
}
void mos6502_rti(struct mos6502* chip){
    chip->ps = mos6502_stack_pop8(chip);
    chip->pc = chip->memory + mos6502_stack_pop16(chip);
}
// Stack
void mos6502_pha(struct mos6502* chip){
    mos6502_stack_push8(chip, chip->a);
}
void mos6502_pla(struct mos6502* chip){
    chip->a = mos6502_stack_pop8(chip);
}
void mos6502_php(struct mos6502* chip){
    mos6502_stack_push8(chip, chip->ps | MOS6502_BREAK);
}
void mos6502_plp(struct mos6502* chip){
    chip->ps = mos6502_stack_pop8(chip);
}
void mos6502_txs(struct mos6502* chip){
    chip->sp = chip->memory + 0x01ff - chip->x;
}
void mos6502_tsx(struct mos6502* chip){
    chip->x = chip->sp - chip->memory;
}
// Flags
void mos6502_clc(struct mos6502* chip){
    chip->c = 0;
}
void mos6502_sec(struct mos6502* chip){
    chip->c = 1;
}
void mos6502_cli(struct mos6502* chip){
    chip->i = 0;
}
void mos6502_sei(struct mos6502* chip){
    chip->i = 1;
}
void mos6502_cld(struct mos6502* chip){
    chip->d = 0;
}
void mos6502_sed(struct mos6502* chip){
    chip->d = 1;
}
void mos6502_clv(struct mos6502* chip){
    chip->o = 0;
}
// Other
void mos6502_nop(struct mos6502* chip){
    return;
}
// Illegal
void mos6502_illegal_nop(struct mos6502* chip){
    return;
}
void mos6502_illegal_shy(struct mos6502* chip){
    return;
}
void mos6502_illegal_stp(struct mos6502* chip){
    chip->stopped = true;
    return;
}
void mos6502_illegal_shx(struct mos6502* chip){
    return;
}
void mos6502_illegal_slo(struct mos6502* chip){
    return;
}
void mos6502_illegal_anc(struct mos6502* chip){
    return;
}
void mos6502_illegal_rla(struct mos6502* chip){
    return;
}
void mos6502_illegal_sre(struct mos6502* chip){
    return;
}
void mos6502_illegal_alr(struct mos6502* chip){
    return;
}
void mos6502_illegal_rra(struct mos6502* chip){
    return;
}
void mos6502_illegal_arr(struct mos6502* chip){
    return;
}
void mos6502_illegal_sax(struct mos6502* chip){
    return;
}
void mos6502_illegal_xaa(struct mos6502* chip){
    return;
}
void mos6502_illegal_ahx(struct mos6502* chip){
    return;
}
void mos6502_illegal_tas(struct mos6502* chip){
    return;
}
void mos6502_illegal_lax(struct mos6502* chip){
    return;
}
void mos6502_illegal_las(struct mos6502* chip){
    return;
}
void mos6502_illegal_dcp(struct mos6502* chip){
    return;
}
void mos6502_illegal_axs(struct mos6502* chip){
    return;
}
void mos6502_illegal_isc(struct mos6502* chip){
    return;
}
void mos6502_illegal_sbc(struct mos6502* chip){
    return;
}