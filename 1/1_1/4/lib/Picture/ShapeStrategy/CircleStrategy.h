//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_CIRCLESTRATEGY_H
#define INC_1_1_CIRCLESTRATEGY_H

#include "sstream"
#include "IShapeStrategy.h"
#include "./../Point.h"

// TODO: патерн прототип

namespace shapes
{
    class CircleStrategy : public IShapeStrategy
    {
    public:
        CircleStrategy(shapes::Point p, double r)
        {
            m_r = r;
            m_center = p;
        }

        shapes::StrategyType GetType() override
        {
            return shapes::StrategyType::CIRCLE;
        }

        std::string GetShapeInfo() override
        {
            std::ostringstream oss;
            oss << m_center.x << " " << m_center.y << " " << m_r;
            return oss.str();
        }

        void Draw(ICanvas &canvas, const std::string &color) override
        {
            canvas.SetColor(color);
            canvas.DrawEllipse(m_center.x, m_center.y, m_r, m_r);
        }


        void Move(double dx, double dy) override
        {
            m_center.x += dx;
            m_center.y += dy;
        }

        [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
        {
            return std::make_unique<CircleStrategy>(*this);
        }

    private:
        double m_r;
        shapes::Point m_center;
    };
}


#endif //INC_1_1_CIRCLESTRATEGY_H
