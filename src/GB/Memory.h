#pragma once
#include <GB/Hardware.h>
#include <GB/MemoryLocation.h>
#include <Nullability.h>
#include <stdio.h>

namespace GB {

enum class LogInvalidAccess : bool {
    No = false,
    Yes = true,
};
constexpr bool operator * (LogInvalidAccess a)
{
    return static_cast<bool>(a);
}

class Memory {
public:    
    constexpr Memory(uint8_t const* nonnull code,
                     uint16_t size,
                     LogInvalidAccess access = LogInvalidAccess::No)
        : m_rom_bank(code)
        , m_rom_bank_size(size)
    {
        s_log_invalid_access = *access;
    }

    void log_invalid_access(bool yes_no)
    {
        s_log_invalid_access = yes_no;
    }

    MemoryLocation operator [](uint16_t index)
    {
        switch(index) {
            using enum MemoryMap;

            case *RomBank ... *RomBankEnd:
                if (index - *RomBank < m_rom_bank_size)
                    return MemoryLocation::read_only(index - *RomBank, wrote_anyway); // FIXME: Add support for MBC
                else return {};

            case *BankRom ... *BankRomEnd:
                // FIXME: Validate this is right
                if (index < m_switchable_rom_bank_size)
                    return MemoryLocation::read_only(index - *BankRom, wrote_anyway);
                else return {};

            case *VideoRam ... *VideoRamEnd:
                return MemoryLocation::read_write(m_video_ram[index - *VideoRam]);

            case *BankRam ... *BankRamEnd:
                // FIXME: Validate this is right
                if (m_switchable_ram_bank_size)
                    return MemoryLocation::read_write(m_switchable_ram_bank[m_current_ram_bank][index - *BankRam]);
                else
                    return {};

            case *Ram0 ... *Ram0End:
                return MemoryLocation::read_write(m_ram[index - *Ram0]);

            case *EchoRam ... *EchoRamEnd:
                return MemoryLocation::read_write(m_ram[index - *EchoRam]);

            case *OAMRam ... *OAMRamEnd:
                return MemoryLocation::read_write(m_oam_ram[index - *OAMRam]);

            case *IORam0 ... *IORam0End:
                return MemoryLocation::read_write(m_io_ram[index - *IORam0]);

            case *IOPorts ... *IOPortsEnd:
            {
                using Reg = MemoryRegister;
                switch(index) {
                case *Reg::Joypad:
                    return MemoryLocation::special(
                            [&]{ return m_gb_joypad.read(); },
                            [&](auto value) { return m_gb_joypad.write(value); });
                case *Reg::SerialTransferData:
                    return {}; // FIXME
                case *Reg::SIOControl:
                    return {}; // FIXME
                case *Reg::Divider:
                    return {}; // FIXME
                case *Reg::TimerCounter:
                    return {}; // FIXME
                case *Reg::TimerModulo:
                    return {}; // FIXME
                case *Reg::TimerControl:
                    return {}; // FIXME
                case *Reg::InterruptFlag:
                    return MemoryLocation::read_write(m_interrupt_flag.full);
                case *Reg::Sound1Sweep:
                    return MemoryLocation::read_write(m_sound1.sweep);
                case *Reg::Sound1LengthAndDuty:
                    return MemoryLocation::read_write(m_sound1.length_and_duty);
                case *Reg::Sound1Envelope:
                    return MemoryLocation::read_write(m_sound1.envelope);
                case *Reg::Sound1FreqLow:
                    return MemoryLocation::read_write(m_sound1.freq_low);
                case *Reg::Sound1FreqHigh:
                    return MemoryLocation::read_write(m_sound1.freq_high);
                case *Reg::Sound2LengthAndDuty:
                    return MemoryLocation::read_write(m_sound2.length_and_duty);
                case *Reg::Sound2Envelope:
                    return MemoryLocation::read_write(m_sound2.envelope);
                case *Reg::Sound2FreqLow:
                    return MemoryLocation::read_write(m_sound2.freq_low);
                case *Reg::Sound2FreqHigh:
                    return MemoryLocation::read_write(m_sound2.freq_high);
                case *Reg::Sound3OnOff:
                    return MemoryLocation::read_write(m_sound3.on_off);
                case *Reg::Sound3Length:
                    return MemoryLocation::read_write(m_sound3.length);
                case *Reg::Sound3OutputLevel:
                    return MemoryLocation::read_write(m_sound3.output_level);
                case *Reg::Sound3FreqLow:
                    return MemoryLocation::read_write(m_sound3.freq_low);
                case *Reg::Sound3FreqHigh:
                    return MemoryLocation::read_write(m_sound3.freq_high);
                case *Reg::Sound4Length:
                    return MemoryLocation::read_write(m_sound4.length);
                case *Reg::Sound4Envelope:
                    return MemoryLocation::read_write(m_sound4.envelope);
                case *Reg::Sound4PolynomialCounter:
                    return MemoryLocation::read_write(m_sound4.polynomial_counter);
                case *Reg::Sound4ResetAndCounter:
                    return MemoryLocation::read_write(m_sound4.reset_and_counter);
                case *Reg::SoundChannelControl:
                    return MemoryLocation::read_write(m_sound_info.channel_control);
                case *Reg::SoundOutputSelection:
                    return MemoryLocation::read_write(m_sound_info.output_selection);
                case *Reg::SoundOnOff:
                    return MemoryLocation::read_write(m_sound_info.on_off);
                case *Reg::WavePatternRam ... *Reg::WavePatternRamEnd:
                    return MemoryLocation::read_write(m_wave_pattern_ram[index - *Reg::WavePatternRam]);
                case *Reg::LCDControl:
                    return MemoryLocation::read_write(m_lcd_control.full);
                case *Reg::LCDStat:
                    return MemoryLocation::special(
                            [&]{ return m_lcd_stat.read(); },
                            [&](auto value) { m_lcd_stat.write(value); }); 
                case *Reg::ScrollY:
                    return MemoryLocation::read_write(m_scroll.y);
                case *Reg::ScrollX:
                    return MemoryLocation::read_write(m_scroll.x);
                case *Reg::LCDYCoordinate:
                    return MemoryLocation::read_write(m_lcd_y_coordinate);
                case *Reg::LCDYCompare:
                    return {}; // FIXME
                case *Reg::DMATransfer:
                    return {}; // FIXME
                case *Reg::BackgroundPalette:
                    return MemoryLocation::read_write(m_background_palette.full);
                case *Reg::ObjectPalette0Data:
                    return MemoryLocation::read_write(m_object_palette0.full);
                case *Reg::ObjectPalette1Data:
                    return MemoryLocation::read_write(m_object_palette1.full);
                case *Reg::WindowY:
                    return MemoryLocation::read_write(m_window_start.y);
                case *Reg::WindowX:
                    return MemoryLocation::read_write(m_window_start.x);
                default:
                    return {};
                }
            }
            
            // FIXME: Is this right?
            case *IORam1 ... *IORam1End:
                return MemoryLocation::read_write(m_io_ram[index - *IORam1 + *IORam0End + 1]);

            case *Ram1 ... *Ram1End:
                return MemoryLocation::read_write(m_ram[index - *Ram1 + *Ram0End + 1]);

            case *InterruptEnable:
                return MemoryLocation::read_write(m_interrupt_enable.full);
        }
        __builtin_unreachable();
    }

