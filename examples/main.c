#include "../include/mos6502/mos6502.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SNAKE_SCREEN_WIDTH 32
#define SNAKE_SCREEN_HEIGHT 32

#define SNAKE_MEM16_FUNC_MAX       (0xfffc                     - 0x1fff)
#define SNAKE_MEM16_RESET_SNAKEPOS (SNAKE_MEM16_FUNC_MAX       - 20)
#define SNAKE_MEM16_RESET_APPLEPOS (SNAKE_MEM16_RESET_SNAKEPOS - 20)
#define SNAKE_MEM16_RANDOMPOS      (SNAKE_MEM16_RESET_APPLEPOS - 20)

#define SNAKE_MEM8_APPLEPOS_TBL   0x00
#define SNAKE_MEM8_POSX           0x41
#define SNAKE_MEM8_POSY           0x42
#define SNAKE_MEM8_APPLEX         0x43
#define SNAKE_MEM8_APPLEY         0x44
#define SNAKE_MEM8_APPLEPOS_PTR   0x45

int main(){
    uint8_t ram[65536] = {
        // Initialize variables
        [0x01ff + 0x0000] = 0xa2, // LDX (Immediate)
        [0x01ff + 0x0001] = 0,
        [0x01ff + 0x0002] = 0x84, // STX (Zero Page)
        [0x01ff + 0x0003] = SNAKE_MEM8_POSX,
        [0x01ff + 0x0004] = 0x84, // STX (Zero Page)
        [0x01ff + 0x0005] = SNAKE_MEM8_POSY,
        [0x01ff + 0x0006] = 0x84, // STX (Zero Page)
        [0x01ff + 0x0007] = SNAKE_MEM8_APPLEX,
        [0x01ff + 0x0008] = 0x84, // STX (Zero Page)
        [0x01ff + 0x0009] = SNAKE_MEM8_APPLEY,
        [0x01ff + 0x000a] = 0x84, // STX (Zero Page)
        [0x01ff + 0x000b] = SNAKE_MEM8_APPLEPOS_PTR,

        // Call: reset_snake
        [0x01ff + 0x000e] = 0x20, // JSR
        [0x01ff + 0x000f] = ((0x01ff + SNAKE_MEM16_RESET_SNAKEPOS) & 0x00ff) >> 0,
        [0x01ff + 0x0010] = ((0x01ff + SNAKE_MEM16_RESET_SNAKEPOS) & 0xff00) >> 8,
        
        // Call: reset_apple
        [0x01ff + 0x0011] = 0x20, // JSR
        [0x01ff + 0x0012] = ((0x01ff + SNAKE_MEM16_RESET_APPLEPOS) & 0x00ff) >> 0,
        [0x01ff + 0x0013] = ((0x01ff + SNAKE_MEM16_RESET_APPLEPOS) & 0xff00) >> 8,
        
        // Halt
        [0x01ff + 0x0014] = 0x02, // STP

        // Function random_position
        // Increment position pointer
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0000] = 0x18, // CLC
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0001] = 0xa6, // LDX (Zero Page)
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0002] = SNAKE_MEM8_APPLEPOS_PTR,
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0003] = 0xe8, // INX
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0004] = 0xe0, // CPX (Immedate)
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0005] = 64,
        // Wrap position pointer
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0006] = 0xd0, // BNE
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0007] = 2,
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0008] = 0xa2, // LDX (Immediate)
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x0009] = 0,
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x000a] = 0x86, // STX (Zero Page)
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x000b] = SNAKE_MEM8_APPLEPOS_PTR,
        // Get position
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x000c] = 0xb4, // LDY (Zero Page,X)
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x000d] = SNAKE_MEM8_APPLEPOS_TBL,
        // Return
        [0x01ff + SNAKE_MEM16_RANDOMPOS + 0x000e] = 0x60, // RTS

        // Function: reset_apple
        // Call: reset_apple
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0000] = 0x20, // JSR
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0001] = ((0x01ff + SNAKE_MEM16_RANDOMPOS) & 0x00ff) >> 0,
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0002] = ((0x01ff + SNAKE_MEM16_RANDOMPOS) & 0xff00) >> 8,
        // Store X position
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0003] = 0x84, // STY (Zero Page)
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0004] = SNAKE_MEM8_APPLEX,
        // Call: reset_apple
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0005] = 0x20, // JSR
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0006] = ((0x01ff + SNAKE_MEM16_RANDOMPOS) & 0x00ff) >> 0,
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0007] = ((0x01ff + SNAKE_MEM16_RANDOMPOS) & 0xff00) >> 8,
        // Store Y position
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0008] = 0x84, // STY (Zero Page)
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x0009] = SNAKE_MEM8_APPLEY,
        // Return
        [0x01ff + SNAKE_MEM16_RESET_APPLEPOS + 0x000a] = 0x60, // RTS

        // Function: reset_snake
        // Store X position
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0000] = 0xa2, // LDX (Immediate)
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0001] = SNAKE_SCREEN_WIDTH / 2,
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0002] = 0x86, // STX (Zero Page)
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0003] = SNAKE_MEM8_POSX,
        // Store Y position
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0004] = 0xa2, // LDX (Immediate)
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0005] = SNAKE_SCREEN_HEIGHT / 2,
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0006] = 0x86, // STX (Zero Page)
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0007] = SNAKE_MEM8_POSY,
        // Return
        [0x01ff + SNAKE_MEM16_RESET_SNAKEPOS + 0x0008] = 0x60, // RTS

        // Set reset vector
        [0xfffc] = 0xff,
        [0xfffd] = 0x01
    };
    srand(time(0));
    for (size_t a = 0; a < 64; a++){
        ram[SNAKE_MEM8_APPLEPOS_TBL + a] = rand() % 32;
    }

    struct mos6502 chip;
    mos6502_init(&chip, ram);
    mos6502_reset(&chip);

    while (true){
        mos6502_cycle(&chip);
        if (chip.remaining_cycles != 0) continue;

        if (chip.current_cycle > 256) break;

        printf("Reg (A): %i\n", chip.a);
        printf("Reg (X): %i\n", chip.x);
        printf("Reg (Y): %i\n", chip.y);
        printf("PC: %zu\n", chip.pc - chip.memory);
        printf("Cycle: %zu\n", chip.current_cycle);
        printf("------------------\n");
        printf("Snake Pos: (%i, %i)\n", ram[SNAKE_MEM8_POSX], ram[SNAKE_MEM8_POSY]);
        printf("Apple Pos: (%i, %i)\n", ram[SNAKE_MEM8_APPLEX], ram[SNAKE_MEM8_APPLEY]);
        printf("\n");
    }
}