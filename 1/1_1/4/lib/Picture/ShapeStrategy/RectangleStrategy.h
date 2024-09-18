//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_RECTANGLESTRATEGY_H
#define INC_1_1_RECTANGLESTRATEGY_H

#include "IShapeStrategy.h"
#include "sstream"

class RectangleStrategy : public IShapeStrategy
{
public:
    RectangleStrategy(double left, double top, double width, double height)
            : m_left(left), m_top(top), m_width(width), m_height(height)
    {
        if (width < 0 || height < 0)
        {
            throw std::invalid_argument("Width and height must be non-negative");
        }
    }

    StrategyType GetType() override
    {
        return StrategyType::RECTANGLE;
    }

    std::string GetShapeInfo() override
    {
        std::ostringstream oss;
        oss << m_color << m_left << " " << m_top << " " << m_width << " " << m_height;
        return oss.str();
    }

    void Draw(ICanvas &canvas, const std::string &color) override
    {
        canvas.SetColor(color);
        canvas.MoveTo(m_left, m_top);
        canvas.LineTo(m_left + m_width, m_top);
        canvas.LineTo(m_left + m_width, m_top + m_height);
        canvas.LineTo(m_left, m_top + m_height);
        canvas.LineTo(m_left, m_top);
    }

    void Move(double dx, double dy) override
    {
        m_left += dx;
        m_top += dy;
    }

    [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
    {
        return std::make_unique<RectangleStrategy>(*this);
    }

private:
    double m_left, m_top, m_width, m_height;
    std::string m_color;
};

#endif //INC_1_1_RECTANGLESTRATEGY_H
