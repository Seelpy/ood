//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_TEXTSTRATEGY_H
#define INC_1_1_TEXTSTRATEGY_H


#include "IShapeStrategy.h"
#include "sstream"

class TextStrategy : public IShapeStrategy
{
public:
    TextStrategy(double left, double top, double fontSize, std::string  text)
            : m_left(left), m_top(top), m_fontSize(fontSize), m_text(std::move(text))
    {
        if (fontSize < 0)
        {
            throw std::invalid_argument("Font size must be non-negative");
        }
    }

    StrategyType GetType() override
    {
        return StrategyType::TEXT;
    }

    std::string GetShapeInfo() override
    {
        std::ostringstream oss;
        oss << m_left << " " << m_top << " " << m_fontSize << " " << m_text;
        return oss.str();
    }

    void Draw(ICanvas &canvas, const std::string &color) override
    {
        canvas.SetColor(color);
        canvas.DrawText(m_left, m_top, m_fontSize, m_text);
    }


    void Move(double dx, double dy) override
    {
        m_left += dx;
        m_top += dy;
    }

    [[nodiscard]] std::unique_ptr<IShapeStrategy> Clone() const override
    {
        return std::make_unique<TextStrategy>(*this);
    }

private:
    double m_left, m_top, m_fontSize;
    std::string m_text;
};

#endif //INC_1_1_TEXTSTRATEGY_H
