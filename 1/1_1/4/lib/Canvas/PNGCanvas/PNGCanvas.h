//
// Created by mrLogic on 7/10/2024.
//
////#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
////#endif // STB_IMAGE_WRITE_IMPLEMENTATION
////#ifndef STB_TRUETYPE_IMPLEMENTATION
//#define STB_TRUETYPE_IMPLEMENTATION
//#include "stb_truetype.h"
////#endif // STB_TRUETYPE_IMPLEMENTATION

#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "../ICanvas.h"

#ifndef PNG_CANVAS_H
#define PNG_CANVAS_H

struct Color {
    uint8_t r, g, b, a;
};

Color StringToColor(const std::string& colorString);

class PNGCanvas : public ICanvas
{
public:
    PNGCanvas(int w, int h, const std::string& outFileName) : m_w(w), m_h(h), m_fileName(std::move(outFileName)), m_color({255, 255, 255, 255}), m_x(0), m_y(0)
    {
        m_pixels.resize(m_w * m_h * 4, 255); // Белый фон
    }

    ~PNGCanvas() override
    {
        SaveToFile(m_fileName);
    }

    void SetColor(const std::string& color) override
    {
        m_color = StringToColor(color);
    }

    void MoveTo(double x, double y) override
    {
        m_x = x;
        m_y = y;
    }

    void LineTo(double x, double y) override
    {
        DrawLine(m_x, m_y, x, y);
        MoveTo(x, y);
    }

    void DrawEllipse(double cx, double cy, double rx, double ry) override {
        int segments = 100;
        double angleStep = 2 * M_PI / segments;

        double prevX = cx + rx;
        double prevY = cy;

        for (int i = 1; i <= segments; ++i)
        {
            double angle = i * angleStep;
            double newX = cx + rx * cos(angle);
            double newY = cy + ry * sin(angle);
            DrawLine(prevX, prevY, newX, newY);
            prevX = newX;
            prevY = newY;
        }
    }

    void DrawText(double left, double top, double fontSize, const std::string &text) override;

    void SaveToFile(const std::string& filename);

private:
    int m_w, m_h;
    Color m_color{};
    double m_x, m_y;
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

    void DrawLine(double x1, double y1, double x2, double y2)
    {
        int ix1 = static_cast<int>(std::round(x1));
        int iy1 = static_cast<int>(std::round(y1));
        int ix2 = static_cast<int>(std::round(x2));
        int iy2 = static_cast<int>(std::round(y2));

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
                err -= dy; ix1 += sx;
            }
            if (e2 < dx) { err += dx; iy1 += sy; }
        }
    }
};

#endif // PNG_CANVAS_H
