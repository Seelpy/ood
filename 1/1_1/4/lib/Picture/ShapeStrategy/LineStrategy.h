//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_LINESTRATEGY_H
#define INC_1_1_LINESTRATEGY_H

#include "IShapeStrategy.h"
#include "sstream"

class LineStrategy : public IShapeStrategy
{
public:
    LineStrategy(double x1, double y1, double x2, double y2)
    {
        m_x1 = x1;
        m_y1 = y1;
        m_x2 = x2;
        m_y2 = y2;
    }

    StrategyType GetType() override
    {
        return StrategyType::LINE;
    }

    std::string GetShapeInfo() override
    {
        std::ostringstream oss;
        oss << m_x1 << " " << m_y1 << " " << m_x2 << " " << m_y2;
        return oss.str();
    }

    void Draw(ICanvas &canvas, const std::string &color) override
    {
        canvas.SetColor(color);
        canvas.MoveTo(m_x1, m_y1);
        canvas.LineTo(m_x2, m_y2);
    }

    void Move(double dx, double dy) override
    {
        m_x1 += dx;
        m_x2 += dx;
        m_y1 += dy;
        m_y2 += dy;
    }

    [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
    {
        return std::make_unique<LineStrategy>(*this);
    }

private:
    double m_x1, m_y1;
    double m_x2, m_y2;
};

#endif //INC_1_1_LINESTRATEGY_H
