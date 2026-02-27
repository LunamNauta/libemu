#ifndef MOS6502_MEMORYBUS_HEADER
#define MOS6502_MEMORYBUS_HEADER

#include "chip.hpp"

#include <cstdint>
#include <array>

template <std::size_t max_address>
class MOS6502_MemoryBus{
public:
    MOS6502_MemoryBus(){}
    MOS6502_MemoryBus(const std::array<std::uint8_t, max_address>& mi) : memory(mi){}

    void write(MOS6502_Chip<MOS6502_MemoryBus>* chip, std::uint16_t addr, std::uint8_t val){
        data = val;
        if (addr >= max_address) return;
        memory[addr] = val;
    }
    std::uint8_t read(MOS6502_Chip<MOS6502_MemoryBus>* chip, std::uint16_t addr){
        if (addr >= max_address) return data;
        data = memory[addr];
        return data;
    }

private:
    std::array<std::uint8_t, max_address> memory;
    std::uint8_t data;
};

#endif