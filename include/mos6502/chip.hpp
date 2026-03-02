#ifndef LIBEMU_MOS6502_CHIP_HEADER
#define LIBEMU_MOS6502_CHIP_HEADER

#include "memory_bus.hpp"
#include "ucode.hpp"

#include <cstdint>

namespace libemu::mos6502{

template <memory_bus MemoryBus>
class chip{
public:
    chip(MemoryBus& bi) : bus(bi), ucode_start(nullptr), ucode_curr(nullptr){}

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
    void tick(){
        if (!res){
            ucode_curr = ucode_start = reset_instructions;
            cycle_curr = 0;
            return;
        }
        cycle_curr++;

        if (!ucode_curr) return;

        if (*ucode_curr == ucode::FETCH_OPCODE){
            ucode_start = instructions[bus.read((pc += rdy) - rdy)];
            ucode_curr = ucode_start + 1;
        }
        else if (*ucode_curr > ucode::INSTRUCTIONS_BEGIN) handle_instruction(static_cast<std::uint8_t>(*ucode_curr) - static_cast<std::uint8_t>(ucode::INSTRUCTIONS_BEGIN) - 1);
        else if (*ucode_curr > ucode::PRE_INSTRUCTIONS_BEGIN) handle_pre_instruction(static_cast<std::uint8_t>(*ucode_curr) - static_cast<std::uint8_t>(ucode::PRE_INSTRUCTIONS_BEGIN) - 1);
        ucode_curr++;
    }

    // Implementation logic
    std::uint8_t get_sub_cycle() const{ return ucode_curr - ucode_start; }
    std::size_t get_cycle() const{ return cycle_curr; }
    bool get_halted() const{ return halted; }

    std::uint8_t get_a() const{ return a; }
    std::uint8_t get_x() const{ return x; }
    std::uint8_t get_y() const{ return y; }
    std::uint16_t get_pc() const{ return pc; }
    std::uint8_t get_sp() const{ return sp; }

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
    std::uint8_t halted : 1;

    bool handle_pre_instruction(std::uint8_t pre_instr){
        void* jmp_tbl[] = {
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

            &&FETCH_RESET_LOW,
            &&FETCH_RESET_HIGH,

            &&PUNISH_PAGE,

            &&ADDR_PX,
            &&ADDR_PY,
            &&READ_VALUE,
            &&READ_ADDR_FIX,
            &&READ_ADDR,

            &&WRITE_ADDR,

            &&PUSH_STACK,
            &&POP_STACK
        };

        sync = pre_instr == 0;
        goto *jmp_tbl[pre_instr];

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

        FETCH_RESET_LOW:  addr_low = data = bus.read(0xfffc);  pc = get_address(); goto DONE;
        FETCH_RESET_HIGH: addr_high = data = bus.read(0xfffd); pc = get_address(); goto DONE;

        PUNISH_PAGE:
            if (page_crossed){
                page_crossed = false;
                ucode_curr--;
                goto DONE;
            }
            return true;

        ADDR_PX:       page_crossed = x > 0xff - addr_low; addr_low += x; goto DONE;
        ADDR_PY:       page_crossed = y > 0xff - addr_low; addr_low += y; goto DONE;
        READ_VALUE:    data = bus.read(pc);                               goto DONE;
        READ_ADDR_FIX: addr_high += page_crossed;                         goto READ_ADDR;
        READ_ADDR:     data = bus.read(get_address());                    goto DONE;

        WRITE_ADDR: data = operand; bus.write(get_address(), data); goto DONE;

        PUSH_STACK: addr_high = 0x01; addr_low = --sp; bus.write(get_address(), data); goto DONE;
        POP_STACK:  addr_high = 0x01; addr_low = sp++; data = bus.read(get_address()); goto DONE;

        DONE:
        return false;
    }

