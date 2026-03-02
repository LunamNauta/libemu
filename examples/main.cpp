#include "../include/mos6502/chip.hpp"

#include <iostream>
#include <array>
#include <thread>

class memory_bus{
public:
    memory_bus(const std::array<std::uint8_t, 65536>& mi) : memory(mi){}

    void write(std::uint16_t addr, std::uint8_t val){
        memory[addr] = val;
    }
    std::uint8_t read(std::uint16_t addr){
        return memory[addr];
    }
private:
    std::array<std::uint8_t, 65536> memory;
};

int main(){
    std::array<std::uint8_t, 65536> rom({});

    rom[0x0200] = 0xa9;
    rom[0x0201] = 56;

    rom[0xfffc] = 0x00;
    rom[0xfffd] = 0x02;

    memory_bus bus(rom);

    libemu::mos6502::chip<memory_bus> chip(bus);

    chip.set_res(0);
    chip.tick();
    chip.set_res(1);
    chip.set_rdy(1);

    while (true){
        chip.tick();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << "Cycle: " << chip.get_cycle() << "\n";
        std::cout << "Address: " << chip.get_address() << "\n";
        std::cout << "Data: " << +chip.get_data() << "\n";
        std::cout << "A: " << +chip.get_a() << "\n";
        std::cout << "X: " << +chip.get_x() << "\n";
        std::cout << "Y: " << +chip.get_y() << "\n";
        std::cout << "PC: " << chip.get_pc() << "\n";
        std::cout << "\n";
    }
}