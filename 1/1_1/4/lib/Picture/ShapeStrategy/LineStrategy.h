//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_LINESTRATEGY_H
#define INC_1_1_LINESTRATEGY_H

#include "IShapeStrategy.h"
#include "sstream"

namespace shapes
{
    class LineStrategy : public IShapeStrategy
    {
    public:
        LineStrategy(shapes::Point p1, shapes::Point p2)
        {
            m_p1 = p1;
            m_p2 = p2;
        }

        shapes::StrategyType GetType() override
        {
            return shapes::StrategyType::LINE;
        }

        std::string GetShapeInfo() override
        {
            std::ostringstream oss;
            oss << m_p1.x << " " << m_p1.y << " " << m_p2.x << " " << m_p2.y;
            return oss.str();
        }

        void Draw(ICanvas &canvas, const std::string &color) override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_p1.x, m_p1.y);
            canvas.LineTo(m_p2.x, m_p2.y);
        }

        void Move(double dx, double dy) override
        {
            m_p1.x += dx;
            m_p2.x += dx;
            m_p1.y += dy;
            m_p2.y += dy;
        }

        [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
        {
            return std::make_unique<LineStrategy>(*this);
        }

    private:
        shapes::Point m_p1{}, m_p2{};
    };
}
#endif //INC_1_1_LINESTRATEGY_H
