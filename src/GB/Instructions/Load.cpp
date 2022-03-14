#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

void LoadHImm8::eval(CPU& cpu) const { cpu.h = m_imm8; }
c_string LoadHImm8::disassemble(CPU const&) const
{
    // ld H, 0xFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "ld H, 0x%.2X", m_imm8);
    return buf;
}
c_string LoadHImm8::changes(CPU const&) const
{
    return "";
}

void LoadAIndexedBc::eval(CPU& cpu) const
{
    cpu.a = cpu.memory.at(cpu.bc); // FIXME: index
}
c_string LoadAIndexedBc::disassemble(CPU const&) const
{
    return "ld A, [BC]";
}
c_string LoadAIndexedBc::changes(CPU const& cpu) const
{
    // A=[0xFFFF] A=>0xFF
    static char buf[19];
    snprintf(buf, sizeof(buf), "A=[0x%.4X] A=>0x%.2X",
             cpu.bc.value, cpu.memory.at(cpu.bc));
    return buf;
}

void LoadAIndexedDe::eval(CPU& cpu) const
{
    cpu.a = cpu.memory.at(cpu.de); // FIXME: index
}
c_string LoadAIndexedDe::disassemble(CPU const&) const
{
    return "ld A, [DE]";
}
c_string LoadAIndexedDe::changes(CPU const& cpu) const
{
    // DE=0xFFFF A=>0xFFFF
    static char buf[21];
    snprintf(buf, sizeof(buf), "DE=0x%.4X A=>0x%.4X",
            cpu.de.value, cpu.memory.at(cpu.de));
    return buf;
}

void LoadBImm8::eval(CPU& cpu) const { cpu.b = m_imm8; }
c_string LoadBImm8::disassemble(CPU const&) const
{
    // ld B, 0xFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "ld B, 0x%.2X", m_imm8);
    return buf;
}
c_string LoadBImm8::changes(CPU const&) const
{
    return "";
}

void LoadCImm8::eval(CPU& cpu) const { cpu.c = m_imm8; }
c_string LoadCImm8::disassemble(CPU const&) const
{
    // ld C, 0xFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "ld C, 0x%.2X", m_imm8);
    return buf;
}
c_string LoadCImm8::changes(CPU const&) const
{
    return "";
}

void LoadIndexedHlImm8::eval(CPU& cpu) const
{
    cpu.memory[cpu.hl] = m_imm8;
}
c_string LoadIndexedHlImm8::disassemble(CPU const&) const
{
    // ld [HL], 0xFF
    static char buf[14];
    snprintf(buf, sizeof(buf), "ld [HL], 0x%.2X", m_imm8);
    return buf;
}
c_string LoadIndexedHlImm8::changes(CPU const&) const
{
    return "";
}

void LoadAImm8::eval(CPU& cpu) const { cpu.a = m_imm8; }
c_string LoadAImm8::disassemble(CPU const&) const
{
    // ld A, 0xFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "ld A, 0x%.2X", m_imm8);
    return buf;
}
c_string LoadAImm8::changes(CPU const&) const
{
    return "";
}

void LoadAIndexedHlminus::eval(CPU& cpu) const
{
    cpu.a = cpu.memory.at(--cpu.hl);
}
c_string LoadAIndexedHlminus::disassemble(CPU const&) const
{
    return "ld A, [HL-]";
}
c_string LoadAIndexedHlminus::changes(CPU const& cpu) const
{
    // A=>0xFF HL=>0xFFFF
    static char buf[19];
    snprintf(buf, sizeof(buf), "A=>0x%.2X HL=>0x%.4X",
            cpu.memory.at(cpu.hl), cpu.hl-1);
    return buf;
}

void LoadIndexedHlminusA::eval(CPU& cpu) const
{
    cpu.memory[--cpu.hl] = cpu.a;
}
c_string LoadIndexedHlminusA::disassemble(CPU const&) const
{
    return "ld [HL-], A";
}
c_string LoadIndexedHlminusA::changes(CPU const& cpu) const
{
    // A=0xFF HL=>0xFFFF
    static char buf[18];
    snprintf(buf, sizeof(buf), "A=0x%.2X HL=>0x%.4X", cpu.a.value, cpu.hl-1);
    return buf;
}

