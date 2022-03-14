#pragma once
#include <GB/Hardware.h>
#include <GUI/Canvas.h>
#include <GUI/SDLWrapper.h>
#include <Forward.h>
#include <utility>

namespace GB {

class PPU {
public:
    PPU(Memory& memory,
        SDL::Renderer&& renderer,
        int32_t physical_width,
        int32_t physical_height
        )
        : m_memory(memory)
        , m_renderer(std::move(renderer))
        , m_texture(SDL::Texture::create(renderer,
                                        internal_width,
                                        internal_height
                                        ))
        , m_physical_width(physical_width)
        , m_physical_height(physical_height)
    {
    }

    constexpr ~PPU()
    {
        m_texture.destroy();
        m_renderer.destroy();
    }

    void draw_frame(bool is_debug_mode);

private:
    Canvas m_canvas {};
    Memory& m_memory;
    SDL::Renderer m_renderer;
    SDL::Texture m_texture;
    int32_t m_physical_width { 0 };
    int32_t m_physical_height { 0 };
};

}
