#pragma once
#include <GB/Hardware.h>
#include <GUI/Font.h>
#include <GUI/Tile.h>

namespace TestScene {

inline Tile tile_a = {
    0b01111100,
    0b01111100,
    0b00000000,
    0b11000110,
    0b11000110,
    0b00000000,
    0b00000000,
    0b11111110,
    0b11000110,
    0b11000110,
    0b00000000,
    0b11000110,
    0b11000110,
    0b00000000,
    0b00000000,
    0b00000000,
};

inline Tiles basic()
{
    auto tiles = Tiles();

    tiles.append(tile_a,
                { GB::viewport_width/2-16-2, GB::viewport_height/2-16 });
    tiles.append(tile_a,
                { GB::viewport_width/2-8-2,  GB::viewport_height/2-16 });
    tiles.append(tile_a,
                { GB::viewport_width/2-2,    GB::viewport_height/2-16 });
    tiles.append(tile_a,
                { GB::viewport_width/2+8-2,  GB::viewport_height/2-16 });

    tiles.append(tile_a,
                { GB::viewport_width/2-16-2, GB::viewport_height/2-8 });
    tiles.append(tile_a,
                { GB::viewport_width/2-8-2,  GB::viewport_height/2-8 });
    tiles.append(tile_a,
                { GB::viewport_width/2-2,    GB::viewport_height/2-8 });
    tiles.append(tile_a,
                { GB::viewport_width/2+8-2,  GB::viewport_height/2-8 });

    tiles.append(tile_a,
                { GB::viewport_width/2-16-2, GB::viewport_height/2 });
    tiles.append(tile_a,
                { GB::viewport_width/2-8-2,  GB::viewport_height/2 });
    tiles.append(tile_a,
                { GB::viewport_width/2-2,    GB::viewport_height/2 });
    tiles.append(tile_a,
                { GB::viewport_width/2+8-2,  GB::viewport_height/2 });

    tiles.append(tile_a,
                { GB::viewport_width/2-16-2, GB::viewport_height/2+8 });
    tiles.append(tile_a,
                { GB::viewport_width/2-8-2,  GB::viewport_height/2+8 });
    tiles.append(tile_a,
                { GB::viewport_width/2-2,    GB::viewport_height/2+8 });
    tiles.append(tile_a,
                { GB::viewport_width/2+8-2,  GB::viewport_height/2+8 });
    
    return tiles;
}

inline Tiles scene_from_text(char const* str, uint16_t length)
{
    auto scene = Tiles();

    uint8_t x = 0x00-0x08;
    uint8_t y = 0;

    for (size_t i = 0; i<length; i++) {
        if (str[i] == '\n') {
            x = 0x00 - 0x08;
            y = (y + 0x08) % 0xA0;
            continue;
        }
        if (x >= 0xA0 - 0x08) {
            x = 0x00 - 0x08;
            y = (y + 0x08) % 0xA0;
        }
        x += 0x08;
        scene.append(GUI::font.at(str[i]), { x, y });
    }

    return scene;
}

inline Tiles text()
{
    auto message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789\n\n"
                   "THE QUICK BROWN FOX\n"
                   "     JUMPS OVER\n"
                   "    THE LAZY DOG";
    return scene_from_text(message, __builtin_strlen(message));
}


}
