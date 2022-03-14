#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

void DecA::eval(CPU& cpu) const { cpu.a--; }
c_string DecA::disassemble(CPU const&) const
{
    return "dec A";
}
c_string DecA::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a-1);
    return buf;
}

void DecB::eval(CPU& cpu) const { cpu.b--; }
c_string DecB::disassemble(CPU const&) const
{
    return "dec B";
}
c_string DecB::changes(CPU const& cpu) const
{
    static char buf[8];
    snprintf(buf, sizeof(buf), "B=>0x%.2X", cpu.b-1);
    return buf;
}

void DecC::eval(CPU& cpu) const { cpu.c--; }
c_string DecC::disassemble(CPU const&) const
{ 
    return "dec C";
}
c_string DecC::changes(CPU const& cpu) const
{
    static char buf[8];
    snprintf(buf, sizeof(buf), "C=>0x%.2X", cpu.c-1);
    return buf;
}

void DecD::eval(CPU& cpu) const { cpu.d--; }
c_string DecD::disassemble(CPU const&) const
{
    return "dec D";
}
c_string DecD::changes(CPU const& cpu) const
{
    static char buf[10];
    snprintf(buf, sizeof(buf), "D=>0x%.4X", cpu.d-1);
    return buf;
}

void DecE::eval(CPU& cpu) const { cpu.e--; }
c_string DecE::disassemble(CPU const&) const
{
    return "dec E";
}
c_string DecE::changes(CPU const& cpu) const
{
    static char buf[8];
    snprintf(buf, sizeof(buf), "E=>0x%.2X", cpu.e-1);
    return buf;
}

void DecH::eval(CPU& cpu) const { cpu.h--; }
c_string DecH::disassemble(CPU const&) const
{
    return "dec H";
}
c_string DecH::changes(CPU const& cpu) const
{
    // H=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "H=>0x%.2X", cpu.h-1);
    return buf;
}

void DecL::eval(CPU& cpu) const { cpu.l--; }
c_string DecL::disassemble(CPU const&) const
{
    return "dec L";
}
c_string DecL::changes(CPU const& cpu) const
{
    // L=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "L=>0x%.2X", cpu.l-1);
    return buf;
}

void DecBc::eval(CPU& cpu) const { cpu.bc--; }
c_string DecBc::disassemble(CPU const&) const
{
    return "dec BC";
}
c_string DecBc::changes(CPU const& cpu) const
{
    static char buf[11];
    snprintf(buf, sizeof(buf), "BC=>0x%.4X", cpu.bc-1);
    return buf;
}

void DecDe::eval(CPU& cpu) const { cpu.de--; }
c_string DecDe::disassemble(CPU const&) const
{
    return "dec DE";
}
c_string DecDe::changes(CPU const& cpu) const
{
    static char buf[11];
    snprintf(buf, sizeof(buf), "DE=>0x%.4X", cpu.de-1);
    return buf;
}

void DecHl::eval(CPU& cpu) const { cpu.hl--; }
c_string DecHl::disassemble(CPU const&) const
{
    return "dec HL";
}
c_string DecHl::changes(CPU const& cpu) const
{
    // HL=>0xFFFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "HL=>0x%.4X", cpu.hl-1);
    return buf;
}

void DecIndexedHl::eval(CPU& cpu) const
{
    cpu.memory[cpu.hl]--;
}
c_string DecIndexedHl::disassemble(CPU const&) const
{
    return "dec [HL]";
}
c_string DecIndexedHl::changes(CPU const& cpu) const
{
    // HL=0xFFFF [HL]=>0xFF
    static char buf[21];
    snprintf(buf, sizeof(buf), "HL=0x%.4X [HL]=>0x%.2X",
            cpu.hl.value, cpu.memory.at(cpu.hl)-1);
    return buf;
}

void DecSp::eval(CPU& cpu) const { cpu.sp--; }
c_string DecSp::disassemble(CPU const&) const
{
    return "dec SP";
}
c_string DecSp::changes(CPU const& cpu) const
{
    // SP=>0xFFFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "SP=>0x%.4X", cpu.sp-1);
    return buf;
}


}
