#include "../include/mos6502/memory_bus.hpp"
#include "../include/mos6502/chip.hpp"

#include <array>
#include <chrono>
#include <iostream>
#include <thread>

int main(){
    std::array<std::uint8_t, 65536> rom;
    std::fill(rom.begin(), rom.end(), 0xa9);
    rom[0xfffc] = 0xff;
    rom[0xfffd] = 0x01;
    rom[0x32] = 37;
    rom[0x34] = 13;
    std::array<std::uint8_t, 12> func_main({
        0xa9, 12, // LDA Immediate
        0xa4, 0x32, // LDY Zero Page
        0xa6, 0x34, // LDX Zero Page
        0x8e, 0xff, 0x02, // STX Absolute
        0xac, 0xff, 0x02 // LDY Absolute
    });
    std::copy(func_main.begin(), func_main.end(), rom.begin() + 0x01ff);

    MOS6502_MemoryBus<65536> bus(rom);
    MOS6502_Chip chip(bus);

    chip.set_res(0);
    chip.tick();
    chip.set_res(1);
    chip.set_rdy(1);

    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "{A: " << +chip.get_a() << ", ";
        std::cout << "X: " << +chip.get_x() << ", ";
        std::cout << "Y: " << +chip.get_y() << ", ";
        std::cout << "PC: " << +chip.get_pc() << ", ";
        std::cout << "SP: " << +chip.get_sp() << "}";
        std::cout << "\n";
        chip.tick();
        if (chip.get_syn()) std::cout << "\n";

        if (bus.read(&chip, 0x02ff) == 13) chip.set_rdy(0);

        if (chip.get_cycle_index() && chip.get_cycle_index() % 1790000 == 0){
            std::cout << "Tick\n";
        }
    }
}