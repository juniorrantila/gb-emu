#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

void AddAA::eval(CPU& cpu) const
{
    cpu.a+=cpu.a;
}
c_string AddAA::disassemble(CPU const&) const
{
    return "add A, A";
}

c_string AddAA::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf),
            "A=>0x%.2X", cpu.a+cpu.a);
    return buf;
}

void AddAB::eval(CPU& cpu) const
{
    cpu.a+=cpu.b;
}
c_string AddAB::disassemble(CPU const&) const
{
    return "add A, B";
}
c_string AddAB::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf),
            "A=>0x%.2X", cpu.a+cpu.b);
    return buf;
}

void AddAC::eval(CPU& cpu) const
{
    cpu.a+=cpu.c;
}
c_string AddAC::disassemble(CPU const&) const
{
    return "add A, C";
}
c_string AddAC::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
                       cpu.a+cpu.c);
    return buf;
}

void AddAD::eval(CPU& cpu) const
{
    cpu.a+=cpu.d;
}
c_string AddAD::disassemble(CPU const&) const
{
    return "add A, D";
}
c_string AddAD::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a+cpu.d);
    return buf;
}

void AddAE::eval(CPU& cpu) const { cpu.a+=cpu.e; }
c_string AddAE::disassemble(CPU const&) const
{
    return "add A, E";
}
c_string AddAE::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a+cpu.e);
    return buf;
}

void AddAH::eval(CPU& cpu) const { cpu.a+=cpu.h; }
c_string AddAH::disassemble(CPU const&) const
{
    return "add A, H";
}
c_string AddAH::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a+cpu.h);
    return buf;
}

void AddAL::eval(CPU& cpu) const
{
    cpu.a+=cpu.l;
}
c_string AddAL::disassemble(CPU const&) const
{
    return "add A, L";
}
c_string AddAL::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a+cpu.l);
    return buf;
}

void AddAIndexedHl::eval(CPU& cpu) const
{
    cpu.a+=cpu.memory[cpu.hl];
}
c_string AddAIndexedHl::disassemble(CPU const&) const
{
    return "add A, [HL]";
}
c_string AddAIndexedHl::changes(CPU const& cpu) const
{
    // add A, [HL]
    static char buf[12];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", cpu.a+cpu.memory.at(cpu.hl));
    return buf;
}

void AddHlBc::eval(CPU& cpu) const
{
    cpu.hl+=cpu.bc;
}
c_string AddHlBc::disassemble(CPU const&) const
{
    return "add HL, BC";
}
c_string AddHlBc::changes(CPU const& cpu) const
{
    // HL=>0xFFFF BC=0xFFFF
    static char buf[21];
    snprintf(buf, sizeof(buf), "HL=>0x%.4X BC=0x%.4X",
             cpu.hl+cpu.bc, cpu.bc.value);
    return buf;
}

void AddHlDe::eval(CPU& cpu) const
{
    cpu.hl+=cpu.de;
}
c_string AddHlDe::disassemble(CPU const&) const
{
    return "add HL, DE";
}
c_string AddHlDe::changes(CPU const& cpu) const
{
    // HL=>0xFFFF DE=0xFFFF
    static char buf[21];
    snprintf(buf, sizeof(buf), "HL=>0x%.4X DE=0x%.4X",
             cpu.hl+cpu.de, cpu.de.value);
    return buf;
}

void AddHlHl::eval(CPU& cpu) const
{
    cpu.hl+=cpu.hl;
}
c_string AddHlHl::disassemble(CPU const&) const
{
    return "add HL, HL";
}
c_string AddHlHl::changes(CPU const& cpu) const
{
    // HL=>0xFFFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "HL=>0x%.2X", cpu.hl+cpu.hl);
    return buf;
}

void AddHlSp::eval(CPU& cpu) const
{
    cpu.hl+=cpu.sp;
}
c_string AddHlSp::disassemble(CPU const&) const
{
    return "add HL, SP";
}
c_string AddHlSp::changes(CPU const& cpu) const
{
    // HL=>0xFFFF
    static char buf[11];
    snprintf(buf, sizeof(buf), "HL=>0x%.4X", cpu.hl.value);
    return buf;
}

void AddCarryAA::eval(CPU& cpu) const
{
    cpu.a+=cpu.a+cpu.f.carry;
}
c_string AddCarryAA::disassemble(CPU const&) const
{
    return "adc A, A";
}
c_string AddCarryAA::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.a+cpu.f.carry);
    return buf;
}

void AddCarryAB::eval(CPU& cpu) const
{
    cpu.a+=cpu.b+cpu.f.carry;
}
c_string AddCarryAB::disassemble(CPU const&) const
{
    return "adc A, B";
}
c_string AddCarryAB::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.b+cpu.f.carry);
    return buf;
}

void AddCarryAC::eval(CPU& cpu) const
{
    cpu.a+=cpu.c+cpu.f.carry;
}
c_string AddCarryAC::disassemble(CPU const&) const
{
    return "adc A, C";
}
c_string AddCarryAC::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.c+cpu.f.carry);
    return buf;
}

void AddCarryAD::eval(CPU& cpu) const
{
    cpu.a+=cpu.d+cpu.f.carry;
}
c_string AddCarryAD::disassemble(CPU const&) const
{
    return "adc A, D";
}
c_string AddCarryAD::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.d+cpu.f.carry);
    return buf;
}

void AddCarryAE::eval(CPU& cpu) const
{
    cpu.a+=cpu.e+cpu.f.carry;
}
c_string AddCarryAE::disassemble(CPU const&) const
{
    return "adc A, E";
}
c_string AddCarryAE::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.e+cpu.f.carry);
    return buf;
}

void AddCarryAH::eval(CPU& cpu) const
{
    cpu.a+=cpu.h+cpu.f.carry;
}
c_string AddCarryAH::disassemble(CPU const&) const
{
    return "adc A, H";
}
c_string AddCarryAH::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.h+cpu.f.carry);
    return buf;
}

void AddCarryAL::eval(CPU& cpu) const
{
    cpu.a+=cpu.l+cpu.f.carry;
}
c_string AddCarryAL::disassemble(CPU const&) const
{
    return "adc A, L";
}
c_string AddCarryAL::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.l+cpu.f.carry);
    return buf;
}

void AddCarryAIndexedHl::eval(CPU& cpu) const
{
    cpu.a+=cpu.memory[cpu.hl]+cpu.f.carry;
}
c_string AddCarryAIndexedHl::disassemble(CPU const&) const
{
    return "adc A, [HL]";
}
c_string AddCarryAIndexedHl::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X",
            cpu.a+cpu.memory.at(cpu.hl)+cpu.f.carry);
    return buf;
}

}
