#include <GB/Ppu.h>
#include <GB/Memory.h>

namespace GB {

void PPU::draw_frame(bool is_debug_mode)
{
    m_canvas.clear();
    auto scroll = m_memory.scroll();
    if (is_debug_mode) {
        m_canvas.draw_viewport_outline(scroll.x, scroll.y);
        m_texture.update(m_canvas.pixels(),
                         m_canvas.pitch()
                        );

        SDL::Rect rect {
            0, 0,
            m_physical_width,
            m_physical_height,
        };
        m_renderer.copy(m_texture, rect);
        
        return;
    }


}


}
