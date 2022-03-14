#pragma once
#include <stdint.h>

namespace GB {

inline constexpr const auto viewport_width = 160;
inline constexpr const auto viewport_height = 144;
inline constexpr const auto internal_width = 256;
inline constexpr const auto internal_height = 256;

inline constexpr const auto oam_search_cycles = 80;
inline constexpr const auto pixel_transfer_cycles = 172;
inline constexpr const auto hblank_cycles = 204;
inline constexpr const auto vblank_cycles = 4560;

inline uint8_t scrolling_graphic[] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
    0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
    0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
};

enum class CartridgeType : uint8_t {
    RomOnly                 = 0x00,

    RomMbc1                 = 0x01,
    RomMbc1Ram              = 0x02,
    RomMbc1RamBat           = 0x03,
    
    RomMbc2                 = 0x05,
    RomMbc2Bat              = 0x06,
    
    RomRam                  = 0x08,
    RomRamBat               = 0x09,
    
    RomMmm01                = 0x0B,
    RomMmm01Sram            = 0x0C,
    RomMmm01SramBat         = 0x0D,
    
    RomMbc3TimerBat         = 0x0F,
    RomMbc3TimerRamBat      = 0x10,
    RomMbc3                 = 0x11,

    RomMbc3Ram              = 0x12,
    RomMbc3RamBat           = 0x13,
    
    RomMbc5                 = 0x19,
    RomMbc5Ram              = 0x1A,
    RomMbc5RamBat           = 0x1B,
    RomMbc5Rumble           = 0x1C,
    RomMbc5RumbleSram       = 0x1D,
    RomMbc5RumbleSramBat    = 0x1E,
    
    PocketCamera            = 0x1F,
    BandaiTama5             = 0xFD,
    
    HudsonHuc3              = 0xFE,
    HudsonHuc1              = 0xFF,
};

enum class IsCGB : uint8_t {
    // No = any other,
    Yes = 0x80
};

enum class IsSGB : uint8_t {
    No = 0x00,
    Yes = 0x03
};

enum class RomSize : uint8_t {
    Banks2   = 0x00,
    Banks4   = 0x01,
    Banks8   = 0x02,
    Banks16  = 0x03,
    Banks32  = 0x04,
    Banks64  = 0x05,
    Banks128 = 0x06,
    Banks72  = 0x52,
    Banks80  = 0x53,
    Banks96  = 0x54,
};

enum class RamSize : uint8_t {
    Banks0      = 0,
    Banks1Small = 1,
    Banks1Large = 2,
    Banks4      = 3,
    Banks16     = 4,
};

enum class DestinationCode : uint8_t {
    Japanese,
    NonJapanese,
};

// Super Game Boy function won't work if 0x33
enum class LicenseeCodeOld : uint8_t {
    Check0x0144to0x0145ForLicense = 0x33,
    Accolade = 0x79,
    Konami = 0xA4,
};

// start_of_execution_end = 0x0103
// scrolling_graphic_end = 0x133
// game_title_end = 0x0142
enum class CartridgeInfoLocation : uint16_t {
    Restart0  = 0x0000,
    Restart8  = 0x0008,
    Restart10 = 0x0010,
    Restart18 = 0x0018,
    Restart20 = 0x0020,
    Restart28 = 0x0028,
    Restart30 = 0x0030,
    Restart38 = 0x0038,
    VBlankInterrupt             = 0x0040,
    LCDControlStatusInterrupt   = 0x0048,
    TimerOverflowInterrupt      = 0x0050,
    SerialTransferCompleteInterrupt = 0x0058,
    ButtonReleasedInterrupt = 0x0060,
    StartOfExecution        = 0x0100,
    ScrollingGraphicStart   = 0x0104,
    GameTitleStart  = 0x0134,
    IsColorGameBoy  = 0x0143,
    LicenseeHighNibbleNew = 0x0144,
    LicenseeLowNibbleNew  = 0x0145,
    IsSuperGameBoy  = 0x0146,
    CartridgeType   = 0x0147,
    RomSize         = 0x0148,
    RamSize         = 0x0149,
    DestinationCode = 0x014A,
    LicenseeCodeOld = 0x014B,
    MaskRomVersion  = 0x014C,
    ComplementCheck = 0x014D, // Will run on Super GB if incorrect
    ChecksumHighByte = 0x014E,
    ChecksumLowByte = 0x015F,
};

