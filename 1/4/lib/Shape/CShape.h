#pragma once

#include "IShapStrategy.h"
#include "./../Common/Color.h"

namespace shapes
{
    class CShape
    {
    public:
        CShape(Color color, IShapeStrategyPtr strategy) : m_strategy(std::move(strategy)), m_color(color)
        {
        }

        void Draw(gfx::ICanvas &canvas)
        {
            canvas.SetColor(m_color);
            m_strategy->Draw(canvas);
        }

    private:
        IShapeStrategyPtr m_strategy;
        Color m_color;
    };

    typedef std::unique_ptr<CShape> CShapePtr;
}
