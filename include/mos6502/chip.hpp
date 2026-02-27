#ifndef MOS6502_MOS6502_HEADER
#define MOS6502_MOS6502_HEADER

#include "instructions.hpp"
#include "memory_bus.hpp"

#include <cstddef>
#include <cstdint>

namespace libemu::mos6502{

template <memory_bus MemoryBus>
class chip{
public:
    // Registers
    std::uint8_t get_a() const{ return a; };
    std::uint8_t get_x() const{ return x; };
    std::uint8_t get_y() const{ return y; };
    bool get_n() const{ return n; };
    bool get_v() const{ return v; };
    bool get_d() const{ return d; };
    bool get_i() const{ return i; };
    bool get_z() const{ return z; };
    bool get_c() const{ return c; };
    std::uint8_t get_sp() const{ return sp; }
    std::uint16_t get_pc() const{ return pc; }

    // Pins
    bool get_irq() const{ return irq; };
    bool get_nmi() const{ return nmi; };
    bool get_res() const{ return res; };
    bool get_syn() const{ return syn; };
    bool get_rdy() const{ return rdy; };
    void set_irq(bool v){ irq = v; }
    void set_nmi(bool v){ nmi = v; }
    void set_res(bool v){ res = v; }
    void set_rdy(bool v){ rdy = v; }

    // Implementation logic
    std::size_t get_sub_cycle() const{ return current_ucode - ucode_start; }
    std::size_t get_cycle() const{ return current_cycle; }

    bool get_started() const{ return started; }
    bool get_halted() const{ return halted; }

private:
    // Registers
    std::uint8_t a;
    std::uint8_t x;
    std::uint8_t y;
    union{
        std::uint8_t ps;
        struct{
            std::uint8_t n : 1;
            std::uint8_t v : 1;
            std::uint8_t   : 1;
            std::uint8_t b : 1;
            std::uint8_t d : 1;
            std::uint8_t i : 1;
            std::uint8_t z : 1;
            std::uint8_t c : 1;
        };
    };
    std::uint8_t sp;
    std::uint16_t pc;

    // Pins
    std::uint8_t irq : 1;
    std::uint8_t nmi : 1;
    std::uint8_t res : 1;
    std::uint8_t syn : 1;
    std::uint8_t rdy : 1;

    // Latches
    std::uint8_t nmi_latch : 1;
    std::uint8_t data;
    std::uint8_t addr_low;
    std::uint8_t addr_high;

    // Memory bus
    MemoryBus& bus;

    // Implementation logic
    std::size_t current_cycle;
    const ucode* current_ucode;
    const ucode* ucode_start;
    uint8_t page_crossed : 1;
    uint8_t started : 1;
    uint8_t halted : 1;

    std::uint16_t get_addr() const{ return (uint16_t(addr_high) << 8) | addr_low; }

    void handle_pre_instr(uint8_t pre_instr);

    void handle_instr(uint8_t instr);
};

}

#endif