//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_TRIANGLESTRATEGY_H
#define INC_1_1_TRIANGLESTRATEGY_H

#include "IShapeStrategy.h"
#include "sstream"

class TriangleStrategy : public IShapeStrategy
{
public:
    TriangleStrategy(double x1, double y1, double x2, double y2, double x3, double y3)
            : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_x3(x3), m_y3(y3)
    {}

    StrategyType GetType() override
    {
        return StrategyType::TRIANGLE;
    }

    std::string GetShapeInfo() override
    {
        std::ostringstream oss;
        oss << m_x1 << " " << m_y1 << " " << m_x2 << " " << m_y2 << " " << m_x3 << " " << m_y3;
        return oss.str();
    }

    void Draw(ICanvas &canvas, const std::string &color) override
    {
        canvas.SetColor(color);
        canvas.MoveTo(m_x1, m_y1);
        canvas.LineTo(m_x2, m_y2);
        canvas.LineTo(m_x3, m_y3);
        canvas.LineTo(m_x1, m_y1);
    }

    void Move(double dx, double dy) override
    {
        m_x1 += dx;
        m_y1 += dy;
        m_x2 += dx;
        m_y2 += dy;
        m_x3 += dx;
        m_y3 += dy;
    }

    [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
    {
        return std::make_unique<TriangleStrategy>(*this);
    }

private:
    double m_x1, m_y1, m_x2, m_y2, m_x3, m_y3;
};

#endif //INC_1_1_TRIANGLESTRATEGY_H
