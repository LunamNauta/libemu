#ifndef LIBEMU_MOS6502_CHIP_HEADER
#define LIBEMU_MOS6502_CHIP_HEADER

#include "memory_bus.hpp"
#include "ucode.hpp"

#include <cstdint>

namespace libemu::mos6502{

template <memory_bus MemoryBus>
class chip{
public:
    // Pins
    bool get_sync() const{ return sync; }
    bool get_rdy() const{ return rdy; }
    bool get_irq() const{ return irq; }
    bool get_nmi() const{ return nmi; }
    bool get_res() const{ return res; }
    bool get_so() const{ return so; }
    bool get_rw() const{ return rw; }
    void set_rdy(bool val){ rdy = val; }
    void set_irq(bool val){ irq = val; }
    void set_nmi(bool val){
        if (nmi && !val) nmi_latch = true;
        nmi = val;
    }
    void set_res(bool val){ res = val; }
    void set_so(bool val){ so = val; }
    std::uint16_t get_address() const{ return (std::uint16_t(addr_high) << 8) | addr_low; }
    std::uint8_t get_data() const{ return data; }

    // Pins phi0 & phi1
    template <class Until>
    void tick_cnt_until(std::size_t cnt, Until until){
        while (cnt-- && !until(this)) tick();
    }
    template <class Until>
    void tick_until(Until until){
        while (!until(this)) tick();
    }
    void tick_cnt(std::size_t cnt){
        while (cnt--) tick();
    }
    void tick();

    // Implementation logic
    std::uint8_t get_sub_cycle() const{ return ucode_curr - ucode_start; }
    std::size_t get_cycle() const{ return cycle_curr; }
    bool get_started() const{ return started; }
    bool get_halted() const{ return halted; } 

private:
    // Registers
    std::uint8_t a;
    std::uint8_t x;
    std::uint8_t y;
    union{
        std::uint8_t status;
        struct{
            std::uint8_t c : 1;
            std::uint8_t z : 1;
            std::uint8_t i : 1;
            std::uint8_t d : 1;
            std::uint8_t b : 1;
            std::uint8_t   : 1;
            std::uint8_t v : 1;
            std::uint8_t n : 1;
        };
    };
    std::uint16_t pc;
    std::uint8_t sp;

    // Pins
    union{
        std::uint8_t pins;
        struct{
            std::uint8_t sync : 1;
            std::uint8_t rdy : 1;
            std::uint8_t irq : 1;
            std::uint8_t nmi : 1;
            std::uint8_t res : 1;
            std::uint8_t so : 1;
            std::uint8_t rw : 1;
        };
    };

    // Latches
    std::uint8_t nmi_latch : 1;
    std::uint8_t addr_low;
    std::uint8_t addr_high;
    std::uint16_t data;

    // Memory bus
    MemoryBus& bus;

    // Implementation logic
    const ucode* ucode_start;
    const ucode* ucode_curr;
    std::uint16_t operand;
    std::size_t cycle_curr;
    std::uint8_t page_crossed : 1;
    std::uint8_t started : 1;
    std::uint8_t halted : 1;

