//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_RECTANGLESTRATEGY_H
#define INC_1_1_RECTANGLESTRATEGY_H

#include "IShapeStrategy.h"
#include "sstream"
namespace shapes
{
    class RectangleStrategy : public IShapeStrategy
    {
    public:
        RectangleStrategy(shapes::Point leftTop, double width, double height)
                : m_leftTop(leftTop), m_width(width), m_height(height)
        {
            if (width < 0 || height < 0)
            {
                throw std::invalid_argument("Width and height must be non-negative");
            }
        }

        shapes::StrategyType GetType() override
        {
            return shapes::StrategyType::RECTANGLE;
        }

        std::string GetShapeInfo() override
        {
            std::ostringstream oss;
            oss << m_color << m_leftTop.x << " " << m_leftTop.y << " " << m_width << " " << m_height;
            return oss.str();
        }

        void Draw(ICanvas &canvas, const std::string &color) override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_leftTop.x, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y);
        }

        void Move(double dx, double dy) override
        {
            m_leftTop.x += dx;
            m_leftTop.y += dy;
        }

        std::unique_ptr<IShapeStrategy> Clone() const override
        {
            return std::make_unique<RectangleStrategy>(*this);
        }

    private:
        shapes::Point m_leftTop;
        double m_width, m_height;
        std::string m_color;
    };
}
#endif //INC_1_1_RECTANGLESTRATEGY_H
