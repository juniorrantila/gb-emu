#pragma once
#include <stdint.h>
#include <sys/types.h>
#include <Forward.h>
#include <type_traits>
#include <functional>

namespace GB {

struct [[gnu::packed]] [[nodiscard]] FlagsRegister {
    bool zero : 1;
    bool sub : 1;
    bool half_carry : 1;
    bool carry : 1;
    uint8_t unused : 4;
    
    void clear()
    {
        zero = false;
        sub = false;
        half_carry = false;
        carry = false;
    }
};

template<typename T>
concept memory_location_t = std::is_same_v<T, MemoryLocation>;

struct [[gnu::packed]] Register {
    constexpr Register() {}

    static void on_overflow(std::function<void()> overflow)
    {
        m_on_overflow = overflow;
    }

    static void on_zero(std::function<void()> zero)
    {
        m_on_zero = zero;
    }

    constexpr void operator = (uint8_t new_value)
    {
        if (new_value == 0)
            m_on_zero();
        value = new_value;
    }

    template <memory_location_t T>
    constexpr void operator = (T location)
    {
        value = location.read();
    }

    constexpr uint8_t operator + (Register other) const
    {
        return value + other.value;
    }

    constexpr uint8_t operator - (Register other) const
    {
        return value - other.value;
    }

    template <memory_location_t T>
    constexpr void operator += (T location)
    {
        value += location.read();
    }

    template <memory_location_t T>
    constexpr void operator -= (T location)
    {
        value -= location.read();
    }

    constexpr void operator += (Register other)
    {
        value = add(other.value);
    }

    constexpr void operator -= (Register other)
    {
        value = sub(other.value);
    }

    constexpr void operator += (size_t other)
    {
        value = add(other);
    }

    constexpr void operator -= (size_t other)
    {
        value = sub(other);
    }

    constexpr void operator &= (Register other)
    {
        value = and_(other.value);
    }

    template<memory_location_t T>
    constexpr void operator &= (T loc)
    {
        value = and_(loc.read());
    }

    constexpr void operator ^= (Register other)
    {
        value = xor_(other.value);
    }

    template<memory_location_t T>
    constexpr void operator ^= (T loc)
    {
        value = xor_(loc.read());
    }

    constexpr void operator |= (Register other)
    {
        value = or_(other.value);
    }

    template<memory_location_t T>
    constexpr void operator |= (T loc)
    {
        value = or_(loc.read());
    }

    constexpr uint16_t operator ++ ()
    {
        value = add(1);
        return value;
    }

    constexpr uint16_t operator ++ (int)
    {
        value = add(1);
        return value-1;
    }
    constexpr uint16_t operator -- ()
    {
        value = sub(1);
        return value;
    }
    constexpr uint16_t operator -- (int)
    {
        value = sub(1);
        return value+1;
    }

    constexpr auto operator ~ () const
    {
        return ~value;
    }

    constexpr auto operator & (uint8_t mask) const
    {
        return value & mask;
    }
    constexpr auto operator & (Register other) const
    {
        return value & other.value;
    }

    constexpr auto operator | (uint8_t other) const
    {
        return value | other;
    }
    constexpr auto operator | (Register other) const
    {
        return value & other.value;
    }

    constexpr auto operator ^ (uint8_t other) const
    {
        return value ^ other;
    }
    constexpr auto operator ^ (Register other) const
    {
        return value ^ other.value;
    }

    constexpr uint8_t add(uint16_t other) const
    {
        auto result = value;
        if (__builtin_add_overflow(value, other, &result))
            m_on_overflow();
        if (result == 0)
            m_on_zero();
        return result;
    }

    constexpr uint8_t sub(uint16_t other) const
    {
        auto result = value;
        if (__builtin_sub_overflow(value, other, &result))
            m_on_overflow();
        if (result == 0)
            m_on_zero();
        return result;
    }

