#pragma once
#include <GB/Hardware.h>
#include <GUI/Canvas.h>
#include <Point.h>
#include <stdint.h>
#include <Util.h>
#include <vector>

struct Tile {
    uint8_t data[16];

    void draw_on(Canvas& canvas, uint8_t x_offset, uint8_t y_offset) const
    {
        for (auto y = 0; y<8; y++)
            for (auto x = 0; x<8; x++)
                if (auto combined = combine(7-x, data[2*y], data[2*y+1]))
                    canvas.at(x+x_offset, y+y_offset) = grayscale(0xFF - 0x55 * combined);
    }
};

class Tiles {
public:
    void append(Tile tile, Point point)
    {
        m_tiles.push_back(tile);
        m_points.push_back(point);
    }

    void draw_on(Canvas& canvas) const
    {
        for (uint16_t i = 0; i < m_tiles.size(); i++) {
            auto point = m_points[i];
            m_tiles[i].draw_on(canvas, point.x, point.y);
        }
    }
private:
    std::vector<Tile> m_tiles;
    std::vector<Point> m_points;
};