    MemoryLocation operator [] (WideRegister r)
    {
        return this->operator[](r.value);
    }

    constexpr uint8_t operator [] (uint16_t index) const
    {
        return at(index);
    }

    constexpr uint8_t at(WideRegister r) const
    {
        return at(r.value);
    }

    constexpr uint8_t at(uint16_t index) const
    {
        switch(index) {
            using enum MemoryMap;

            case *RomBank ... *RomBankEnd:
                if (m_rom_bank_size)
                    return m_rom_bank[index - *RomBank];
                else return {};

            case *BankRom ... *BankRomEnd:
                // FIXME: Validate this is right
                if (index < m_switchable_rom_bank_size)
                    return m_switchable_rom_bank[m_current_rom_bank][index - *BankRom];
                else return {};

            case *VideoRam ... *VideoRamEnd:
                return m_video_ram[index - *VideoRam];

            case *BankRam ... *BankRamEnd:
                // FIXME: Validate this is right
                if (m_switchable_ram_bank_size)
                    return m_switchable_ram_bank[m_current_ram_bank][index - *BankRam];
                else
                    return {};

            case *Ram0 ... *Ram0End:
                return m_ram[index - *Ram0];

            case *EchoRam ... *EchoRamEnd:
                return m_ram[index - *EchoRam];

            case *OAMRam ... *OAMRamEnd:
                return m_oam_ram[index - *OAMRam];

            case *IORam0 ... *IORam0End:
                return m_io_ram[index - *IORam0];

            case *IOPorts ... *IOPortsEnd:
            {
                using Reg = MemoryRegister;
                switch(index) {
                case *Reg::Joypad:
                    return m_gb_joypad.full;
                case *Reg::SerialTransferData:
                    return {}; // FIXME
                case *Reg::SIOControl:
                    return {}; // FIXME
                case *Reg::Divider:
                    return {}; // FIXME
                case *Reg::TimerCounter:
                    return {}; // FIXME
                case *Reg::TimerModulo:
                    return {}; // FIXME
                case *Reg::TimerControl:
                    return {}; // FIXME
                case *Reg::InterruptFlag:
                    // FIXME: Check if this needs to mask unused bits
                    return m_interrupt_flag.full;
                case *Reg::Sound1Sweep:
                    return m_sound1.sweep;
                case *Reg::Sound1LengthAndDuty:
                    return m_sound1.length_and_duty;
                case *Reg::Sound1Envelope:
                    return m_sound1.envelope;
                case *Reg::Sound1FreqLow:
                    return m_sound1.freq_low;
                case *Reg::Sound1FreqHigh:
                    return m_sound1.freq_high;
                case *Reg::Sound2LengthAndDuty:
                    return m_sound2.length_and_duty;
                case *Reg::Sound2Envelope:
                    return m_sound2.envelope;
                case *Reg::Sound2FreqLow:
                    return m_sound2.freq_low;
                case *Reg::Sound2FreqHigh:
                    return m_sound2.freq_high;
                case *Reg::Sound3OnOff:
                    return m_sound3.on_off;
                case *Reg::Sound3Length:
                    return m_sound3.length;
                case *Reg::Sound3OutputLevel:
                    return m_sound3.output_level;
                case *Reg::Sound3FreqLow:
                    return m_sound3.freq_low;
                case *Reg::Sound3FreqHigh:
                    return m_sound3.freq_high;
                case *Reg::Sound4Length:
                    return m_sound4.length;
                case *Reg::Sound4Envelope:
                    return m_sound4.envelope;
                case *Reg::Sound4PolynomialCounter:
                    return m_sound4.polynomial_counter;
                case *Reg::Sound4ResetAndCounter:
                    return m_sound4.reset_and_counter;
                case *Reg::SoundChannelControl:
                    return m_sound_info.channel_control;
                case *Reg::SoundOutputSelection:
                    return m_sound_info.output_selection;
                case *Reg::SoundOnOff:
                    return m_sound_info.on_off;
                case *Reg::WavePatternRam ... *Reg::WavePatternRamEnd:
                    return m_wave_pattern_ram[index - *Reg::WavePatternRam];
                case *Reg::LCDControl:
                    return m_lcd_control.full;
                case *Reg::LCDStat:
                    return m_lcd_stat.full;
                case *Reg::ScrollY:
                    return m_scroll.y;
                case *Reg::ScrollX:
                    return m_scroll.x;
                case *Reg::LCDYCoordinate:
                    return m_lcd_y_coordinate;
                case *Reg::LCDYCompare:
                    return {}; // FIXME
                case *Reg::DMATransfer:
                    return {}; // FIXME
                case *Reg::BackgroundPalette:
                    return m_background_palette.full;
                case *Reg::ObjectPalette0Data:
                    return m_object_palette0.full;
                case *Reg::ObjectPalette1Data:
                    return m_object_palette1.full;
                case *Reg::WindowY:
                    return m_window_start.y;
                case *Reg::WindowX:
                    return m_window_start.x;
                default:
                    return {};
                }
            }
            
            // FIXME: Is this right?
            case *IORam1 ... *IORam1End:
                return m_io_ram[index - *IORam1 + *IORam0End + 1];

            case *Ram1 ... *Ram1End:
                return m_ram[index - *Ram1 + *Ram0End + 1];

            case *InterruptEnable:
                return m_interrupt_enable.full;
        }
        __builtin_unreachable();
    }