enum class MemoryMap : uint16_t {
    RomBank         = 0x0000,
    RomBankEnd      = 0x4000-1,
    BankRom         = 0x4000,
    BankRomEnd      = 0x8000-1,
    VideoRam        = 0x8000,
    VideoRamEnd     = 0xA000-1,
    BankRam         = 0xA000,
    BankRamEnd      = 0xC000-1,
    Ram0            = 0xC000,
    Ram0End         = 0xE000-1,
    EchoRam         = 0xE000,
    EchoRamEnd      = 0xFE00-1,
    OAMRam          = 0xFE00,
    OAMRamEnd       = 0xFEA0-1,
    IORam0          = 0xFEA0,   // prohibited
    IORam0End       = 0xFF00-1, // prohibited
    IOPorts         = 0xFF00,
    IOPortsEnd      = 0xFF4C-1,
    IORam1          = 0xFF4C,   // prohibited?
    IORam1End       = 0xFF80-1, // prohibited?
    Ram1            = 0xFF80,
    Ram1End         = 0xFFFE,
    InterruptEnable = 0xFFFF,
};
[[nodiscard]]
inline constexpr uint16_t operator * (MemoryMap&& map)
{
    return static_cast<uint16_t>(map);
}

enum class InterruptMask : uint8_t {
    VBlank           = 1 << 0,
    LCDControl       = 1 << 1,
    TimerOverflow    = 1 << 2,
    SerialIOComplete = 1 << 3,
    ButtonReleased   = 1 << 4,
};
[[nodiscard]]
inline constexpr uint8_t operator * (InterruptMask&& mask)
{
    return static_cast<uint8_t>(mask);
}

enum class MemoryRegister : uint16_t {
    Joypad              = 0xFF00,
    SerialTransferData  = 0xFF01,
    SIOControl          = 0xFF02,
    Divider             = 0xFF04,
    TimerCounter        = 0xFF05,
    TimerModulo         = 0xFF06,
    TimerControl        = 0xFF07,
    InterruptFlag       = 0xFF0F,
    Sound1Sweep         = 0xFF10,
    Sound1LengthAndDuty = 0xFF11,
    Sound1Envelope      = 0xFF12,
    Sound1FreqLow       = 0xFF13,
    Sound1FreqHigh      = 0xFF14,
    Sound2LengthAndDuty = 0xFF16,
    Sound2Envelope      = 0xFF17,
    Sound2FreqLow       = 0xFF18,
    Sound2FreqHigh      = 0xFF19,
    Sound3OnOff         = 0xFF1A,
    Sound3Length        = 0xFF1B,
    Sound3OutputLevel   = 0xFF1C,
    Sound3FreqLow       = 0xFF1D,
    Sound3FreqHigh      = 0xFF1E,
    Sound4Length        = 0xFF20,
    Sound4Envelope      = 0xFF21,
    Sound4PolynomialCounter = 0xFF22,
    Sound4ResetAndCounter   = 0xFF23,
    SoundChannelControl     = 0xFF24,
    SoundOutputSelection    = 0xFF25,
    SoundOnOff          = 0xFF26,
    WavePatternRam      = 0xFF30,
    WavePatternRamEnd   = 0xFF3F,
    LCDControl          = 0xFF40,
    LCDStat             = 0xFF41,
    ScrollY             = 0xFF42,
    ScrollX             = 0xFF43,
    LCDYCoordinate      = 0xFF44,
    LCDYCompare         = 0xFF45,
    DMATransfer         = 0xFF46,
    BackgroundPalette   = 0xFF47,
    ObjectPalette0Data  = 0xFF48,
    ObjectPalette1Data  = 0xFF49,
    WindowY             = 0xFF4A,
    WindowX             = 0xFF4B,
    InterruptEnable     = 0xFFFF
};
[[nodiscard]]
inline constexpr uint16_t operator * (MemoryRegister&& register_)
{
    return static_cast<uint16_t>(register_);
}

}
