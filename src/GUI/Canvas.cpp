#include <GUI/Canvas.h>
#include <GB/Hardware.h>

void Canvas::draw_viewport_outline(uint16_t x, uint16_t y)
{
    x %= internal_width();
    y %= internal_height();

    for (auto i = x; i<viewport_width()+x; i++) {
        auto first_bar_x = i % internal_width();
        auto first_bar_y = y % internal_height();
        at(first_bar_x, first_bar_y) ^= 0x7F7F7F7F;

        auto second_bar_x = i % internal_width();
        auto second_bar_y = (y+viewport_height()) % internal_height();
        at(second_bar_x, second_bar_y) ^= 0x7F7F7F7F;
    }

    for (auto i = y+1; i<viewport_height()+y; i++) {
        auto first_bar_x = x % internal_width();
        auto first_bar_y = i % internal_height();
        at(first_bar_x, first_bar_y) ^= 0x7F7F7F7F;

        auto second_bar_x = (x+viewport_width()-1) % internal_width();
        auto second_bar_y = i % internal_height();
        at(second_bar_x, second_bar_y) ^= 0x7F7F7F7F;
    }
}

