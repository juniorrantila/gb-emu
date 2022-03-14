#pragma once
#include <Forward.h>
#include <GB/Register.h>
#include <GB/Memory.h>

namespace GB {

enum class PrintAssembly {
    No,
    Yes,
};

enum class LogRegisterEvents {
    No,
    Yes,
};

class CPU {
public:
    constexpr CPU(Memory& memory,
            PrintAssembly pa = PrintAssembly::No,
            LogRegisterEvents lre = LogRegisterEvents::No
            )
        : memory(memory)
        , m_print_assembly(pa == PrintAssembly::Yes)
    {
        if (lre == LogRegisterEvents::Yes)
            set_log_register_events(true);
        else
            set_log_register_events(false);
    }

    void run_next_instruction();
    void run_next_cycles(uint16_t cycles);

    void set_print_assembly(bool yes_no)
    {
        m_print_assembly = yes_no;
    }

    void set_log_register_events(bool yes_no)
    {
        if (yes_no == true) {
            Register::on_overflow([&] {
                f.carry = true;
                __builtin_printf("did overflow\n");
            });
            Register::on_zero([&] {
                f.zero = true;
                __builtin_printf("did zero\n");
            });

            WideRegister::on_overflow([&] {
                f.carry = true;
                __builtin_printf("did overflow wide\n");
            });
            WideRegister::on_zero([&] {
                f.zero = true;
                __builtin_printf("did zero wide\n");
            });
        } else {
            Register::on_overflow([&] {
                f.carry = true;
            });
            Register::on_zero([&] {
                f.zero = true;
            });
            WideRegister::on_overflow([&] {
                f.carry = true;
            });
            WideRegister::on_zero([&] {
                f.zero = true;
            });
        }
    }

    void sleep_for_cycles(uint16_t cycles)
    {
        m_slept_cycles += cycles;
    }

private:
    template <typename T, InstructionTag Tag>
    void run_instruction();

    template <typename T, InstructionTag Tag>
    void disassemble_and_dump(T instruction) const;


public:
    Memory& memory;

    union {
        WideRegister af {};
        struct [[gnu::packed]] {
            Register a;
            FlagsRegister f;
        };
    };
    #define GB_REGISTER(upper, lower)     \
        union {                           \
            struct {                      \
                Register upper;           \
                Register lower;           \
            };                            \
            WideRegister upper##lower {}; \
    }
    GB_REGISTER(b, c);
    GB_REGISTER(d, e);
    GB_REGISTER(h, l);
    #undef GB_REGISTER
    WideRegister sp {};
    WideRegister pc {};
private:
    uint16_t m_slept_cycles { 0 };
public:
    bool took_branch : 1 { false };
private:
    bool m_print_assembly : 1 { false };
};


}
