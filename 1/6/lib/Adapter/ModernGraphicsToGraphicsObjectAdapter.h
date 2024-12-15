#pragma once

#include "./../Graphic/graphics_lib.h"
#include "./../Graphic/modern_graphics_lib.h"
#include <exception>

// TODO: композиция или агрегация лучше
namespace adapter
{
    class ModernGraphicsToGraphicsObjectAdapter : public graphics_lib::ICanvas
    {
    public:
        explicit ModernGraphicsToGraphicsObjectAdapter(modern_graphics_lib::ModernGraphicsRenderer &modernRenderer)
                : m_renderer(modernRenderer),
                  m_start(0, 0),
                  m_color(0, 0, 0, 0)
        {
            m_renderer.BeginDraw();
        }

        void SetColor(uint32_t rgbaColor) override
        {
            float a = ConvertByteTyFloatFromColor(rgbaColor, 3);
            float r = ConvertByteTyFloatFromColor(rgbaColor, 0); // TODO: недостатоно хорошо адаптера
            float g = ConvertByteTyFloatFromColor(rgbaColor, 1);
            float b = ConvertByteTyFloatFromColor(rgbaColor, 0);

            m_color = {r, g, b, a};
        }

        void MoveTo(int x, int y) override
        {
            m_start = {x, y};
        }

        void LineTo(int x, int y) override
        {
            const modern_graphics_lib::Point end(x, y);

            m_renderer.DrawLine(m_start, end, m_color);

           m_start = end; // TODO: не работает коммент
        }

    private:
        static float ConvertByteTyFloatFromColor(uint32_t rgbaColor, uint pos)
        {
            return float(((rgbaColor >> 8*pos) & 0xFF)) / 255.0f;;
        }

        modern_graphics_lib::RGBAColor m_color;
        modern_graphics_lib::Point m_start;
        modern_graphics_lib::ModernGraphicsRenderer &m_renderer;
    };
}