void LoadSpImm16::eval(CPU& cpu) const
{
    cpu.sp = m_imm16;
}
c_string LoadSpImm16::disassemble(CPU const&) const
{
    // ld SP, 0xFFFF
    static char buf[16];
    snprintf(buf, sizeof(buf), "ld SP, 0x%.4X", m_imm16);
    return buf;
}
c_string LoadSpImm16::changes(CPU const&) const
{
    return "";
}

void LoadLImm8::eval(CPU& cpu) const { cpu.l = m_imm8; }
c_string LoadLImm8::disassemble(CPU const&) const
{
    // ld L, 0xFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "ld L, 0x%.2X", m_imm8);
    return buf;
}
c_string LoadLImm8::changes(CPU const&) const
{
    return "";
}

void LoadAIndexedHlplus::eval(CPU& cpu) const
{
    cpu.a = cpu.memory.at(cpu.hl++);
}
c_string LoadAIndexedHlplus::disassemble(CPU const&) const
{
    return "ld A, [HL+]";
}
c_string LoadAIndexedHlplus::changes(CPU const& cpu) const
{
    // A=>0xFF HL=>0xFFFF
    static char buf[19];
    snprintf(buf, sizeof(buf), "A=>0x%.2X HL=>0x%.4X",
            cpu.memory.at(cpu.hl), cpu.hl+1);
    return buf;
}

void LoadIndexedHlplusA::eval(CPU& cpu) const
{
    cpu.memory[cpu.hl++] = cpu.a;
}
c_string LoadIndexedHlplusA::disassemble(CPU const&) const
{
    return "ld [HL+], A";
}
c_string LoadIndexedHlplusA::changes(CPU const& cpu) const
{
    // A=0xFF HL=>0xFFFF
    static char buf[18];
    snprintf(buf, sizeof(buf), "A=0x%.2X HL=>0x%.4X", cpu.a.value, cpu.hl+1);
    return buf;
}

void LoadHlImm16::eval(CPU& cpu) const
{
    cpu.hl = m_imm16;
}
c_string LoadHlImm16::disassemble(CPU const&) const
{
    // ld HL, 0xFFFF
    static char buf[16];
    snprintf(buf, sizeof(buf), "ld HL, 0x%.4X", m_imm16);
    return buf;
}
c_string LoadHlImm16::changes(CPU const&) const
{
    return "";
}

void LoadEImm8::eval(CPU& cpu) const { cpu.e = m_imm8; }
c_string LoadEImm8::disassemble(CPU const&) const
{
    // ld B, 0xFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "ld E, 0x%.2X", m_imm8);
    return buf;
}
c_string LoadEImm8::changes(CPU const&) const
{
    return "";
}

void LoadDImm8::eval(CPU& cpu) const { cpu.d = m_imm8; }
c_string LoadDImm8::disassemble(CPU const&) const
{
    // ld D, 0xFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "ld D, 0x%.2X", m_imm8);
    return buf;
}
c_string LoadDImm8::changes(CPU const&) const
{
    return "";
}

void LoadBcImm16::eval(CPU& cpu) const
{
    cpu.bc = m_imm16;
}
c_string LoadBcImm16::disassemble(CPU const&) const
{
    // ld BC, 0xFFFF
    static char buf[16];
    snprintf(buf, sizeof(buf), "ld BC, 0x%.4X", m_imm16);
    return buf;
}
c_string LoadBcImm16::changes(CPU const&) const
{
    return "";
}

void LoadDeImm16::eval(CPU& cpu) const
{
    cpu.de = m_imm16;
}
c_string LoadDeImm16::disassemble(CPU const&) const
{
    // ld BC, 0xFFFF
    static char buf[16];
    snprintf(buf, sizeof(buf), "ld DE, 0x%.4X", m_imm16);
    return buf;
}
c_string LoadDeImm16::changes(CPU const&) const
{
    return "";
}