    // FIXME: Remove after instructions are done
    constexpr uint16_t rom_size() const
    {
        return m_rom_bank_size;
    }

    [[nodiscard]] auto& joypad() { return s_joypad; }
    [[nodiscard]] auto interrupt_flag() const
    {
        return m_interrupt_flag;
    }
    [[nodiscard]] auto interrupt_enable() const
    {
        return m_interrupt_enable;
    }

    [[nodiscard]] auto sound1() const { return m_sound1; }
    [[nodiscard]] auto sound2() const { return m_sound2; }
    [[nodiscard]] auto sound3() const { return m_sound3; }
    [[nodiscard]] auto sound4() const { return m_sound4; }
    [[nodiscard]] auto sound_info() const
    {
        return m_sound_info;
    }

    [[nodiscard]] auto lcd_control() const 
    {
        return m_lcd_control;
    }
    // wave_pattern_ram
    [[nodiscard]] auto& lcd_stat()
    {
        return m_lcd_stat;
    };
    [[nodiscard]] auto scroll() { return m_scroll; }

    [[nodiscard]] auto background_palette() const
    {
        return m_background_palette;
    };

    [[nodiscard]] auto object_palette0() const
    {
        return m_object_palette0;
    }; 

    [[nodiscard]] auto object_palette1() const
    {
        return m_object_palette1;
    }; 

