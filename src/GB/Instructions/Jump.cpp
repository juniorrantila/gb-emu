#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

void JumpRelativeSignedImm8::eval(CPU& cpu) const
{
    cpu.pc += m_imm8;
    cpu.took_branch = true;
}
c_string JumpRelativeSignedImm8::disassemble(CPU const&) const
{
    // jr -127
    static char buf[8];
    snprintf(buf, sizeof(buf), "jr %d", m_imm8);
    return buf;
}
c_string JumpRelativeSignedImm8::changes(CPU const& cpu) const
{
    // PC=>0xFFFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "PC=>0x%.4X",
             cpu.pc+m_imm8);
    return buf;
}

void JumpRelativeZeroSignedImm8::eval(CPU& cpu) const
{
    if (cpu.f.zero) {
        cpu.pc += m_imm8;
        cpu.took_branch = true;
    }
}
c_string JumpRelativeZeroSignedImm8::disassemble(CPU const&) const
{
    // jrz -127
    static char buf[9];
    snprintf(buf, sizeof(buf), "jrz %d", m_imm8);
    return buf;
}
c_string JumpRelativeZeroSignedImm8::changes(CPU const& cpu) const
{
    if (cpu.f.zero)
        return "did jump";
    return "did not jump";
}

void JumpRelativeNotZeroSignedImm8::eval(CPU& cpu) const
{
    if (!cpu.f.zero) {
        cpu.pc += m_imm8;
        cpu.took_branch = true;
    }
}
c_string JumpRelativeNotZeroSignedImm8::disassemble(CPU const&) const
{
    // jrnz -127
    static char buf[10];
    snprintf(buf, sizeof(buf), "jrnz %d", m_imm8);
    return buf;
}
c_string JumpRelativeNotZeroSignedImm8::changes(CPU const& cpu) const
{
    if (!cpu.f.zero)
        return "did jump";
    return "did not jump";
}

void JumpRelativeCarrySignedImm8::eval(CPU& cpu) const
{
    if (cpu.f.carry) {
        cpu.pc += m_imm8;
        cpu.took_branch = true;
    }
}
c_string JumpRelativeCarrySignedImm8::disassemble(CPU const&) const
{
    // jrc -127
    static char buf[9];
    snprintf(buf, sizeof(buf), "jrc %d", m_imm8);
    return buf;
}
c_string JumpRelativeCarrySignedImm8::changes(CPU const& cpu) const
{
    if (cpu.took_branch)
        return "did jump";
    return "did not jump";
}

void JumpRelativeNoCarrySignedImm8::eval(CPU& cpu) const
{
    if (!cpu.f.carry) {
        cpu.pc += m_imm8;
        cpu.took_branch = true;
    }
}
c_string JumpRelativeNoCarrySignedImm8::disassemble(CPU const&) const
{
    // jrnc -127
    static char buf[10];
    snprintf(buf, sizeof(buf), "jrnc %d", m_imm8);
    return buf;
}
c_string JumpRelativeNoCarrySignedImm8::changes(CPU const& cpu) const
{
    if (!cpu.f.carry)
        return "did jump";
    return "did not jump";
}

}
