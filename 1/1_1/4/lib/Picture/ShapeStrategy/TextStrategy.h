//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_TEXTSTRATEGY_H
#define INC_1_1_TEXTSTRATEGY_H


#include "IShapeStrategy.h"
#include "sstream"
namespace shapes
{
    class TextStrategy : public IShapeStrategy
    {
    public:
        TextStrategy(shapes::Point leftTop, double fontSize, std::string text)
                : m_leftTop(leftTop), m_fontSize(fontSize), m_text(std::move(text))
        {
            if (fontSize < 0)
            {
                throw std::invalid_argument("Font size must be non-negative");
            }
        }

        shapes::StrategyType GetType() override
        {
            return shapes::StrategyType::TEXT;
        }

        std::string GetShapeInfo() override
        {
            std::ostringstream oss;
            oss << m_leftTop.x << " " << m_leftTop.y << " " << m_fontSize << " " << m_text;
            return oss.str();
        }

        void Draw(ICanvas &canvas, const std::string &color) override
        {
            canvas.SetColor(color);
            canvas.DrawText(m_leftTop.x, m_leftTop.y, m_fontSize, m_text);
        }


        void Move(double dx, double dy) override
        {
            m_leftTop.x += dx;
            m_leftTop.y += dy;
        }

        [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
        {
            return std::make_unique<TextStrategy>(*this);
        }

    private:
        double m_fontSize;
        shapes::Point m_leftTop;
        std::string m_text;
    };
}
#endif //INC_1_1_TEXTSTRATEGY_H