void LoadIndexedBcA::eval(CPU& cpu) const
{
    cpu.memory[cpu.bc] = cpu.a;
}
c_string LoadIndexedBcA::disassemble(CPU const&) const
{
    return "ld [BC], A";
}
c_string LoadIndexedBcA::changes(CPU const& cpu) const
{
    // [0xFFFF]=0xFF
    static char buf[14];
    snprintf(buf, sizeof(buf), "[0x%.4X]=0x%.2X",
             cpu.bc.value, cpu.a.value);
    return buf;
}

void LoadIndexedDeA::eval(CPU& cpu) const
{
    cpu.memory[cpu.de] = cpu.a;
}
c_string LoadIndexedDeA::disassemble(CPU const&) const
{
    return "ld [DE], A";
}
c_string LoadIndexedDeA::changes(CPU const& cpu) const
{
    // [0xFFFF]=0xFF
    static char buf[14];
    snprintf(buf, sizeof(buf), "[0x%.4X]=0x%.2X",
             cpu.de.value, cpu.a.value);
    return buf;
}

void LoadIndexedImm16Sp::eval(CPU& cpu) const
{
    cpu.memory[m_imm16] = cpu.sp.upper();
    cpu.memory[m_imm16+1] = cpu.sp.lower();
}
c_string LoadIndexedImm16Sp::disassemble(CPU const&) const
{
    // ld [0xFFFF], SP
    static char buf[16];
    snprintf(buf, sizeof(buf), "ld [0x%.4X], SP", m_imm16);
    return buf;
}
c_string LoadIndexedImm16Sp::changes(CPU const& cpu) const
{
    // [0xFFFF]=0xFFFF
    static char buf[16];
    snprintf(buf, sizeof(buf), "[0x%.4X]=0x%.4X",
             m_imm16, cpu.sp.value);
    return buf;
}

