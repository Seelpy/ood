//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_CIRCLESTRATEGY_H
#define INC_1_1_CIRCLESTRATEGY_H

#include "sstream"
#include "IShapeStrategy.h"

class CircleStrategy : public IShapeStrategy
{
public:
    CircleStrategy(double x, double y, double r)
    {
        m_r = r;
        m_x = x;
        m_y = y;
    }

    StrategyType GetType() override
    {
        return StrategyType::CIRCLE;
    }

    std::string GetShapeInfo() override
    {
        std::ostringstream oss;
        oss << m_x << " " << m_y << " " << m_r;
        return oss.str();
    }

    void Draw(ICanvas &canvas, const std::string &color) override
    {
        canvas.SetColor(color);
        canvas.DrawEllipse(m_x, m_y, m_r, m_r);
    }


    void Move(double dx, double dy) override
    {
        m_x += dx;
        m_y += dy;
    }

    [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
    {
        return std::make_unique<CircleStrategy>(*this);
    }

private:
    double m_r;
    double m_x, m_y;
};

#endif //INC_1_1_CIRCLESTRATEGY_H