    constexpr uint8_t and_(uint16_t other) const
    {
        auto result = value & other;
        if (result == 0)
            m_on_zero();
        return result;
    }

    constexpr uint8_t or_(uint16_t other) const
    {
        auto result = value | other;
        if (result == 0)
            m_on_zero();
        return result;
    }

    constexpr uint8_t xor_(uint16_t other) const
    {
        auto result = value ^ other;
        if (result == 0)
            m_on_zero();
        return result;
    }

    uint8_t value { 0 };

private:
    static std::function<void()> m_on_overflow;
    static std::function<void()> m_on_zero;
};
constexpr auto operator + (Register r, int value)
{
    return r.value+value;
}
constexpr auto operator - (Register r, int value)
{
    return r.value-value;
}
constexpr auto operator + (int value, Register r)
{
    return r.value+value;
}
constexpr auto operator - (int value, Register r)
{
    return r.value-value;
}

struct WideRegister {
    constexpr WideRegister() {}

    static void on_overflow(std::function<void()> overflow)
    {
        m_on_overflow = overflow;
    }

    static void on_zero(std::function<void()> zero)
    {
        m_on_zero = zero;
    }

    constexpr void operator = (uint16_t new_value)
    {
        if (new_value == 0)
            m_on_zero();
        value = new_value;
    }
    constexpr void operator += (WideRegister other)
    {
        value = add(other.value);
    }
    constexpr void operator -= (WideRegister other)
    {
        value = sub(other.value);
    }
    constexpr void operator += (Register other)
    {
        value = add(other.value);
    }
    constexpr void operator -= (Register other)
    {
        value = sub(other.value);
    }
    constexpr void operator += (size_t other)
    {
        value = add(other);
    }
    constexpr void operator -= (size_t other)
    {
        value = sub(other);
    }

    constexpr uint16_t operator ++ ()
    {
        value = add(1);
        return value;
    }

    constexpr uint16_t operator ++ (int)
    {
        value = add(1);
        return value-1;
    }
    constexpr uint16_t operator -- ()
    {
        value = sub(1);
        return value;
    }
    constexpr uint16_t operator -- (int)
    {
        value = sub(1);
        return value+1;
    }

    constexpr uint16_t add(uint16_t other) const
    {
        auto result = value;
        if (__builtin_add_overflow(value, other, &result))
            m_on_overflow();
        if (value == 0)
            m_on_zero();
        return result;
    }

    constexpr uint16_t sub(uint16_t other) const
    {
        auto result = value;
        if (__builtin_sub_overflow(value, other, &result))
            m_on_overflow();
        if (value == 0)
            m_on_zero();
        return result;
    }

    constexpr uint16_t operator + (uint16_t v) const
    {
        return value+v;
    }
    constexpr uint16_t operator - (uint16_t v) const
    {
        return value-v;
    }
    constexpr uint16_t operator + (Register r) const
    {
        return value+r.value;
    }
    constexpr uint16_t operator - (Register r) const
    {
        return value+r.value;
    }
    constexpr uint16_t operator + (WideRegister r) const
    {
        return value+r.value;
    }
    constexpr uint16_t operator - (WideRegister r) const
    {
        return value+r.value;
    }

    constexpr bool operator < (uint16_t v) const
    {
        return value < v;
    }
    constexpr bool operator <= (uint16_t v) const
    {
        return value <= v;
    }
    constexpr bool operator > (uint16_t v) const
    {
        return value > v;
    }
    constexpr bool operator >= (uint16_t v) const
    {
        return value >= v;
    }
    constexpr bool operator == (uint16_t v) const
    { 
        return value == v;
    }

    constexpr uint8_t upper() const
    {
        return (value & 0xFF00) >> 8;
    }
    constexpr uint8_t lower() const
    {
        return (value & 0x00FF);
    }
    
    uint16_t value { 0 };

private:
    static std::function<void()> m_on_overflow;
    static std::function<void()> m_on_zero;
};


}
