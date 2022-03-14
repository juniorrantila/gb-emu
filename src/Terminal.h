#pragma once

namespace Terminal {

inline void hide_cursor(bool hide = true)
{
    if (hide)
        __builtin_printf("\033[?25l\n");
    else
        __builtin_printf("\033[?25h\n");
}

inline void clear()
{
    __builtin_printf("\033[2J\n");
}

inline void move_cursor_home()
{
    __builtin_printf("\033[H\n");
}

}