    void handle_pre_instruction(std::uint8_t pre_instr){
        void* jmp_tbl[] = {
            &&FETCH_OPCODE,

            &&FETCH_VALUE,
            &&FETCH_ADDR,
            &&FETCH_ADDR_LOW,
            &&FETCH_ADDR_HIGH_PX,
            &&FETCH_ADDR_HIGH_PY,
            &&FETCH_ADDR_HIGH,

            &&FETCH_POINTER,
            &&FETCH_EFF_ADDR_LOW,
            &&FETCH_EFF_ADDR_HIGH_PY,
            &&FETCH_EFF_ADDR_HIGH,

            &&PUNISH_PAGE,

            &&ADDR_PX,
            &&ADDR_PY,
            &&READ_VALUE,
            &&READ_ADDR_FIX,
            &&READ_ADDR,

            &&WRITE_ADDR
        };

        goto *jmp_tbl[pre_instr];

        FETCH_OPCODE: ucode_start = bus.read((pc += rdy) - rdy); ucode_curr = ucode_start; goto DONE;

        FETCH_VALUE:        data = bus.read((pc += rdy) - rdy);                goto DONE;
        FETCH_ADDR:         addr_high = 0;                                     goto FETCH_ADDR_LOW;
        FETCH_ADDR_LOW:     addr_low = data = bus.read((pc += rdy) - rdy);     goto DONE;
        FETCH_ADDR_HIGH_PX: page_crossed = x > 0xff - addr_low; addr_low += x; goto FETCH_ADDR_HIGH;
        FETCH_ADDR_HIGH_PY: page_crossed = y > 0xff - addr_low; addr_low += y; goto FETCH_ADDR_HIGH;
        FETCH_ADDR_HIGH:    addr_high = data = bus.read((pc += rdy) - rdy);    goto DONE;

        FETCH_POINTER:          operand = data = bus.read((pc += rdy) - rdy);      goto DONE;
        FETCH_EFF_ADDR_LOW:     addr_low = data = bus.read(operand);               goto DONE;
        FETCH_EFF_ADDR_HIGH_PY: page_crossed = y > 0xff - addr_low; addr_low += y; goto FETCH_EFF_ADDR_HIGH;
        FETCH_EFF_ADDR_HIGH:    addr_high = data = bus.read(operand + 1);          goto DONE;

        PUNISH_PAGE:
            if (page_crossed){
                page_crossed = false;
                ucode_curr--;
                goto DONE;
            }
            goto READ_ADDR;

        ADDR_PX:       page_crossed = x > 0xff - addr_low; addr_low += x; goto DONE;
        ADDR_PY:       page_crossed = y > 0xff - addr_low; addr_low += y; goto DONE;
        READ_VALUE:    data = bus.read(pc);                               goto DONE;
        READ_ADDR_FIX: addr_high += page_crossed;                         goto READ_ADDR;
        READ_ADDR:     data = bus.read(get_address());                    goto DONE;

        WRITE_ADDR: data = operand; bus.write(get_address(), data); goto DONE;

        DONE:
        return;
    }

    void handle_instruction(std::uint8_t instr){
        void* jmp_tbl[] = {
            &&LDA, &&STA, &&LDX, &&STX, &&LDY, &&STY,
            &&TAX, &&TXA, &&TAY, &&TYA,
            &&ADC, &&SBC, &&INC, &&DEC, &&INX, &&DEX, &&INY, &&DEY
        };
        std::uint8_t tmp;

        goto *jmp_tbl[instr];

        LDA: a = operand = data;                       goto SET_FLAGS_NZ;
        STA: data = a; bus.write(get_address(), data); goto DONE;
        LDX: x = operand = data;                       goto SET_FLAGS_NZ;
        STX: data = x; bus.write(get_address(), data); goto DONE;
        LDY: y = operand = data;                       goto SET_FLAGS_NZ;
        STY: data = y; bus.write(get_address(), data); goto DONE;

        TAX: x = operand = a; goto SET_FLAGS_NZ;
        TXA: a = operand = x; goto SET_FLAGS_NZ;
        TAY: y = operand = a; goto SET_FLAGS_NZ;
        TYA: a = operand = y; goto SET_FLAGS_NZ;

        ADC: tmp = a; a = operand = std::uint16_t(a) + data + c;        goto SET_FLAGS_ADC;
        SBC: tmp = a; a = operand = std::uint16_t(a) - data + ~c;       goto SET_FLAGS_SBC;
        INC: data = operand = data + 1; bus.write(get_address(), data); goto SET_FLAGS_NZ;
        DEC: data = operand = data - 1; bus.write(get_address(), data); goto SET_FLAGS_NZ;
        INX: data = operand = x + 1; bus.write(get_address(), data);    goto SET_FLAGS_NZ;
        DEX: data = operand = x - 1; bus.write(get_address(), data);    goto SET_FLAGS_NZ;
        INY: data = operand = y + 1; bus.write(get_address(), data);    goto SET_FLAGS_NZ;
        DEY: data = operand = y - 1; bus.write(get_address(), data);    goto SET_FLAGS_NZ;

        // ASL:

        SET_FLAGS_ADC: c = data > 0xff - tmp; v = (operand ^ tmp) & (operand ^ data) & 0x80; goto SET_FLAGS_NZ;
        SET_FLAGS_SBC: c = data > tmp; v = (operand ^ tmp) & (operand ^ ~data) & 0x80;       goto SET_FLAGS_NZ;
        SET_FLAGS_NZ:  z = operand == 0; n = operand & 0x80;                                 goto DONE;

        DONE:
        return;
    }
};

}

#endif