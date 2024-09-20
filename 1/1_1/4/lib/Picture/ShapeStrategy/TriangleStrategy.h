//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_TRIANGLESTRATEGY_H
#define INC_1_1_TRIANGLESTRATEGY_H

#include "IShapeStrategy.h"
#include "sstream"

namespace shapes
{
    class TriangleStrategy : public IShapeStrategy
    {
    public:
        TriangleStrategy(shapes::Point p1, shapes::Point p2, shapes::Point p3)
                : m_p1(p1), m_p2(p2), m_p3(p3)
        {}

        shapes::StrategyType GetType() override
        {
            return shapes::StrategyType::TRIANGLE;
        }

        std::string GetShapeInfo() override
        {
            std::ostringstream oss;
            oss << m_p1.x << " " << m_p1.y << " " << m_p2.x << " " << m_p2.y << " " << m_p3.x << " " << m_p3.y;
            return oss.str();
        }

        void Draw(ICanvas &canvas, const std::string &color) override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_p1.x, m_p1.y);
            canvas.LineTo(m_p2.x, m_p2.y);
            canvas.LineTo(m_p3.x, m_p3.y);
            canvas.LineTo(m_p1.x, m_p1.y);
        }

        void Move(double dx, double dy) override
        {
            m_p1.x += dx;
            m_p1.y += dy;
            m_p2.x += dx;
            m_p2.y += dy;
            m_p3.x += dx;
            m_p3.y += dy;
        }

        [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
        {
            return std::make_unique<TriangleStrategy>(*this);
        }

    private:
        shapes::Point m_p1, m_p2, m_p3;
    };
}
#endif //INC_1_1_TRIANGLESTRATEGY_H
