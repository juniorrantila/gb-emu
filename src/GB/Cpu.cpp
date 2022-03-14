#include <GB/Cpu.h>
#include <GB/Instruction.h>
#include <stdio.h>

namespace GB {

// FIXME: Maybe give access to InstructionTag via template
template <typename T, InstructionTag Tag>
void CPU::disassemble_and_dump(T instruction) const
{
    printf("%.4X:  %.2X ", pc.value, *Tag);
    if constexpr(T::size == 1) {
        printf("       |   ");
    } else if constexpr (T::size == 2) {
        printf("%.2X     |   ", instruction.m_imm8);
    } else if constexpr (T::size == 3) {
        printf("%.2X %.2X  |   ",
                (instruction.m_imm16 & 0xFF00) >> 8,
                instruction.m_imm16 & 0x00FF);
    } else {
        abort();
    }
    auto padding = 16 - printf("%s", instruction.disassemble(*this));
    for (auto i = 0; i<padding; i++) printf(" ");
    printf("| %s\n", instruction.changes(*this));
}

template <typename T, InstructionTag Tag>
[[gnu::flatten]]
void CPU::run_instruction()
{
    took_branch = false;

    // FIXME: Find way to remove the byte array
    union {
        T impl;
        uint8_t bytes[sizeof(T)];
    } static instruction {};

    if constexpr (T::size == 1) {
        static_assert(sizeof(T) == 1);
    } else if constexpr (T::size == 2) {
        static_assert(sizeof(T) == T::size-1);
        instruction.impl.m_imm8 = memory.at(pc+1);
    } else if constexpr (T::size == 3) {
        static_assert(sizeof(T) == T::size-1);
        // FIXME: Figure out why this crashes
        //        when trying to set without
        //        union trick
        instruction.bytes[0] = memory.at(pc+1);
        instruction.bytes[1] = memory.at(pc+2);
    } else {
        abort();
    }

    if (m_print_assembly)
        disassemble_and_dump<T, Tag>(instruction.impl);

    if (!T::reads_flags)
        f.clear();
    instruction.impl.eval(*this);
    if (!T::sets_flags)
        f.clear();

    if (took_branch) {
        sleep_for_cycles(T::long_cycles);
    } else {
        sleep_for_cycles(T::cycles);
        pc.value += T::size;
    }
}

void CPU::run_next_cycles(uint16_t cycles)
{
    m_slept_cycles = 0;
    while (m_slept_cycles < cycles) {
        if (pc >= memory.rom_size())
            break;
        run_next_instruction();
    }
}

void CPU::run_next_instruction()
{
    switch (InstructionTag(memory.at(pc))) {

#define INSTRUCTION_RUN(instruction)                 \
    InstructionTag::instruction:                     \
    run_instruction<Instruction::instruction,        \
                    InstructionTag::instruction>();  \
    break;

    case INSTRUCTION_RUN(Nop);
    case INSTRUCTION_RUN(LoadBcImm16);
    case INSTRUCTION_RUN(LoadIndexedBcA);
    case INSTRUCTION_RUN(IncBc);
    case INSTRUCTION_RUN(IncB);
    case INSTRUCTION_RUN(DecB);
    case INSTRUCTION_RUN(LoadBImm8);
    case INSTRUCTION_RUN(Rlca);
    case INSTRUCTION_RUN(LoadIndexedImm16Sp);
    case INSTRUCTION_RUN(AddHlBc);
    case INSTRUCTION_RUN(LoadAIndexedBc);
    case INSTRUCTION_RUN(DecBc);
    case INSTRUCTION_RUN(IncC);
    case INSTRUCTION_RUN(DecC);
    case INSTRUCTION_RUN(LoadCImm8);
    case INSTRUCTION_RUN(Rrca);
    case INSTRUCTION_RUN(Stop);

    case INSTRUCTION_RUN(LoadDeImm16);
    case INSTRUCTION_RUN(LoadIndexedDeA);
    case INSTRUCTION_RUN(IncDe);
    case INSTRUCTION_RUN(IncD);
    case INSTRUCTION_RUN(DecD);
    case INSTRUCTION_RUN(LoadDImm8);
    case INSTRUCTION_RUN(Rla);
    case INSTRUCTION_RUN(JumpRelativeSignedImm8);
    case INSTRUCTION_RUN(AddHlDe);
    case INSTRUCTION_RUN(LoadAIndexedDe);
    case INSTRUCTION_RUN(DecDe);
    case INSTRUCTION_RUN(IncE);
    case INSTRUCTION_RUN(DecE);
    case INSTRUCTION_RUN(LoadEImm8);
    case INSTRUCTION_RUN(Rra);

    case INSTRUCTION_RUN(JumpRelativeNotZeroSignedImm8);
    case INSTRUCTION_RUN(LoadHlImm16);
    case INSTRUCTION_RUN(LoadIndexedHlplusA);
    case INSTRUCTION_RUN(IncHl);
    case INSTRUCTION_RUN(IncH);
    case INSTRUCTION_RUN(DecH);
    case INSTRUCTION_RUN(LoadHImm8);
    case INSTRUCTION_RUN(Daa);
    case INSTRUCTION_RUN(JumpRelativeZeroSignedImm8);
    case INSTRUCTION_RUN(AddHlHl);
    case INSTRUCTION_RUN(LoadAIndexedHlplus);
    case INSTRUCTION_RUN(DecHl);
    case INSTRUCTION_RUN(IncL);
    case INSTRUCTION_RUN(DecL);
    case INSTRUCTION_RUN(LoadLImm8);
    case INSTRUCTION_RUN(Cpl);

    case INSTRUCTION_RUN(JumpRelativeNoCarrySignedImm8);
    case INSTRUCTION_RUN(LoadSpImm16);
    case INSTRUCTION_RUN(LoadIndexedHlminusA);
    case INSTRUCTION_RUN(IncSp);
    case INSTRUCTION_RUN(IncIndexedHl);
    case INSTRUCTION_RUN(DecIndexedHl);
    case INSTRUCTION_RUN(LoadIndexedHlImm8);
    case INSTRUCTION_RUN(Scf);
    case INSTRUCTION_RUN(JumpRelativeCarrySignedImm8);
    case INSTRUCTION_RUN(AddHlSp);
    case INSTRUCTION_RUN(LoadAIndexedHlminus);
    case INSTRUCTION_RUN(DecSp);
    case INSTRUCTION_RUN(IncA);
    case INSTRUCTION_RUN(DecA);
    case INSTRUCTION_RUN(LoadAImm8);
    case INSTRUCTION_RUN(Ccf);

    case INSTRUCTION_RUN(LoadBB);
    case INSTRUCTION_RUN(LoadBC);
    case INSTRUCTION_RUN(LoadBD);
    case INSTRUCTION_RUN(LoadBE);
    case INSTRUCTION_RUN(LoadBH);
    case INSTRUCTION_RUN(LoadBL);
    case INSTRUCTION_RUN(LoadBIndexedHl);
    case INSTRUCTION_RUN(LoadBA);
    case INSTRUCTION_RUN(LoadCB);
    case INSTRUCTION_RUN(LoadCC);
    case INSTRUCTION_RUN(LoadCD);
    case INSTRUCTION_RUN(LoadCE);
    case INSTRUCTION_RUN(LoadCH);
    case INSTRUCTION_RUN(LoadCL);
    case INSTRUCTION_RUN(LoadCIndexedHl);
    case INSTRUCTION_RUN(LoadCA);

    case INSTRUCTION_RUN(LoadDB);
    case INSTRUCTION_RUN(LoadDC);
    case INSTRUCTION_RUN(LoadDD);
    case INSTRUCTION_RUN(LoadDE);
    case INSTRUCTION_RUN(LoadDH);
    case INSTRUCTION_RUN(LoadDL);
    case INSTRUCTION_RUN(LoadDIndexedHl);
    case INSTRUCTION_RUN(LoadDA);
    case INSTRUCTION_RUN(LoadEB);
    case INSTRUCTION_RUN(LoadEC);
    case INSTRUCTION_RUN(LoadED);
    case INSTRUCTION_RUN(LoadEE);
    case INSTRUCTION_RUN(LoadEH);
    case INSTRUCTION_RUN(LoadEL);
    case INSTRUCTION_RUN(LoadEIndexedHl);
    case INSTRUCTION_RUN(LoadEA);

    case INSTRUCTION_RUN(LoadHB);
    case INSTRUCTION_RUN(LoadHC);
    case INSTRUCTION_RUN(LoadHD);
    case INSTRUCTION_RUN(LoadHE);
    case INSTRUCTION_RUN(LoadHH);
    case INSTRUCTION_RUN(LoadHL);
    case INSTRUCTION_RUN(LoadHIndexedHl);
    case INSTRUCTION_RUN(LoadHA);
    case INSTRUCTION_RUN(LoadLB);
    case INSTRUCTION_RUN(LoadLC);
    case INSTRUCTION_RUN(LoadLD);
    case INSTRUCTION_RUN(LoadLE);
    case INSTRUCTION_RUN(LoadLH);
    case INSTRUCTION_RUN(LoadLL);
    case INSTRUCTION_RUN(LoadLIndexedHl);
    case INSTRUCTION_RUN(LoadLA);

    case INSTRUCTION_RUN(LoadIndexedHlB);
    case INSTRUCTION_RUN(LoadIndexedHlC);
    case INSTRUCTION_RUN(LoadIndexedHlD);
    case INSTRUCTION_RUN(LoadIndexedHlE);
    case INSTRUCTION_RUN(LoadIndexedHlH);
    case INSTRUCTION_RUN(LoadIndexedHlL);
    case INSTRUCTION_RUN(Halt);
    case INSTRUCTION_RUN(LoadIndexedHlA);
    case INSTRUCTION_RUN(LoadAB);
    case INSTRUCTION_RUN(LoadAC);
    case INSTRUCTION_RUN(LoadAD);
    case INSTRUCTION_RUN(LoadAE);
    case INSTRUCTION_RUN(LoadAH);
    case INSTRUCTION_RUN(LoadAL);
    case INSTRUCTION_RUN(LoadAIndexedHl);
    case INSTRUCTION_RUN(LoadAA);

    case INSTRUCTION_RUN(AddAB);
    case INSTRUCTION_RUN(AddAC);
    case INSTRUCTION_RUN(AddAD);
    case INSTRUCTION_RUN(AddAE);
    case INSTRUCTION_RUN(AddAH);
    case INSTRUCTION_RUN(AddAL);
    case INSTRUCTION_RUN(AddAIndexedHl);
    case INSTRUCTION_RUN(AddAA);
    case INSTRUCTION_RUN(AddCarryAB);
    case INSTRUCTION_RUN(AddCarryAC);
    case INSTRUCTION_RUN(AddCarryAD);
    case INSTRUCTION_RUN(AddCarryAE);
    case INSTRUCTION_RUN(AddCarryAH);
    case INSTRUCTION_RUN(AddCarryAL);
    case INSTRUCTION_RUN(AddCarryAIndexedHl);
    case INSTRUCTION_RUN(AddCarryAA);

    case INSTRUCTION_RUN(SubAB);
    case INSTRUCTION_RUN(SubAC);
    case INSTRUCTION_RUN(SubAD);
    case INSTRUCTION_RUN(SubAE);
    case INSTRUCTION_RUN(SubAH);
    case INSTRUCTION_RUN(SubAL);
    case INSTRUCTION_RUN(SubAIndexedHl);
    case INSTRUCTION_RUN(SubAA);
    case INSTRUCTION_RUN(SubCarryAB);
    case INSTRUCTION_RUN(SubCarryAC);
    case INSTRUCTION_RUN(SubCarryAD);
    case INSTRUCTION_RUN(SubCarryAE);
    case INSTRUCTION_RUN(SubCarryAH);
    case INSTRUCTION_RUN(SubCarryAL);
    case INSTRUCTION_RUN(SubCarryAIndexedHl);
    case INSTRUCTION_RUN(SubCarryAA);

    case INSTRUCTION_RUN(AndAB);
    case INSTRUCTION_RUN(AndAC);
    case INSTRUCTION_RUN(AndAD);
    case INSTRUCTION_RUN(AndAE);
    case INSTRUCTION_RUN(AndAH);
    case INSTRUCTION_RUN(AndAL);
    case INSTRUCTION_RUN(AndAIndexedHl);
    case INSTRUCTION_RUN(AndAA);
    case INSTRUCTION_RUN(XorAB);
    case INSTRUCTION_RUN(XorAC);
    case INSTRUCTION_RUN(XorAD);
    case INSTRUCTION_RUN(XorAE);
    case INSTRUCTION_RUN(XorAH);
    case INSTRUCTION_RUN(XorAL);
    case INSTRUCTION_RUN(XorAIndexedHl);
    case INSTRUCTION_RUN(XorAA);

    case INSTRUCTION_RUN(OrAB);
    case INSTRUCTION_RUN(OrAC);
    case INSTRUCTION_RUN(OrAD);
    case INSTRUCTION_RUN(OrAE);
    case INSTRUCTION_RUN(OrAH);
    case INSTRUCTION_RUN(OrAL);
    case INSTRUCTION_RUN(OrAIndexedHl);
    case INSTRUCTION_RUN(OrAA);
    case InstructionTag::CompareAB:
    case InstructionTag::CompareAC:
    case InstructionTag::CompareAD:
    case InstructionTag::CompareAE:
    case InstructionTag::CompareAH:
    case InstructionTag::CompareAL:
    case InstructionTag::CompareAIndexedHl:
    case InstructionTag::CompareAA:

    case InstructionTag::RetNotZero:
    case InstructionTag::PopBC:
    case InstructionTag::JumpNotZeroImm16:
    case InstructionTag::JumpImm16:
    case InstructionTag::CallNotZeroImm16:
    case InstructionTag::PushBc:
    case InstructionTag::AddAImm8:
    case InstructionTag::Rst00H:
    case InstructionTag::RetZero:
    case InstructionTag::Ret:
    case InstructionTag::JumpZeroImm16:
    case InstructionTag::ExtendedInstruction:
    case InstructionTag::CallZeroImm16:
    case InstructionTag::CallImm16:
    case InstructionTag::AddCarryAImm8:
    case InstructionTag::Rst08H:

    case InstructionTag::RetNoCarry:
    case InstructionTag::PopDe:
    case InstructionTag::JumpNoCarryImm16:
    case InstructionTag::Invalid0:
    case InstructionTag::CallNoCarryImm16:
    case InstructionTag::PushDe:
    case InstructionTag::SubImm8:
    case InstructionTag::Rst10H:
    case InstructionTag::RetCarry:
    case InstructionTag::Reti:
    case InstructionTag::JumpCarryImm16:
    case InstructionTag::Invalid1:
    case InstructionTag::CallCarryImm16:
    case InstructionTag::Invalid2:
    case InstructionTag::SubCarryAImm8:
    case InstructionTag::Rst18H:

    case InstructionTag::LoadHighAdressIndexedImm8A:
    case InstructionTag::PopHl:
    case InstructionTag::LoadIndexedCA:
    case InstructionTag::Invalid3:
    case InstructionTag::Invalid4:
    case InstructionTag::PushHl:
    case InstructionTag::AndImm8:
    case InstructionTag::Rst20H:
    case InstructionTag::AddSpImm8:
    case InstructionTag::JumpIndexedHl:
    case InstructionTag::LoadIndexedImm16A:
    case InstructionTag::Invalid5:
    case InstructionTag::Invalid6:
    case InstructionTag::Invalid7:
    case InstructionTag::XorImm8:
    case InstructionTag::Rst28H:

    case InstructionTag::LoadHighAdressAIndexedImm8:
    case InstructionTag::PopAf:
    case InstructionTag::LoadAIndexedC:
    case InstructionTag::Di:
    case InstructionTag::Invalid8:
    case InstructionTag::PushAf:
    case InstructionTag::OrImm8:
    case InstructionTag::Rst30H:
    case InstructionTag::LoadHlSpplussignedimm8:
    case InstructionTag::LoadSpHl:
    case InstructionTag::LoadAIndexedImm16:
    case InstructionTag::Ei:
    case InstructionTag::Invalid9:
    case InstructionTag::Invalid10:
    case InstructionTag::CompareAImm8:
    case InstructionTag::Rst38H:
        break;
#undef INSTRUCTION_RUN
    }
}

}
