#pragma once

#include "./../IShapStrategy.h"

namespace shapes
{
    class CTriangleStrategy : public IShapeStrategy
    {
    public:
        CTriangleStrategy(Point p1, Point p2, Point p3): m_p1(p1), m_p2(p2), m_p3(p3)
        {
        }

        void Draw(gfx::ICanvas &canvas) override
        {
            canvas.DrawLine(m_p1, m_p2);
            canvas.DrawLine(m_p2, m_p3);
            canvas.DrawLine(m_p3, m_p1);
        }

    private:
        Point m_p1, m_p2, m_p3;
    };
}
