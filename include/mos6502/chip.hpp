#ifndef MOS6502_MOS6502_HEADER
#define MOS6502_MOS6502_HEADER

#include "micro_code.hpp"

#include <cstdint>

// TODO: Implement decimal mode logic
// TODO: Finish implementing ucode instructions for all opcodes

template <class MemoryBus>
class MOS6502_Chip{
public:
    MOS6502_Chip(MemoryBus& bi) : bus(bi){
        processing_irq = false;
        processing_nmi = false;

        started = false;
        halted = false;

        ucode_ptr = nullptr;

        cycle_index = 0;

        operand = 0;
        addr_low = 0;
        addr_high = 0;
    }

    void set_irq(bool val){ irq = val; }
    void set_nmi(bool val){ nmi_latched |= nmi && !val; nmi = val; }
    void set_res(bool val){ res = val; }
    void set_ovf(bool val){ v = val; }
    void set_rdy(bool val){ rdy = val; }

    bool get_irq() const{ return irq; }
    bool get_nmi() const{ return nmi; }
    bool get_res() const{ return res; }
    bool get_ovf() const{ return v; }
    bool get_syn() const{ return syn; }
    bool get_rw() const{ return rw; }

    uint8_t get_a() const{ return a; }
    uint8_t get_x() const{ return x; }
    uint8_t get_y() const{ return y; }
    uint16_t get_pc() const{ return pc; }
    uint8_t get_sp() const{ return sp; }
    
    template <class Condition>
    void tick_cnt_cnd(std::size_t cnt, Condition cnd){
        while (cnt-- && cnd(this)) tick();
    }

    template <class Condition>
    void tick_cnd(Condition cnd){
        while (!cnd(this)) tick();
    }

    void tick_cnt(std::size_t cnt){
        while (cnt--) tick();
    }

