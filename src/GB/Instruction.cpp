#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB::Instruction {

void Nop::eval(CPU&) const { }
c_string Nop::disassemble(CPU const&) const
{
    return "nop";
}
c_string Nop::changes(CPU const&) const
{
    return "";
}

void Halt::eval(CPU&) const
{
    // FIXME: Implement this
}
c_string Halt::disassemble(CPU const&) const
{
    return "halt";
}
c_string Halt::changes(CPU const&) const
{
    return "";
}

void Stop::eval(CPU&) const
{
    // FIXME: Implement this
}
c_string Stop::disassemble(CPU const&) const
{
    return "stop";
}
c_string Stop::changes(CPU const&) const
{
    return "";
}


void Rlca::eval(CPU&) const
{
    // FIXME: Implement this
}
c_string Rlca::disassemble(CPU const&) const
{
    return "rlca";
}
c_string Rlca::changes(CPU const&) const
{
    return "";
}

void Rrca::eval(CPU&) const
{
    // FIXME: Implement this
}
c_string Rrca::disassemble(CPU const&) const
{
    return "rrca";
}
c_string Rrca::changes(CPU const&) const
{
    return "";
}

void Rla::eval(CPU&) const
{
    // FIXME: Implement this
}
c_string Rla::disassemble(CPU const&) const
{
    return "rla";
}
c_string Rla::changes(CPU const&) const
{
    return "";
}

void Rra::eval(CPU&) const
{
    // FIXME: Implement this
}
c_string Rra::disassemble(CPU const&) const
{
    return "rra";
}
c_string Rra::changes(CPU const&) const
{
    return "";
}

void Daa::eval(CPU&) const
{
    // FIXME: Implement this, convert register A to binary
    //        encoded decimal
}
c_string Daa::disassemble(CPU const&) const
{
    return "daa";
}
c_string Daa::changes(CPU const&) const
{
    return "";
}

void Cpl::eval(CPU& cpu) const
{
    cpu.a = ~cpu.a;
}
c_string Cpl::disassemble(CPU const&) const
{
    return "cpl a";
}

c_string Cpl::changes(CPU const& cpu) const
{
    // A=>0xFF
    static char buf[8];
    snprintf(buf, sizeof(buf), "A=>0x%.2X", ~cpu.a.value);
    return buf;
}

void Scf::eval(CPU& cpu) const
{
    cpu.f.carry = true;
}
c_string Scf::disassemble(CPU const&) const
{
    return "scf";
}
c_string Scf::changes(CPU const&) const
{
    return "";
}

void Ccf::eval(CPU& cpu) const
{
    cpu.f.carry = !cpu.f.carry;
}
c_string Ccf::disassemble(CPU const&) const
{
    return "ccf";
}
c_string Ccf::changes(CPU const&) const
{
    return "";
}

}

namespace GB::ExtendedInstruction {


}
