#pragma once

#include "./../IShapStrategy.h"

namespace shapes
{
    class CRectangleStrategy : public IShapeStrategy
    {
    public:
        CRectangleStrategy(Point topLeft, Point rightBottom): m_tl(topLeft), m_br(rightBottom)
        {
        }

        void Draw(gfx::ICanvas &canvas) override
        {
            canvas.DrawLine(m_tl, {m_br.x, m_tl.y});
            canvas.DrawLine({m_br.x, m_tl.y}, m_br);
            canvas.DrawLine(m_br, {m_tl.x, m_br.y});
            canvas.DrawLine({m_tl.x, m_br.y}, m_tl);
        }

    private:
        Point m_tl, m_br;
    };
}

