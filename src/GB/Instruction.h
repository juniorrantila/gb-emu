#pragma once
#include <stdint.h>
#include <Forward.h>
#include <CString.h>

namespace GB {

using InstructionTagStorage = uint8_t;
enum class InstructionTag : InstructionTagStorage {
    Nop,
    LoadBcImm16,
    LoadIndexedBcA,
    IncBc,
    IncB,
    DecB,
    LoadBImm8,
    Rlca,
    LoadIndexedImm16Sp,
    AddHlBc,
    LoadAIndexedBc,
    DecBc,
    IncC, 
    DecC, 
    LoadCImm8, 
    Rrca,

    Stop,
    LoadDeImm16,
    LoadIndexedDeA,
    IncDe,
    IncD,
    DecD,
    LoadDImm8,
    Rla,
    JumpRelativeSignedImm8,
    AddHlDe,
    LoadAIndexedDe,
    DecDe,
    IncE,
    DecE,
    LoadEImm8,
    Rra,

    JumpRelativeNotZeroSignedImm8,
    LoadHlImm16,
    LoadIndexedHlplusA,
    IncHl,
    IncH,
    DecH,
    LoadHImm8,
    Daa,
    JumpRelativeZeroSignedImm8,
    AddHlHl,
    LoadAIndexedHlplus,
    DecHl,
    IncL,
    DecL,
    LoadLImm8,
    Cpl,

    JumpRelativeNoCarrySignedImm8,
    LoadSpImm16,
    LoadIndexedHlminusA,
    IncSp,
    IncIndexedHl,
    DecIndexedHl,
    LoadIndexedHlImm8,
    Scf,
    JumpRelativeCarrySignedImm8,
    AddHlSp,
    LoadAIndexedHlminus,
    DecSp,
    IncA,
    DecA,
    LoadAImm8,
    Ccf,

    LoadBB,
    LoadBC,
    LoadBD,
    LoadBE,
    LoadBH,
    LoadBL,
    LoadBIndexedHl,
    LoadBA,
    LoadCB,
    LoadCC,
    LoadCD,
    LoadCE,
    LoadCH,
    LoadCL,
    LoadCIndexedHl,
    LoadCA,

    LoadDB,
    LoadDC,
    LoadDD,
    LoadDE,
    LoadDH,
    LoadDL,
    LoadDIndexedHl,
    LoadDA,
    LoadEB,
    LoadEC,
    LoadED,
    LoadEE,
    LoadEH,
    LoadEL,
    LoadEIndexedHl,
    LoadEA,

    LoadHB,
    LoadHC,
    LoadHD,
    LoadHE,
    LoadHH,
    LoadHL,
    LoadHIndexedHl,
    LoadHA,
    LoadLB,
    LoadLC,
    LoadLD,
    LoadLE,
    LoadLH,
    LoadLL,
    LoadLIndexedHl,
    LoadLA,

    LoadIndexedHlB,
    LoadIndexedHlC,
    LoadIndexedHlD,
    LoadIndexedHlE,
    LoadIndexedHlH,
    LoadIndexedHlL,
    Halt,
    LoadIndexedHlA,
    LoadAB,
    LoadAC,
    LoadAD,
    LoadAE,
    LoadAH,
    LoadAL,
    LoadAIndexedHl,
    LoadAA,

    AddAB,
    AddAC,
    AddAD,
    AddAE,
    AddAH,
    AddAL,
    AddAIndexedHl,
    AddAA,
    AddCarryAB,
    AddCarryAC,
    AddCarryAD,
    AddCarryAE,
    AddCarryAH,
    AddCarryAL,
    AddCarryAIndexedHl,
    AddCarryAA,

    SubAB,
    SubAC,
    SubAD,
    SubAE,
    SubAH,
    SubAL,
    SubAIndexedHl,
    SubAA,
    SubCarryAB,
    SubCarryAC,
    SubCarryAD ,
    SubCarryAE,
    SubCarryAH,
    SubCarryAL,
    SubCarryAIndexedHl,
    SubCarryAA,

