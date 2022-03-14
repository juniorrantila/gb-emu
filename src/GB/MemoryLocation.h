#pragma once
#include <GB/Register.h>
#include <stdint.h>

namespace GB {

class MemoryLocation {
    using OnRead = std::function<uint8_t()>;
    using OnWrite = std::function<void(uint8_t)>;
public:
    MemoryLocation()
        : m_on_read([]{ return 0xFF; })
        , m_on_write([](uint8_t){})
    {
    }

    static MemoryLocation read_only(uint8_t const& read,
                                    OnWrite on_write =
                                        [](uint8_t){})
    {
        return { read, on_write };
    }

    static MemoryLocation write_only(uint8_t& write,
                                     OnRead on_read = 
                                        []{ return 0xFF; })
    {
        return { write, on_read };
    }

    static MemoryLocation read_write(uint8_t const& read,
                                     uint8_t& write)
    {
        return { read, write };
    }

    static MemoryLocation read_write(uint8_t& read_write)
    {
        return { read_write, read_write };
    }

    static MemoryLocation special(OnRead on_read,
                                  OnWrite on_write)
    {
        return { on_read, on_write };
    }

    constexpr void operator = (uint8_t value)
    {
        write(value);
    }

    constexpr void operator = (Register r)
    {
        write(r.value);
    }

    constexpr uint8_t operator + (bool other)
    {
        return read() + other;
    }

    constexpr void operator ++ () { write(read()+1); }
    constexpr void operator ++ (int) { write(read()+1); }
    constexpr void operator -- () { write(read()-1); }
    constexpr void operator -- (int) { write(read()-1); }

    constexpr uint8_t read() const
    { 
        return m_on_read();
    }

    constexpr void write(uint8_t value)
    {
        m_on_write(value);
    }

private:
    
    MemoryLocation(uint8_t const& read, OnWrite on_write)
        : m_on_read([&]{ return read; })
        , m_on_write(on_write)
    {
    }

    MemoryLocation(uint8_t& write, OnRead on_read)
        : m_on_read(on_read)
        , m_on_write([&](uint8_t value){ write = value; })
    {
    }

    MemoryLocation(uint8_t const& read, uint8_t& write)
        : m_on_read([&]{ return read; })
        , m_on_write([&](uint8_t value) { write = value; })
    {
    }

    MemoryLocation(OnRead on_read, OnWrite on_write)
        : m_on_read(on_read)
        , m_on_write(on_write)
    {
    }

    OnRead m_on_read;
    OnWrite m_on_write;
};
// constexpr auto operator - (MemoryLocation const& location, int value) { return location.read()-value; }
// constexpr auto operator + (int value, MemoryLocation const& location) { return location.read()+value; }
// constexpr auto operator - (int value, MemoryLocation const& location) { return location.read()-value; }

}
