#pragma once

#include <iostream>
namespace modern_graphics_lib
{
    using namespace std;

    class Point
    {
    public:
        Point(int x, int y)
                : x(x), y(y)
        {}

        int x;
        int y;
    };

    class RGBAColor
    {
    public:
        RGBAColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
        {}

        float r, g, b, a;
    };

    class ModernGraphicsRenderer
    {
    public:
        explicit ModernGraphicsRenderer(ostream &strm)
                : m_out(strm)
        {}

        ~ModernGraphicsRenderer()
        {
            if (m_drawing)
            {
                EndDraw();
            }
        }

        void BeginDraw()
        {
            if (m_drawing)
            {
                throw logic_error("Drawing has already begun");
            }
            m_out << "<draw>" << endl;
            m_drawing = true;
        }

        void DrawLine(const Point &start, const Point &end, const RGBAColor &color)
        {
            if (!m_drawing)
            {
                throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
            }

            m_out << std::printf(R"(  <line fromX="%d" fromY="%d" toX="%d" toY="%d">)", start.x, start.y, end.x, end.y)
                  << std::endl;
            m_out << std::printf(R"(    <color r="%f" g="%f" b="%f" a="%f" />)", color.r, color.g, color.b, color.a)
                  << std::endl;
            m_out << R"(  </line>)" << std::endl;
        }

        void EndDraw()
        {
            if (!m_drawing)
            {
                throw logic_error("Drawing has not been started");
            }
            m_out << "</draw>" << endl;
            m_drawing = false;
        }

    private:
        ostream &m_out;
        bool m_drawing = false;
    };
}