    AndAB,
    AndAC,
    AndAD,
    AndAE,
    AndAH,
    AndAL,
    AndAIndexedHl,
    AndAA,
    XorAB,
    XorAC,
    XorAD,
    XorAE,
    XorAH,
    XorAL,
    XorAIndexedHl,
    XorAA,

    OrAB,
    OrAC,
    OrAD,
    OrAE,
    OrAH,
    OrAL,
    OrAIndexedHl,
    OrAA,
    CompareAB,
    CompareAC,
    CompareAD,
    CompareAE,
    CompareAH,
    CompareAL,
    CompareAIndexedHl,
    CompareAA,

    RetNotZero,
    PopBC,
    JumpNotZeroImm16,
    JumpImm16,
    CallNotZeroImm16,
    PushBc,
    AddAImm8,
    Rst00H,
    RetZero,
    Ret,
    JumpZeroImm16,
    ExtendedInstruction,
    CallZeroImm16,
    CallImm16,
    AddCarryAImm8,
    Rst08H,

    RetNoCarry,
    PopDe,
    JumpNoCarryImm16,
    Invalid0,
    CallNoCarryImm16,
    PushDe,
    SubImm8,
    Rst10H,
    RetCarry,
    Reti,
    JumpCarryImm16,
    Invalid1,
    CallCarryImm16,
    Invalid2,
    SubCarryAImm8,
    Rst18H,

    LoadHighAdressIndexedImm8A,
    PopHl,
    LoadIndexedCA,
    Invalid3,
    Invalid4,
    PushHl,
    AndImm8,
    Rst20H,
    AddSpImm8,
    JumpIndexedHl,
    LoadIndexedImm16A,
    Invalid5,
    Invalid6,
    Invalid7,
    XorImm8,
    Rst28H,