    [[nodiscard]] auto window_start() const
    {
        return m_window_start;
    }

private:
    static void wrote_anyway(uint8_t value)
    {
        if (s_log_invalid_access)
            printf("did invalid write (value: %d)\n", value);
    }

    static uint8_t read_anyway()
    {
        if (s_log_invalid_access)
            printf("did invalid read\n");
        return 0xFF;
    }

    using multi_rom_t = uint8_t const* nonnull 
                                const* nullable;
    using multi_ram_t = uint8_t * nonnull 
                          const * nullable;

    uint8_t const* nonnull m_rom_bank;
    uint16_t m_rom_bank_size { 0 };

    multi_rom_t m_switchable_rom_bank { nullptr };
    uint16_t m_switchable_rom_bank_size { 0 };
    uint16_t m_current_rom_bank { 0 };

    static constexpr const auto video_ram_size =
                                  *MemoryMap::VideoRamEnd
                                - *MemoryMap::VideoRam + 1;
    uint8_t m_video_ram[video_ram_size] {};
    multi_ram_t m_switchable_ram_bank { nullptr };
    uint16_t m_switchable_ram_bank_size { 0 };
    uint16_t m_current_ram_bank { 0 };

    static constexpr const auto ram_size =
                                  *MemoryMap::Ram0End
                                - *MemoryMap::Ram0 + 1
                                + *MemoryMap::Ram1End
                                - *MemoryMap::Ram1 + 1;
    uint8_t m_ram[ram_size] {};


