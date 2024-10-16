#pragma once

#include "./../IShapStrategy.h"

namespace shapes
{
    class CRegularPolygonStrategy : public IShapeStrategy
    {
    public:
        CRegularPolygonStrategy(Point c, unsigned int vertexCount, double r): m_c(c)
        {
            m_vertexCount = vertexCount;
            m_r = r;
        }

        void Draw(gfx::ICanvas &canvas) override
        {
            double angleStep = 2 * M_PI / m_vertexCount;

            for (int i = 1; i <= m_vertexCount + 1; ++i)
            {
                double angle = i * angleStep;
                double prevAngle = (i - 1) * angleStep;
                canvas.DrawLine(CalculatePoint(prevAngle), CalculatePoint(angle));
            }
        }

    private:
        Point CalculatePoint(double angle) const
        {
            return {m_c.x + m_r * std::cos(angle), m_c.y + m_r * std::sin(angle)};
        }

        Point m_c;
        unsigned int m_vertexCount;
        double m_r;
    };
}