    LoadHighAdressAIndexedImm8,
    PopAf,
    LoadAIndexedC,
    Di,
    Invalid8,
    PushAf,
    OrImm8,
    Rst30H,
    LoadHlSpplussignedimm8,
    LoadSpHl,
    LoadAIndexedImm16,
    Ei,
    Invalid9,
    Invalid10,
    CompareAImm8,
    Rst38H,
};
inline constexpr
InstructionTagStorage operator * (InstructionTag tag)
{
    return static_cast<InstructionTagStorage>(tag);
}

using ExtendedInstructionTagStorage = uint8_t;
enum class ExtendedInstructionTag
    : ExtendedInstructionTagStorage
{
    RlcB,  LcC,   RlcD,  RlcE,  RlcH,  RlcL,  RlcIndexedHL,  RlcA,  RrcB,  RrcC,  RrcD,  RrcE,  RrcH,  RrcL,  RrcIndexedHL,  RrcA,
    RlB,   RlC,   RlD,   RlE,   RlH,   RlL,   RlIndexedHL,   RlA,   RrB,   RrC,   RrD,   RrE,   RrH,   RrL,   RrIndexedHL,   RrA,
    SlaB,  SlaC,  SlaD,  SlaE,  SlaH,  SlaL,  SlaIndexedHL,  SlaA,  SraB,  SraC,  SraD,  SraE,  SraH,  SraL,  SraIndexedHL,  SraA,
    SwapB, SwapC, SwapD, SwapE, SwapH, SwapL, SwapIndexedHL, SwapA, SrlB,  SrlC,  SrlD,  SrlE,  SrlH,  SrlL,  SrlIndexedHL,  SrlA,
    Bit0B, Bit0C, Bit0D, Bit0E, Bit0H, Bit0L, Bit0IndexedHL, Bit0A, Bit1B, Bit1C, Bit1D, Bit1E, Bit1H, Bit1L, Bit1IndexedHL, Bit1A,
    Bit2B, Bit2C, Bit2D, Bit2E, Bit2H, Bit2L, Bit2IndexedHL, Bit2A, Bit3B, Bit3C, Bit3D, Bit3E, Bit3H, Bit3L, Bit3IndexedHL, Bit3A,
    Bit4B, Bit4C, Bit4D, Bit4E, Bit4H, Bit4L, Bit4IndexedHL, Bit4A, Bit5B, Bit5C, Bit5D, Bit5E, Bit5H, Bit5L, Bit5IndexedHL, Bit5A,
    Bit6B, Bit6C, Bit6D, Bit6E, Bit6H, Bit6L, Bit6IndexedHL, Bit6A, Bit7B, Bit7C, Bit7D, Bit7E, Bit7H, Bit7L, Bit7IndexedHL, Bit7A,
    Res0B, Res0C, Res0D, Res0E, Res0H, Res0L, Res0IndexedHL, Res0A, Res1B, Res1C, Res1D, Res1E, Res1H, Res1L, Res1IndexedHL, Res1A,
    Res2B, Res2C, Res2D, Res2E, Res2H, Res2L, Res2IndexedHL, Res2A, Res3B, Res3C, Res3D, Res3E, Res3H, Res3L, Res3IndexedHL, Res3A,
    Res4B, Res4C, Res4D, Res4E, Res4H, Res4L, Res4IndexedHL, Res4A, Res5B, Res5C, Res5D, Res5E, Res5H, Res5L, Res5IndexedHL, Res5A,
    Res6B, Res6C, Res6D, Res6E, Res6H, Res6L, Res6IndexedHL, Res6A, Res7B, Res7C, Res7D, Res7E, Res7H, Res7L, Res7IndexedHL, Res7A,
    Set0B, Set0C, Set0D, Set0E, Set0H, Set0L, Set0IndexedHL, Set0A, Set1B, Set1C, Set1D, Set1E, Set1H, Set1L, Set1IndexedHL, Set1A,
    Set2B, Set2C, Set2D, Set2E, Set2H, Set2L, Set2IndexedHL, Set2A, Set3B, Set3C, Set3D, Set3E, Set3H, Set3L, Set3IndexedHL, Set3A,
    Set4B, Set4C, Set4D, Set4E, Set4H, Set4L, Set4IndexedHL, Set4A, Set5B, Set5C, Set5D, Set5E, Set5H, Set5L, Set5IndexedHL, Set5A,
    Set6B, Set6C, Set6D, Set6E, Set6H, Set6L, Set6IndexedHL, Set6A, Set7B, Set7C, Set7D, Set7E, Set7H, Set7L, Set7IndexedHL, Set7A,
};

template <typename T, InstructionTag Tag, char Size,
          char Cycles, char LongCycles = Cycles,
          bool SetsFlags = false, bool ReadsFlags = false>
struct [[gnu::packed]] InstructionBase {
public:
    static constexpr const auto size        = Size;
    static constexpr const auto cycles      = Cycles;
    static constexpr const auto long_cycles = LongCycles;
    static constexpr const auto sets_flags  = SetsFlags;
    static constexpr const auto reads_flags = ReadsFlags;

    // InstructionTag tag() const { return m_tag; }

