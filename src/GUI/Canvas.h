#pragma once
#include <stdint.h>
#include <GB/Hardware.h>

class Canvas {
public:
    constexpr static uint16_t internal_width()
    {
        return GB::internal_width; 
    }
    constexpr static uint16_t internal_height()
    {
        return GB::internal_height;
    }
    constexpr static uint16_t viewport_width()
    {
        return GB::viewport_width;
    };
    constexpr static uint16_t viewport_height()
    {
        return GB::viewport_height;
    };

    uint32_t& at(uint16_t x, uint16_t y)
    {
        return m_pixels[y*GB::internal_width+x];
    }

    uint32_t const& at(uint16_t x, uint16_t y) const
    {
        return m_pixels[y*GB::internal_width+x];
    }

    void draw_viewport_outline(uint16_t x, uint16_t y);

    void clear(uint32_t color = 0xFFFFFFFF)
    {
        for (auto& pixel : m_pixels)
            pixel = color;
    }

    uint32_t const* pixels() const { return m_pixels; }

    constexpr auto pitch() const
    {
        return internal_width()*sizeof(m_pixels[0]);
    }

private:
    uint32_t m_pixels[GB::internal_height*GB::internal_width];
};