    void handle_instruction(std::uint8_t instr){
        void* jmp_tbl[] = {
            &&LDA, &&STA, &&LDX, &&STX, &&LDY, &&STY,
            &&TAX, &&TXA, &&TAY, &&TYA,
            &&ADC, &&SBC, &&INC, &&DEC, &&INX, &&DEX, &&INY, &&DEY,
            &&ASL, &&LSR, &&ROL, &&ROR,
            &&AND, &&ORA, &&EOR, &&BIT,
            &&CMP, &&CPX, &&CPY,
            &&BCC, &&BCS, &&BEQ, &&BNE, &&BPL, &&BMI, &&BVC, &&BVS,
            &&JMP, &&JSR, &&RTS, &&BRK, &&RTI,
            &&PHA, &&PLA, &&PHP, &&PLP, &&TXS, &&TSX,
            &&CLC, &&SEC, &&CLI, &&SEI, &&CLD, &&SED, &&CLV,
            &&NOP
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

        ADC: tmp = a; a = operand = std::uint16_t(a) + data + c;  goto SET_FLAGS_ADC;
        SBC: tmp = a; a = operand = std::uint16_t(a) - data + ~c; goto SET_FLAGS_SBC;
        INC: data = operand = data + 1;                           goto SET_FLAGS_NZ;
        DEC: data = operand = data - 1;                           goto SET_FLAGS_NZ;
        INX: data = operand = x + 1;                              goto SET_FLAGS_NZ;
        DEX: data = operand = x - 1;                              goto SET_FLAGS_NZ;
        INY: data = operand = y + 1;                              goto SET_FLAGS_NZ;
        DEY: data = operand = y - 1;                              goto SET_FLAGS_NZ;

        ASL: c = data & 0x80; data = operand = data << 1; if (rdy && *ucode_start == ucode::ACCUMULATOR) a = data;                  goto SET_FLAGS_NZ;
        LSR: c = data & 0x01; data = operand = data >> 1; if (rdy && *ucode_start == ucode::ACCUMULATOR) a = data;                  goto SET_FLAGS_NZ;
        ROL: tmp = c; c = data & 0x80; data = operand = (data << 1) | tmp; if (rdy && *ucode_start == ucode::ACCUMULATOR) a = data; goto SET_FLAGS_NZ;
        ROR: tmp = c; c = data & 0x01; data = operand = (data >> 1) | tmp; if (rdy && *ucode_start == ucode::ACCUMULATOR) a = data; goto SET_FLAGS_NZ;

        AND: a = operand = a & data;                 goto SET_FLAGS_NZ;
        ORA: a = operand = a | data;                 goto SET_FLAGS_NZ;
        EOR: a = operand = a ^ data;                 goto SET_FLAGS_NZ;
        BIT: operand = a & data; v = operand & 0x40; goto SET_FLAGS_NZ;

        CMP: c = a >= data; z = a == data; n = a < data; goto DONE;
        CPX: c = x >= data; z = x == data; n = x < data; goto DONE;
        CPY: c = y >= data; z = y == data; n = y < data; goto DONE;

        // TODO: Fix timing
        BCC: if (!c) goto BRANCH; else goto DONE;
        BCS: if (c)  goto BRANCH; else goto DONE;
        BEQ: if (z)  goto BRANCH; else goto DONE;
        BNE: if (!z) goto BRANCH; else goto DONE;
        BPL: if (!n) goto BRANCH; else goto DONE;
        BMI: if (n)  goto BRANCH; else goto DONE;
        BVC: if (!v) goto BRANCH; else goto DONE;
        BVS: if (v)  goto BRANCH; else goto DONE;
        BRANCH: pc = pc + 2 + std::int8_t(data); goto DONE;

        JMP:
        JSR:
        RTS:
        BRK:
        RTI:

        PHA:
        PLA:
        PHP:
        PLP:
        TXS:
        TSX:
        
        CLC:
        SEC:
        CLI:
        SEI:
        CLD:
        SED:
        CLV:

        NOP: goto DONE;

        SET_FLAGS_ADC: c = data > 0xff - tmp; v = (operand ^ tmp) & (operand ^ data) & 0x80; goto SET_FLAGS_NZ;
        SET_FLAGS_SBC: c = data > tmp; v = (operand ^ tmp) & (operand ^ ~data) & 0x80;       goto SET_FLAGS_NZ;
        SET_FLAGS_NZ:  z = operand == 0; n = operand & 0x80;                                 goto DONE;

        DONE:
        return;
    }
};

}

#endif