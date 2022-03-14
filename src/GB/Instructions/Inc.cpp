#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

void IncA::eval(CPU& cpu) const { cpu.a++; }
c_string IncA::disassemble(CPU const&) const
{
    return "inc A";
}
c_string IncA::changes(CPU const& cpu) const
{
    // A=>0xFFFF
    static char buf[10];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a+1);
    return buf;
}

void IncB::eval(CPU& cpu) const { cpu.b++; }
c_string IncB::disassemble(CPU const&) const
{
    return "inc B";
}
c_string IncB::changes(CPU const& cpu) const
{
    static char buf[8];
    snprintf(buf, sizeof(buf), "B=>0x%.2X", cpu.b+1);
    return buf;
}

void IncC::eval(CPU& cpu) const { cpu.c++; }
c_string IncC::disassemble(CPU const&) const
{
    return "inc C";
}
c_string IncC::changes(CPU const& cpu) const
{
    static char buf[8];
    snprintf(buf, sizeof(buf), "C=>0x%.2X", cpu.c+1);
    return buf;
}

void IncD::eval(CPU& cpu) const { cpu.d++; }
c_string IncD::disassemble(CPU const&) const
{
    return "inc D";
}
c_string IncD::changes(CPU const& cpu) const
{
    static char buf[10];
    snprintf(buf, sizeof(buf), "D=>0x%.4X", cpu.d+1);
    return buf;
}

void IncE::eval(CPU& cpu) const { cpu.e++; }
c_string IncE::disassemble(CPU const&) const
{
    return "inc E";
}
c_string IncE::changes(CPU const& cpu) const
{
    static char buf[8];
    snprintf(buf, sizeof(buf), "E=>0x%.2X", cpu.e+1);
    return buf;
}

void IncH::eval(CPU& cpu) const { cpu.h++; }
c_string IncH::disassemble(CPU const&) const 
{
    return "inc H";
}
c_string IncH::changes(CPU const& cpu) const
{
    // H=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "H=>0x%.2X", cpu.h+1);
    return buf;
}

void IncL::eval(CPU& cpu) const { cpu.l++; }
c_string IncL::disassemble(CPU const&) const
{
    return "inc L";
}
c_string IncL::changes(CPU const& cpu) const
{
    // L=>0xFFFF
    static char buf[10];
    snprintf(buf, sizeof(buf), "L=>0x%.2X", cpu.l+1);
    return buf;
}

void IncBc::eval(CPU& cpu) const { cpu.bc++; }
c_string IncBc::disassemble(CPU const&) const
{
    return "inc BC";
}
c_string IncBc::changes(CPU const& cpu) const
{
    static char buf[11];
    snprintf(buf, sizeof(buf), "BC=>0x%.4X", cpu.bc+1);
    return buf;
}

void IncDe::eval(CPU& cpu) const { cpu.de++; }
c_string IncDe::disassemble(CPU const&) const
{
    return "inc DE";
}
c_string IncDe::changes(CPU const& cpu) const
{
    static char buf[11];
    snprintf(buf, sizeof(buf), "DE=>0x%.4X", cpu.de+1);
    return buf;
}

void IncHl::eval(CPU& cpu) const { cpu.hl++; }
c_string IncHl::disassemble(CPU const&) const
{
    return "inc HL";
}
c_string IncHl::changes(CPU const& cpu) const
{
    // HL=>0xFFFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "HL=>0x%.4X", cpu.hl+1);
    return buf;
}

void IncSp::eval(CPU& cpu) const { cpu.sp++; }
c_string IncSp::disassemble(CPU const&) const
{
    return "inc SP";
}
c_string IncSp::changes(CPU const& cpu) const
{
    // SP=>0xFFFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "SP=>0x%.4X", cpu.sp+1);
    return buf;
}

void IncIndexedHl::eval(CPU& cpu) const
{
    cpu.memory[cpu.hl]++;
}
c_string IncIndexedHl::disassemble(CPU const&) const
{
    return "inc [HL]";
}
c_string IncIndexedHl::changes(CPU const& cpu) const
{
    // HL=0xFFFF [HL]=>0xFF
    static char buf[21];
    snprintf(buf, sizeof(buf), "HL=0x%.4X [HL]=>0x%.2X",
            cpu.hl.value, cpu.memory.at(cpu.hl)+1);
    return buf;
}

}
