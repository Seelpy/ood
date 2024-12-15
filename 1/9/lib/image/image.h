#pragma once

#include <cassert>
#include <iostream>
#include <vector>
#include "../proxy/cow.h"
#include "tile.h"
#include "../geom/size.h"

// В каком случае модификаци вызывает создание копии

class Image
{
public:
    explicit Image(Size size, uint32_t color = 0xFFFFFF)
            : m_size(size),
              m_tiles(size.height, std::vector<CoW<Tile>>(size.width, CoW<Tile>(Tile(color))))
    {}

    [[nodiscard]] Size GetSize() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] uint32_t GetPixel(Point p) const noexcept
    {
        if (!In(p))
        {
            return 0xFFFFFF;
        }

        auto [tileP, pixelP] = GetTilePixelCoords(p);
        return m_tiles[tileP.y][tileP.x]->GetPixel({pixelP.x, pixelP.y});
    }

    void SetPixel(Point p, uint32_t color)
    {
        if (!In(p))
        {
            return;
        }

        auto [tileP, pixelP] = GetTilePixelCoords(p);
        m_tiles[tileP.y][tileP.x].Write(
                [&](Tile &tile) {
                    tile.SetPixel({pixelP.x, pixelP.y}, color);
                });
    }

private:
    static std::pair<Point, Point> GetTilePixelCoords(Point source)
    {
        return {{source.x / Tile::SIZE, source.y / Tile::SIZE},
                {source.x % Tile::SIZE, source.y % Tile::SIZE}};
    }

    [[nodiscard]] bool In(Point p) const
    {
        return p.x >= 0 && p.x < m_size.width && p.y >= 0 && p.y < m_size.height;
    }

    Size m_size;
    std::vector<std::vector<CoW<Tile>>> m_tiles;
};