    static constexpr const auto oam_ram_size =
                                  *MemoryMap::OAMRamEnd
                                - *MemoryMap::OAMRam + 1;
    uint8_t m_oam_ram[oam_ram_size] {};


    static constexpr const auto io_ram_size =
                                  *MemoryMap::IORam0End
                                - *MemoryMap::IORam0 + 1
                                + *MemoryMap::IORam1End
                                - *MemoryMap::IORam1 + 1;
    uint8_t m_io_ram[io_ram_size] {};


    struct Joypad {
        bool up     : 1;
        bool down   : 1;
        bool left   : 1;
        bool right  : 1;
        bool start  : 1;
        bool select : 1;
        bool b      : 1;
        bool a      : 1;
    } static s_joypad;

    union {
        uint8_t read() const
        {
            return full;
        }
        void write(uint8_t value)
        {
            if (value & 0b00100000) {
                down_or_start_not_pressed = !s_joypad.down;
                up_or_select_not_pressed = !s_joypad.up;
                left_or_b_not_pressed = !s_joypad.left;
                right_or_a_not_pressed = !s_joypad.right;
            } else if (value & 0b00010000) {
                down_or_start_not_pressed =!s_joypad.start;
                up_or_select_not_pressed =!s_joypad.select;
                left_or_b_not_pressed = !s_joypad.a;
                right_or_a_not_pressed = !s_joypad.b;
            }
        }
        uint8_t full { 0 };
        struct {
            uint8_t unused : 2;
            bool select_direction_buttons   : 1;
            bool select_action_buttons      : 1;
            bool down_or_start_not_pressed  : 1;
            bool up_or_select_not_pressed   : 1;
            bool left_or_b_not_pressed      : 1;
            bool right_or_a_not_pressed     : 1;
        };
    } m_gb_joypad;

#if 0
    uint8_t m_serial_transfer_data { 0 };
    uint8_t m_sio_control { 0 };
    uint8_t m_Divider { 0 };
    uint8_t m_timer_counter { 0 };
    uint8_t m_timer_modulo { 0 };
    uint8_t m_timer_control { 0 }; 
#endif
    union {
        uint8_t full { 0 };
        struct {
            uint8_t unused : 3;
            bool joypad : 1;
            bool serial : 1;
            bool timer : 1;
            bool lcd_stat : 1;
            bool vblank : 1;
        };
    } m_interrupt_flag {};

    struct [[gnu::packed]] {
        uint8_t sweep { 0 };
        uint8_t length_and_duty { 0 };
        uint8_t envelope { 0 };
        union {
            uint16_t freq { 0 };
            struct [[gnu::packed]] {
                uint8_t freq_low;
                uint8_t freq_high;
            };
        };
    } m_sound1 {};
    
    struct [[gnu::packed]] {
        uint8_t length_and_duty { 0 };
        uint8_t envelope { 0 };
        union {
            uint16_t freq { 0 };
            struct [[gnu::packed]] {
                uint8_t freq_low;
                uint8_t freq_high;
            };
        };
    } m_sound2 {};

    struct [[gnu::packed]] {
        uint8_t on_off { 0 };
        uint8_t length { 0 };
        uint8_t output_level { 0 };
        union {
            uint16_t freq { 0 };
            struct [[gnu::packed]] {
                uint8_t freq_low;
                uint8_t freq_high;
            };
        };
    } m_sound3 {};

    struct [[gnu::packed]] {
        uint8_t length { 0 };
        uint8_t envelope { 0 };
        uint8_t polynomial_counter { 0 };
        uint8_t reset_and_counter { 0 };
    } m_sound4 {};

    struct [[gnu::packed]] {
        uint8_t channel_control { 0 };
        uint8_t output_selection { 0 };
        uint8_t on_off { 0 };
    } m_sound_info {};

