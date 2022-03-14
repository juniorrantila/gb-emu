#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

#define LOGIC_INSTRUCTION(name, ass, eval0, eval1)  \
    void name::eval(CPU& cpu) const                 \
    {                                               \
        eval0;                                      \
    }                                               \
    c_string name::disassemble(CPU const&) const    \
    {                                               \
        return ass;                                 \
    }                                               \
    c_string name::changes(CPU const& cpu) const    \
    {                                               \
        /* A=>0xFF */                               \
        static char buf[8];                         \
        snprintf(buf, sizeof(buf),                  \
                "A=>0x%.2X", eval1);                \
        return buf;                                 \
    }

#define LOGIC_MEMORY_INSTRUCTION(name, ass, eval0, eval1) \
    void name::eval(CPU& cpu) const                 \
    {                                               \
        eval0;                                      \
    }                                               \
    c_string name::disassemble(CPU const&) const    \
    {                                               \
        return ass;                                 \
    }                                               \
    c_string name::changes(CPU const& cpu) const    \
    {                                               \
        /* HL=0xFFFF A=>0xFF */                     \
        static char buf[18];                        \
        snprintf(buf, sizeof(buf),                  \
                "HL=0x%.4X A=>0x%.2X",              \
                cpu.memory.at(cpu.hl),              \
                eval1);                             \
        return buf;                                 \
    }

LOGIC_INSTRUCTION(AndAB, "and A, B",
                  cpu.a &= cpu.b, cpu.a & cpu.b);
LOGIC_INSTRUCTION(AndAC, "and A, C",
                  cpu.a &= cpu.c, cpu.a & cpu.c);
LOGIC_INSTRUCTION(AndAD, "and A, D",
                  cpu.a &= cpu.d, cpu.a & cpu.d);
LOGIC_INSTRUCTION(AndAE, "and A, E",
                  cpu.a &= cpu.e, cpu.a & cpu.e);
LOGIC_INSTRUCTION(AndAH, "and A, H",
                  cpu.a &= cpu.h, cpu.a & cpu.h);
LOGIC_INSTRUCTION(AndAL, "and A, L",
                  cpu.a &= cpu.l, cpu.a & cpu.l);
LOGIC_MEMORY_INSTRUCTION(AndAIndexedHl, "and A, [HL]",
                         cpu.a &= cpu.memory[cpu.hl],
                         cpu.a & cpu.memory.at(cpu.hl));
LOGIC_INSTRUCTION(AndAA, "and A, A",
                  cpu.a &= cpu.a, cpu.a & cpu.a);

LOGIC_INSTRUCTION(XorAB, "xor A, B",
                  cpu.a ^= cpu.b, cpu.a ^ cpu.b);
LOGIC_INSTRUCTION(XorAC, "xor A, C",
                  cpu.a ^= cpu.c, cpu.a ^ cpu.c);
LOGIC_INSTRUCTION(XorAD, "xor A, D",
                  cpu.a ^= cpu.d, cpu.a ^ cpu.d);
LOGIC_INSTRUCTION(XorAE, "xor A, E",
                  cpu.a ^= cpu.e, cpu.a ^ cpu.e);
LOGIC_INSTRUCTION(XorAH, "xor A, H",
                  cpu.a ^= cpu.h, cpu.a ^ cpu.h);
LOGIC_INSTRUCTION(XorAL, "xor A, L",
                  cpu.a ^= cpu.l, cpu.a ^ cpu.l);
LOGIC_MEMORY_INSTRUCTION(XorAIndexedHl, "xor A, [HL]",
                         cpu.a ^= cpu.memory[cpu.hl],
                         cpu.a ^ cpu.memory.at(cpu.hl));
LOGIC_INSTRUCTION(XorAA, "xor A, A",
                  cpu.a ^= cpu.a, cpu.a ^ cpu.a);

LOGIC_INSTRUCTION(OrAB, "or A, B",
                  cpu.a |= cpu.b, cpu.a | cpu.b);
LOGIC_INSTRUCTION(OrAC, "or A, C",
                  cpu.a |= cpu.c, cpu.a | cpu.c);
LOGIC_INSTRUCTION(OrAD, "or A, D",
                  cpu.a |= cpu.d, cpu.a | cpu.d);
LOGIC_INSTRUCTION(OrAE, "or A, E",
                  cpu.a |= cpu.e, cpu.a | cpu.e);
LOGIC_INSTRUCTION(OrAH, "or A, H",
                  cpu.a |= cpu.h, cpu.a | cpu.h);
LOGIC_INSTRUCTION(OrAL, "or A, L",
                  cpu.a |= cpu.l, cpu.a | cpu.l);
LOGIC_MEMORY_INSTRUCTION(OrAIndexedHl, "or A, [HL]",
                         cpu.a |= cpu.memory[cpu.hl],
                         cpu.a | cpu.memory.at(cpu.hl));
LOGIC_INSTRUCTION(OrAA, "or A, A",
                  cpu.a |= cpu.a, cpu.a | cpu.a);

#undef LOGIC_MEMORY_INSTRUCTION
#undef LOGIC_INSTRUCTION

}
