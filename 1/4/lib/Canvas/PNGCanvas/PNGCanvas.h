#pragma once

#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "../ICanvas.h"
#include <utility>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_truetype.h"

namespace gfx
{
    struct RGBAColor
    {
        uint8_t r, g, b, a;
    };

    RGBAColor ColorToRGBA(Color color)
    {
        switch (color)
        {
            case Color::BLACK:
                return {0, 0, 0, 0};
            case GREEN:
                return {0, 255, 0, 255};
            case RED:
                return {255, 0, 0, 255};
            case BLUE:
                return {0, 0, 255, 255};
            case YELLOW:
                return {255, 255, 0, 255};
            case PINK:
                return {255, 125, 125, 255};
        }
    }

    class PNGCanvas : public ICanvas
    {
    public:
        PNGCanvas(int w, int h, std::string outFileName) : m_w(w), m_h(h), m_fileName(std::move(outFileName)),
                                                           m_color({255, 255, 255, 255})
        {
            m_pixels.resize(m_w * m_h * 4, 255);
        }

        ~PNGCanvas() override
        {
            SaveToFile(m_fileName);
        }

        void SetColor(Color color) override
        {
            m_color = ColorToRGBA(color);
        }

        void DrawLine(Point from, Point to) override // TODO: разобраться
        {
            int ix1 = static_cast<int>(std::round(from.x));
            int iy1 = static_cast<int>(std::round(from.y));
            int ix2 = static_cast<int>(std::round(to.x));
            int iy2 = static_cast<int>(std::round(to.y));

            int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
            int sx = (ix1 < ix2) ? 1 : -1;
            int sy = (iy1 < iy2) ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                PutPixel(ix1, iy1);
                if (ix1 == ix2 && iy1 == iy2) break;
                int e2 = 2 * err;
                if (e2 > -dy)
                {
                    err -= dy;
                    ix1 += sx;
                }
                if (e2 < dx)
                {
                    err += dx;
                    iy1 += sy;
                }
            }
        }

        void DrawEllipse(Point center, double rx, double ry) override
        {
            int segments = 100;
            double angleStep = 2 * M_PI / segments;

            double prevX = center.x + rx;
            double prevY = center.y;

            for (int i = 1; i <= segments; ++i)
            {
                double angle = i * angleStep;
                double newX = center.x + rx * cos(angle);
                double newY = center.y + ry * sin(angle);
                DrawLine({prevX, prevY}, {newX, newY});
                prevX = newX;
                prevY = newY;
            }
        }

        void SaveToFile(const std::string &filename)
        {
            stbi_write_png(filename.c_str(), m_w, m_h, 4, m_pixels.data(), m_w * 4);
        }

    private:
        int m_w, m_h;
        RGBAColor m_color{};
        std::vector<uint8_t> m_pixels;
        std::string m_fileName;

        void PutPixel(int x, int y)
        {
            if (x >= 0 && x < m_w && y >= 0 && y < m_h)
            {
                int index = 4 * (y * m_w + x);
                m_pixels[index] = m_color.r;
                m_pixels[index + 1] = m_color.g;
                m_pixels[index + 2] = m_color.b;
                m_pixels[index + 3] = m_color.a;
            }
        }
    };
}