    static constexpr const auto wave_pattern_ram_size =
                      *MemoryRegister::WavePatternRamEnd
                    - *MemoryRegister::WavePatternRam + 1;
    uint8_t m_wave_pattern_ram[wave_pattern_ram_size] { }; 

    struct Area {
        uint16_t start;
        uint16_t end;
    };
    union {
        friend Memory;
    public:
        auto enable_ppu_and_lcd() const
        {
            return m_enable_ppu_and_lcd;
        }

        auto window_tile_map_area() const
        {
            return !m_window_tile_map_area
                   ? Area { 0x9800, 0x9BFF }
                   : Area { 0x9C00, 0x9FFF };
        }

        auto window_enable() const
        {
            return m_background_and_window_enable
                   ? true : m_window_enable; 
        }

        auto background_and_window_tile_data_area() const
        {
            return !m_background_and_window_tile_area
                   ? Area { 0x8800, 0x97FF }
                   : Area { 0x8000, 0x8FFF };
        }

        auto background_tile_map_area() const
        {
            return !m_background_tile_map_area
                   ? Area { 0x9800, 0x9BFF }
                   : Area { 0x9C00, 0x9FFF };
        }

        uint8_t object_height() const
        {
            return m_object_height ? 16 : 8;
        }

        auto object_enable() const
        {
            return m_object_enable;
        }

        auto background_and_window_enable()
        {
            return m_background_and_window_enable;
        }

    private:
        uint8_t full {};
        struct {
            bool m_enable_ppu_and_lcd              : 1;
            bool m_window_tile_map_area            : 1;
            bool m_window_enable                   : 1;
            bool m_background_and_window_tile_area : 1;
            bool m_background_tile_map_area        : 1;
            bool m_object_height                   : 1;
            bool m_object_enable                   : 1;
            bool m_background_and_window_enable    : 1;
        };
    } m_lcd_control {};
    
    union {
        friend Memory;
    public:
        enum class ModeFlag : uint8_t {
            HBlank = 0,
            VBlank = 1,
            SearchingOAM = 2,
            TransferringDatatoLCDController = 3,
        };
        struct [[gnu::packed]] {
            bool unused : 1;
            bool lyc_is_equal_to_ly_interrupt_source : 1;
            bool mode_2_oam_stat_interrupt_source    : 1;
            bool mode_1_vblank_stat_interrupt_source : 1;
            bool mode_0_hblank_stat_interrupt_source : 1;
            bool lyc_is_equal_to_ly                  : 1;
            ModeFlag mode_flag                       : 2;
        };
    private:
        uint8_t full { 0 };

        void write(uint8_t value)
        {
            if (value & 0b00000111)
                wrote_anyway(value);
            full = value & 0b11111000;
        }

        uint8_t read() const { return full; }
    } m_lcd_stat;

    struct [[gnu::packed]] {
        uint8_t y { 0 };
        uint8_t x { 0 };
    } m_scroll {};
    uint8_t m_lcd_y_coordinate { 0 }; 
    // uint8_t m_dma_transfer { 0 }; 

    union Palette {
        uint8_t full { 0 };
        struct [[gnu::packed]] {
            uint8_t first  : 2;
            uint8_t second : 2;
            uint8_t third  : 2;
            uint8_t fourth : 2;
        };
    };
    Palette m_background_palette {};
    Palette m_object_palette0 {}; 
    Palette m_object_palette1 {}; 
    
    struct [[gnu::packed]] {
        uint8_t x { 0 };
        uint8_t y { 0 };
    } m_window_start;
    
    union {
        uint8_t full { 0 };
        struct [[gnu::packed]] {
            uint8_t unused : 3;
            bool joypad    : 1;
            bool serial    : 1;
            bool timer     : 1;
            bool lcd_stat  : 1;
            bool vblank    : 1;
        };
    } m_interrupt_enable {};

    static bool s_log_invalid_access;
};

}