    void eval(CPU& cpu) const
    {
        self().eval(cpu);
    };
    c_string disassemble(CPU const& cpu) const
    {
        return self().disassemble(cpu);
    };
    c_string changes(CPU const& cpu) const
    { 
        return self().changes(cpu);
    };

private:
    T const& self() const
    {
        return static_cast<T const&>(*this);
    }
    // const InstructionTag m_tag { Tag };
};

template <typename T,
          ExtendedInstructionTag Tag,
          char Size, char Cycles,
          bool SetsFlags = false, bool ReadsFlags = false>
struct [[gnu::packed]] ExtendedInstructionBase
    : public InstructionBase<
                ExtendedInstructionBase<
                    T, Tag, Size, Cycles,
                    SetsFlags, ReadsFlags>,
                InstructionTag::ExtendedInstruction,
                Size, Cycles, SetsFlags, ReadsFlags>
{
public:
    ExtendedInstructionTag extended_tag() const
    {
        return m_tag;
    }
private:
    const ExtendedInstructionTag m_tag { Tag };
};

namespace Instruction {

#define INSTRUCTION(name, size, cycles)                 \
    struct [[gnu::packed]] name                         \
        : public InstructionBase<name,                  \
                    InstructionTag::name, size, cycles>

#define BRANCH(name, size, cycles, long_cycles)         \
    struct [[gnu::packed]] name                         \
        : public InstructionBase<name,                  \
                                 InstructionTag::name,  \
                                 size, cycles, long_cycles>

#define PRELUDE                             \
    public:                                             \
    void eval(CPU&) const;                              \
    c_string disassemble(CPU const& cpu) const;         \
    c_string changes(CPU const& cpu) const              \

INSTRUCTION(Nop, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBcImm16, 3, 12)
{
    PRELUDE;
    uint16_t m_imm16;
};
INSTRUCTION(LoadIndexedBcA, 1, 8) { PRELUDE; };
INSTRUCTION(IncBc, 1, 8) { PRELUDE; };
INSTRUCTION(IncB, 1, 4) { PRELUDE; };
INSTRUCTION(DecB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBImm8, 2, 8)
{
    PRELUDE;
    uint8_t m_imm8;
};

INSTRUCTION(Rlca, 1, 4) { PRELUDE; };
INSTRUCTION(LoadIndexedImm16Sp, 3, 20)
{
    PRELUDE;
    uint16_t m_imm16;
};
INSTRUCTION(AddHlBc, 1, 8) { PRELUDE; };
INSTRUCTION(LoadAIndexedBc, 1, 8) { PRELUDE; };
INSTRUCTION(DecBc, 1, 8) { PRELUDE; };
INSTRUCTION(IncC, 1, 4) { PRELUDE; };
INSTRUCTION(DecC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCImm8, 2, 8)
{
    PRELUDE;
    uint8_t m_imm8;
};
INSTRUCTION(Rrca, 1, 4) { PRELUDE; };

INSTRUCTION(Stop, 1, 0) { PRELUDE; };
INSTRUCTION(LoadDeImm16, 3, 12)
{
    PRELUDE;
    uint16_t m_imm16;
};
INSTRUCTION(LoadIndexedDeA, 1, 8) { PRELUDE; };
INSTRUCTION(IncDe, 1, 8) { PRELUDE; };
INSTRUCTION(IncD, 1, 4) { PRELUDE; };
INSTRUCTION(DecD, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDImm8, 2, 8)
{
    PRELUDE;
    uint8_t m_imm8;
};
INSTRUCTION(Rla, 1, 4) { PRELUDE; };
INSTRUCTION(JumpRelativeSignedImm8, 2, 12)
{
    PRELUDE;
    int8_t m_imm8;
};
INSTRUCTION(AddHlDe, 1, 8) { PRELUDE; };
INSTRUCTION(LoadAIndexedDe, 1, 8) { PRELUDE; };
INSTRUCTION(DecDe, 1, 8) { PRELUDE; };
INSTRUCTION(IncE, 1, 4) { PRELUDE; };
INSTRUCTION(DecE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadEImm8, 2, 8)
{
    PRELUDE;
    uint8_t m_imm8;
};
INSTRUCTION(Rra, 1, 4) { PRELUDE; };
BRANCH(JumpRelativeNotZeroSignedImm8, 2, 8, 12)
{
    PRELUDE;
    int8_t m_imm8;
};

INSTRUCTION(LoadHlImm16, 3, 12)
{
    PRELUDE;
    uint16_t m_imm16;
};
INSTRUCTION(LoadIndexedHlplusA, 1, 8) { PRELUDE; };
INSTRUCTION(IncHl, 1, 8) { PRELUDE; };
INSTRUCTION(IncH, 1, 4) { PRELUDE; };
INSTRUCTION(DecH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHImm8, 2, 8)
{
    PRELUDE;
    uint8_t m_imm8;
};
INSTRUCTION(Daa, 1, 1) { PRELUDE; };
BRANCH(JumpRelativeZeroSignedImm8, 2, 8, 12)
{
    PRELUDE;
    int8_t m_imm8;
};
INSTRUCTION(AddHlHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadAIndexedHlplus, 1, 8) { PRELUDE; };
INSTRUCTION(DecHl, 1, 8) { PRELUDE; };
INSTRUCTION(IncL, 1, 4) { PRELUDE; };
INSTRUCTION(DecL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLImm8, 2, 8)
{
    PRELUDE;
    uint8_t m_imm8;
};
INSTRUCTION(Cpl, 1, 4) { PRELUDE; };
BRANCH(JumpRelativeNoCarrySignedImm8, 2, 8, 12)
{
    PRELUDE;
    int8_t m_imm8;
};

INSTRUCTION(LoadSpImm16, 3, 12) 
{
    PRELUDE;
    uint16_t m_imm16;
};
INSTRUCTION(LoadIndexedHlminusA, 1, 8) { PRELUDE; };
INSTRUCTION(IncSp, 1, 8) { PRELUDE; };
INSTRUCTION(IncIndexedHl, 1, 12) { PRELUDE; };
INSTRUCTION(DecIndexedHl, 1, 12) { PRELUDE; };
INSTRUCTION(LoadIndexedHlImm8, 2, 12)
{
    PRELUDE;
    uint8_t m_imm8;
};
INSTRUCTION(Scf, 1, 4) { PRELUDE; };
BRANCH(JumpRelativeCarrySignedImm8, 2, 2, 3)
{ 
    PRELUDE;
    int8_t m_imm8;
};
INSTRUCTION(AddHlSp, 1, 8) { PRELUDE; };
INSTRUCTION(LoadAIndexedHlminus, 1, 8) { PRELUDE; };
INSTRUCTION(DecSp, 1, 8) { PRELUDE; };
INSTRUCTION(IncA, 1, 4) { PRELUDE; };
INSTRUCTION(DecA, 1, 4) { PRELUDE; };
INSTRUCTION(LoadAImm8, 2, 8)
{
    PRELUDE;
    uint8_t m_imm8;
};
INSTRUCTION(Ccf, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBD, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadBIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadBA, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCD, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadCIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadCA, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDD, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadDIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadDA, 1, 4) { PRELUDE; };
INSTRUCTION(LoadEB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadEC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadED, 1, 4) { PRELUDE; };
INSTRUCTION(LoadEE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadEH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadEL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadEIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadEA, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHD, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadHIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadHA, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLD, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadLIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadLA, 1, 4) { PRELUDE; };
INSTRUCTION(LoadIndexedHlB, 1, 8) { PRELUDE; };
INSTRUCTION(LoadIndexedHlC, 1, 8) { PRELUDE; };
INSTRUCTION(LoadIndexedHlD, 1, 8) { PRELUDE; };
INSTRUCTION(LoadIndexedHlE, 1, 8) { PRELUDE; };
INSTRUCTION(LoadIndexedHlH, 1, 8) { PRELUDE; };
INSTRUCTION(LoadIndexedHlL, 1, 8) { PRELUDE; };
INSTRUCTION(Halt, 1, 4) { PRELUDE; };
INSTRUCTION(LoadIndexedHlA, 1, 8) { PRELUDE; };
INSTRUCTION(LoadAB, 1, 4) { PRELUDE; };
INSTRUCTION(LoadAC, 1, 4) { PRELUDE; };
INSTRUCTION(LoadAD, 1, 4) { PRELUDE; };
INSTRUCTION(LoadAE, 1, 4) { PRELUDE; };
INSTRUCTION(LoadAH, 1, 4) { PRELUDE; };
INSTRUCTION(LoadAL, 1, 4) { PRELUDE; };
INSTRUCTION(LoadAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(LoadAA, 1, 4) { PRELUDE; };

INSTRUCTION(AddAB, 1, 4) { PRELUDE; };
INSTRUCTION(AddAC, 1, 4) { PRELUDE; };
INSTRUCTION(AddAD, 1, 4) { PRELUDE; };
INSTRUCTION(AddAE, 1, 4) { PRELUDE; };
INSTRUCTION(AddAH, 1, 4) { PRELUDE; };
INSTRUCTION(AddAL, 1, 4) { PRELUDE; };
INSTRUCTION(AddAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(AddAA, 1, 4) { PRELUDE; };
INSTRUCTION(AddCarryAB, 1, 4) { PRELUDE; };
INSTRUCTION(AddCarryAC, 1, 4) { PRELUDE; };
INSTRUCTION(AddCarryAD, 1, 4) { PRELUDE; };
INSTRUCTION(AddCarryAE, 1, 4) { PRELUDE; };
INSTRUCTION(AddCarryAH, 1, 4) { PRELUDE; };
INSTRUCTION(AddCarryAL, 1, 4) { PRELUDE; };
INSTRUCTION(AddCarryAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(AddCarryAA, 1, 4) { PRELUDE; };

INSTRUCTION(SubAB, 1, 4) { PRELUDE; };
INSTRUCTION(SubAC, 1, 4) { PRELUDE; };
INSTRUCTION(SubAD, 1, 4) { PRELUDE; };
INSTRUCTION(SubAE, 1, 4) { PRELUDE; };
INSTRUCTION(SubAH, 1, 4) { PRELUDE; };
INSTRUCTION(SubAL, 1, 4) { PRELUDE; };
INSTRUCTION(SubAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(SubAA, 1, 4) { PRELUDE; };
INSTRUCTION(SubCarryAB, 1, 4) { PRELUDE; };
INSTRUCTION(SubCarryAC, 1, 4) { PRELUDE; };
INSTRUCTION(SubCarryAD, 1, 4) { PRELUDE; };
INSTRUCTION(SubCarryAE, 1, 4) { PRELUDE; };
INSTRUCTION(SubCarryAH, 1, 4) { PRELUDE; };
INSTRUCTION(SubCarryAL, 1, 4) { PRELUDE; };
INSTRUCTION(SubCarryAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(SubCarryAA, 1, 4) { PRELUDE; };

INSTRUCTION(AndAB, 1, 4) { PRELUDE; };
INSTRUCTION(AndAC, 1, 4) { PRELUDE; };
INSTRUCTION(AndAD, 1, 4) { PRELUDE; };
INSTRUCTION(AndAE, 1, 4) { PRELUDE; };
INSTRUCTION(AndAH, 1, 4) { PRELUDE; };
INSTRUCTION(AndAL, 1, 4) { PRELUDE; };
INSTRUCTION(AndAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(AndAA, 1, 4) { PRELUDE; };
INSTRUCTION(XorAB, 1, 4) { PRELUDE; };
INSTRUCTION(XorAC, 1, 4) { PRELUDE; };
INSTRUCTION(XorAD, 1, 4) { PRELUDE; };
INSTRUCTION(XorAE, 1, 4) { PRELUDE; };
INSTRUCTION(XorAH, 1, 4) { PRELUDE; };
INSTRUCTION(XorAL, 1, 4) { PRELUDE; };
INSTRUCTION(XorAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(XorAA, 1, 4) { PRELUDE; };

INSTRUCTION(OrAB, 1, 4) { PRELUDE; };
INSTRUCTION(OrAC, 1, 4) { PRELUDE; };
INSTRUCTION(OrAD, 1, 4) { PRELUDE; };
INSTRUCTION(OrAE, 1, 4) { PRELUDE; };
INSTRUCTION(OrAH, 1, 4) { PRELUDE; };
INSTRUCTION(OrAL, 1, 4) { PRELUDE; };
INSTRUCTION(OrAIndexedHl, 1, 8) { PRELUDE; };
INSTRUCTION(OrAA, 1, 4) { PRELUDE; };

}

#undef PRELUDE
#undef BRANCH
#undef INSTRUCTION

namespace ExtendedInstruction {

}

}