#define LOAD_INSTRUCTION(to_asm, from_asm, to, from)    \
void Load##to_asm##from_asm::eval(CPU& cpu) const       \
{                                                       \
    cpu.to = cpu.from;                                  \
}                                                       \
c_string Load##to_asm##from_asm::disassemble(CPU const&) const \
{                                                       \
    return "ld " #to_asm ", " #from_asm;                \
}                                                       \
c_string Load##to_asm##from_asm::changes(CPU const& cpu) const \
{                                                       \
    /* A=>0xFF */                                       \
    static char buf[8];                                 \
    snprintf(buf, sizeof(buf), #to_asm "=>0x%.2X", cpu.from.value); \
    return buf;                                         \
}

#define LOAD_REGISTER_MEMORY(to_asm, to)                \
void Load##to_asm##IndexedHl::eval(CPU& cpu) const      \
{                                                       \
    cpu.to = cpu.memory.at(cpu.hl);                     \
}                                                       \
c_string Load##to_asm##IndexedHl::disassemble(CPU const&) const \
{                                                       \
    return "ld " #to_asm ", [HL]";                      \
}                                                       \
c_string Load##to_asm##IndexedHl::changes(CPU const& cpu) const \
{                                                       \
    /* A=>0xFF */                                       \
    static char buf[8];                                 \
    snprintf(buf, sizeof(buf), #to_asm "=>0x%.2X",      \
             cpu.memory.at(cpu.hl));                    \
    return buf;                                         \
}

#define LOAD_MEMORY_REGISTER(from_asm, from)            \
void LoadIndexedHl##from_asm::eval(CPU& cpu) const      \
{                                                       \
    cpu.memory[cpu.hl] = cpu.from;                      \
}                                                       \
c_string LoadIndexedHl##from_asm::disassemble(CPU const&) const \
{                                                       \
    return "ld [HL], " #from_asm;                       \
}                                                       \
c_string LoadIndexedHl##from_asm::changes(CPU const& cpu) const \
{                                                       \
    /* [HL]=>0xFF */                                    \
    static char buf[12];                                \
    snprintf(buf, sizeof(buf), "[HL]=>0x%.2X",          \
             cpu.from.value);                           \
    return buf;                                         \
}

LOAD_INSTRUCTION(B, B, b, b);
LOAD_INSTRUCTION(B, C, b, c);
LOAD_INSTRUCTION(B, D, b, d);
LOAD_INSTRUCTION(B, E, b, e);
LOAD_INSTRUCTION(B, H, b, h);
LOAD_INSTRUCTION(B, L, b, l);
LOAD_REGISTER_MEMORY(B, b);
LOAD_INSTRUCTION(B, A, b, a);

LOAD_INSTRUCTION(C, B, c, b);
LOAD_INSTRUCTION(C, C, c, c);
LOAD_INSTRUCTION(C, D, c, d);
LOAD_INSTRUCTION(C, E, c, e);
LOAD_INSTRUCTION(C, H, c, h);
LOAD_INSTRUCTION(C, L, c, l);
LOAD_REGISTER_MEMORY(C, c);
LOAD_INSTRUCTION(C, A, c, a);

LOAD_INSTRUCTION(D, B, d, b);
LOAD_INSTRUCTION(D, C, d, c);
LOAD_INSTRUCTION(D, D, d, d);
LOAD_INSTRUCTION(D, E, d, e);
LOAD_INSTRUCTION(D, H, d, h);
LOAD_INSTRUCTION(D, L, d, l);
LOAD_REGISTER_MEMORY(D, d);
LOAD_INSTRUCTION(D, A, d, a);

LOAD_INSTRUCTION(E, B, e, b);
LOAD_INSTRUCTION(E, C, e, c);
LOAD_INSTRUCTION(E, D, e, d);
LOAD_INSTRUCTION(E, E, e, e);
LOAD_INSTRUCTION(E, H, e, h);
LOAD_INSTRUCTION(E, L, e, l);
LOAD_REGISTER_MEMORY(E, e);
LOAD_INSTRUCTION(E, A, e, a);

LOAD_INSTRUCTION(H, B, h, b);
LOAD_INSTRUCTION(H, C, h, c);
LOAD_INSTRUCTION(H, D, h, d);
LOAD_INSTRUCTION(H, E, h, e);
LOAD_INSTRUCTION(H, H, h, h);
LOAD_INSTRUCTION(H, L, h, l);
LOAD_REGISTER_MEMORY(H, h);
LOAD_INSTRUCTION(H, A, h, a);

LOAD_INSTRUCTION(L, B, l, b);
LOAD_INSTRUCTION(L, C, l, c);
LOAD_INSTRUCTION(L, D, l, d);
LOAD_INSTRUCTION(L, E, l, e);
LOAD_INSTRUCTION(L, H, l, h);
LOAD_INSTRUCTION(L, L, l, l);
LOAD_REGISTER_MEMORY(L, l);
LOAD_INSTRUCTION(L, A, l, a);

LOAD_MEMORY_REGISTER(B, b);
LOAD_MEMORY_REGISTER(C, c);
LOAD_MEMORY_REGISTER(D, d);
LOAD_MEMORY_REGISTER(E, e);
LOAD_MEMORY_REGISTER(H, h);
LOAD_MEMORY_REGISTER(L, l);

LOAD_MEMORY_REGISTER(A, a);

LOAD_INSTRUCTION(A, B, a, b);
LOAD_INSTRUCTION(A, C, a, c);
LOAD_INSTRUCTION(A, D, a, d);
LOAD_INSTRUCTION(A, E, a, e);
LOAD_INSTRUCTION(A, H, a, h);
LOAD_INSTRUCTION(A, L, a, l);
LOAD_REGISTER_MEMORY(A, a);
LOAD_INSTRUCTION(A, A, a, a);

#undef LOAD_INSTRUCTION
#undef LOAD_REGISTER_MEMORY
#undef LOAD_MEMORY_REGISTER


}
