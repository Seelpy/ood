#pragma once

#include "./../IShapStrategy.h"

namespace shapes
{
    class CEllipseStrategy: public IShapeStrategy
    {
    public:
        CEllipseStrategy(Point c, double rx, double ry): m_c(c)
        {
            m_rx = rx;
            m_ry = ry;
        }

        void Draw(gfx::ICanvas &canvas) override
        {
            canvas.DrawEllipse(m_c, m_rx, m_ry);
        }

    private:
        Point m_c;
        double m_rx, m_ry;
    };
}