    void tick(){
        if (!res){
            started = false;
            halted = false;
            cycle_index = 0;
            return;
        }
        if (!started){
            switch (cycle_index){ // TODO: Is this accurate? 8 cycles?
                case 0: break;
                case 1: i = 1; break;
                case 2: bus.read(this, 0x0100 | (sp--)); break;
                case 3: bus.read(this, 0x0100 | (sp--)); break;
                case 4: bus.read(this, 0x0100 | (sp--)); break;
                case 5: pc = (pc & 0xff00) | bus.read(this, 0xfffc); break;
                case 6: pc = int16_t(bus.read(this, 0xfffd) << 8) | (pc & 0x00ff); break;
                case 7:
                    ucode_ptr = mos6502_ucode_instructions[bus.read(this, pc++)];
                    syn = 1;
                    started = true;
                    break;
            }
            cycle_index++;
            return;
        }
        cycle_index++;

        void* ucode_table[] = {
            &&DONE,

            &&FETCH_IMPLIED,
            &&FETCH_ACCUMULATOR,
            &&FETCH_IMMEDIATE,

            &&FETCH_ADDR,
            &&FETCH_ADDR_LOW,
            &&FETCH_ADDR_HIGH_PX,
            &&FETCH_ADDR_HIGH_PY,
            &&FETCH_ADDR_HIGH,

            &&FETCH_EFF_ADDR_LOW,
            &&FETCH_EFF_ADDR_HIGH_PY,
            &&FETCH_EFF_ADDR_HIGH,

            &&ADDR_PX,
            &&ADDR_PY,
            &&PUNISH_PAGE,
            &&READ_OPERAND,
            &&WRITE_OPERAND,

            &&INSTRUCTION_BEGIN,

            &&LDA, &&STA, &&LDX, &&STX, &&LDY, &&STY
        };
        bool page_crossed = false;

        if (*ucode_ptr == MOS6502_uCode::DONE){
            ucode_ptr = mos6502_ucode_instructions[bus.read(this, (pc += rdy) - rdy)];
            syn = 1;
            return;
        }
        else syn = 0;

        uint16_t tmp_operand;

        goto *ucode_table[static_cast<std::size_t>(*((ucode_ptr += rdy) - rdy))]; // Handles reads/writes
        HANDLE_UCODE:
        if (*ucode_ptr > MOS6502_uCode::INSTRUCTION_BEGIN) goto *ucode_table[static_cast<std::size_t>(*((ucode_ptr += rdy) - rdy))]; // Handles instructions
        else goto DONE;

        FETCH_IMPLIED    : operand = bus.read(this, pc);                goto HANDLE_UCODE;
        FETCH_ACCUMULATOR: operand = bus.read(this, pc);                goto HANDLE_UCODE;
        FETCH_IMMEDIATE  : operand = bus.read(this, (pc += rdy) - rdy); goto HANDLE_UCODE;

        FETCH_ADDR        : addr_high = 0;
        FETCH_ADDR_LOW    : addr_low = bus.read(this, (pc += rdy) - rdy);      goto HANDLE_UCODE;
        FETCH_ADDR_HIGH_PX: page_crossed = x > 0xff - addr_low; addr_low += x; goto FETCH_ADDR_HIGH; // TODO: Check if this is correct
        FETCH_ADDR_HIGH_PY: page_crossed = y > 0xff - addr_low; addr_low += y; goto FETCH_ADDR_HIGH; // TODO: Check if this is correct
        FETCH_ADDR_HIGH   : addr_high = bus.read(this, (pc += rdy) - rdy);     goto HANDLE_UCODE;

        FETCH_EFF_ADDR_LOW    : operand = bus.read(this, addr_low);                           goto HANDLE_UCODE;
        FETCH_EFF_ADDR_HIGH_PY: page_crossed = y > 0xff - operand; operand += y;              goto FETCH_EFF_ADDR_HIGH; // TODO: Check if this is correct
        FETCH_EFF_ADDR_HIGH   : addr_high = bus.read(this, addr_low + 1); addr_low = operand; goto HANDLE_UCODE;

        ADDR_PX     : operand += x; goto HANDLE_UCODE;
        ADDR_PY     : operand += y; goto HANDLE_UCODE;
        PUNISH_PAGE :
        READ_OPERAND:
            if (*ucode_ptr == MOS6502_uCode::PUNISH_PAGE){
                if (page_crossed){
                    page_crossed = false;
                    addr_high++;
                    goto PUNISH_PAGE;
                } else ucode_ptr++;
            }
            operand = bus.read(this, (uint16_t(addr_high) << 8) | addr_low);
            goto HANDLE_UCODE;
        WRITE_OPERAND: bus.write(this, (uint16_t(addr_high) << 8) | addr_low, operand); goto HANDLE_UCODE;

        LDA: a = operand;                                               goto DONE;
        STA: bus.write(this, (uint16_t(addr_high) << 8) | addr_low, a); goto DONE;
        LDX: x = operand;                                               goto DONE;
        STX: bus.write(this, (uint16_t(addr_high) << 8) | addr_low, x); goto DONE;
        LDY: y = operand;                                               goto DONE;
        STY: bus.write(this, (uint16_t(addr_high) << 8) | addr_low, y); goto DONE;

        TAX: x = a; goto DONE;
        TXA: a = x; goto DONE;
        TAY: y = a; goto DONE;
        TYA: a = y; goto DONE;

        ADC: a = tmp_operand = uint16_t(a) + operand + c; goto PROCESS_FLAGS_ARITH_ADD;
        SBC: a = tmp_operand = uint16_t(a) + ~operand + c; goto PROCESS_FLAGS_ARITH_SUB; // TODO: Check if this works
        INC: bus.write(this, (uint16_t(addr_high) << 8) | addr_low, tmp_operand = operand + 1); goto PROCESS_FLAGS_NZ;
        DEC: bus.write(this, (uint16_t(addr_high) << 8) | addr_low, tmp_operand = operand - 1); goto PROCESS_FLAGS_NZ;
        INX: tmp_operand = x + 1; x = tmp_operand; goto PROCESS_FLAGS_NZ;
        DEX: tmp_operand = x - 1; x = tmp_operand; goto PROCESS_FLAGS_NZ;
        INY: tmp_operand = y + 1; y = tmp_operand; goto PROCESS_FLAGS_NZ;
        DEY: tmp_operand = y - 1; y = tmp_operand; goto PROCESS_FLAGS_NZ;

        PROCESS_FLAGS_ARITH_ADD: c = tmp_operand > 0xff; goto PROCESS_FLAGS_ARITH;
        PROCESS_FLAGS_ARITH_SUB: c = tmp_operand > a;    goto PROCESS_FLAGS_ARITH;
        PROCESS_FLAGS_ARITH: v = (tmp_operand ^ a) & (tmp_operand ^ operand) & 0x80;
        PROCESS_FLAGS_NZ: z = tmp_operand == 0; n = tmp_operand & 0x80; goto DONE;

        INSTRUCTION_BEGIN:
        DONE:
        return;
    }

    std::size_t get_cycle_index() const{
        return cycle_index;
    }

private:
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
    std::uint16_t pc;
    std::uint8_t sp;
    std::uint8_t irq         : 1;
    std::uint8_t nmi         : 1;
    std::uint8_t nmi_latched : 1;
    std::uint8_t res         : 1;
    std::uint8_t rdy         : 1;
    std::uint8_t syn         : 1;
    std::uint8_t rw          : 1;
    MemoryBus& bus;

    std::uint8_t processing_irq : 1;
    std::uint8_t processing_nmi : 1;

    std::uint8_t started : 1;
    std::uint8_t halted  : 1;

    const MOS6502_uCode* ucode_ptr;

    std::size_t cycle_index;
    uint8_t page_crossed : 1;

    uint16_t operand;
    uint8_t addr_low;
    uint8_t addr_high;
};

#endif