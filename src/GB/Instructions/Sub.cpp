#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

void SubAA::eval(CPU& cpu) const
{
    cpu.a -= cpu.a;
}
c_string SubAA::disassemble(CPU const&) const
{
    return "sub A, A";
}

c_string SubAA::changes(CPU const&) const
{
    return "A=>0x00";
}

void SubAB::eval(CPU& cpu) const
{
    cpu.a-=cpu.b;
}
c_string SubAB::disassemble(CPU const&) const
{
    return "sub A, B";
}
c_string SubAB::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf),
            "A=>0x%.2X", cpu.a-cpu.b);
    return buf;
}

void SubAC::eval(CPU& cpu) const
{
    cpu.a-=cpu.c;
}
c_string SubAC::disassemble(CPU const&) const
{
    return "sub A, C";
}
c_string SubAC::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
                       cpu.a-cpu.c);
    return buf;
}

void SubAD::eval(CPU& cpu) const
{
    cpu.a-=cpu.d;
}
c_string SubAD::disassemble(CPU const&) const
{
    return "sub A, D";
}
c_string SubAD::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a-cpu.d);
    return buf;
}

void SubAE::eval(CPU& cpu) const { cpu.a-=cpu.e; }
c_string SubAE::disassemble(CPU const&) const
{
    return "sub A, E";
}
c_string SubAE::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a-cpu.e);
    return buf;
}

void SubAH::eval(CPU& cpu) const { cpu.a-=cpu.h; }
c_string SubAH::disassemble(CPU const&) const
{
    return "sub A, H";
}
c_string SubAH::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a-cpu.h);
    return buf;
}

void SubAL::eval(CPU& cpu) const
{
    cpu.a-=cpu.l;
}
c_string SubAL::disassemble(CPU const&) const
{
    return "sub A, L";
}
c_string SubAL::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a-cpu.l);
    return buf;
}

void SubAIndexedHl::eval(CPU& cpu) const
{
    cpu.a-=cpu.memory[cpu.hl];
}
c_string SubAIndexedHl::disassemble(CPU const&) const
{
    return "sub A, [HL]";
}
c_string SubAIndexedHl::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[12];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            uint8_t(cpu.a-cpu.memory.at(cpu.hl)));
    return buf;
}

void SubCarryAA::eval(CPU& cpu) const
{
    cpu.a-=cpu.a+cpu.f.carry;
}
c_string SubCarryAA::disassemble(CPU const&) const
{
    return "adc A, A";
}
c_string SubCarryAA::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.a+cpu.f.carry);
    return buf;
}

void SubCarryAB::eval(CPU& cpu) const
{
    cpu.a-=cpu.b+cpu.f.carry;
}
c_string SubCarryAB::disassemble(CPU const&) const
{
    return "adc A, B";
}
c_string SubCarryAB::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.b+cpu.f.carry);
    return buf;
}

void SubCarryAC::eval(CPU& cpu) const
{
    cpu.a-=cpu.c+cpu.f.carry;
}
c_string SubCarryAC::disassemble(CPU const&) const
{
    return "adc A, C";
}
c_string SubCarryAC::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.c+cpu.f.carry);
    return buf;
}

void SubCarryAD::eval(CPU& cpu) const
{
    cpu.a-=cpu.d+cpu.f.carry;
}
c_string SubCarryAD::disassemble(CPU const&) const
{
    return "adc A, D";
}
c_string SubCarryAD::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.d+cpu.f.carry);
    return buf;
}

void SubCarryAE::eval(CPU& cpu) const
{
    cpu.a-=cpu.e+cpu.f.carry;
}
c_string SubCarryAE::disassemble(CPU const&) const
{
    return "adc A, E";
}
c_string SubCarryAE::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.e+cpu.f.carry);
    return buf;
}

void SubCarryAH::eval(CPU& cpu) const
{
    cpu.a-=cpu.h+cpu.f.carry;
}
c_string SubCarryAH::disassemble(CPU const&) const
{
    return "adc A, H";
}
c_string SubCarryAH::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.h+cpu.f.carry);
    return buf;
}

void SubCarryAL::eval(CPU& cpu) const
{
    cpu.a-=cpu.l+cpu.f.carry;
}
c_string SubCarryAL::disassemble(CPU const&) const
{
    return "adc A, L";
}
c_string SubCarryAL::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.l+cpu.f.carry);
    return buf;
}

void SubCarryAIndexedHl::eval(CPU& cpu) const
{
    cpu.a-=cpu.memory[cpu.hl]+cpu.f.carry;
}
c_string SubCarryAIndexedHl::disassemble(CPU const&) const
{
    return "adc A, [HL]";
}
c_string SubCarryAIndexedHl::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a-cpu.memory.at(cpu.hl)+cpu.f.carry);
    return buf;
}

}
