#pragma once

#include "./../BaseView.h"
#include <functional>
#include <optional>
#include "./../../model/style/fill/IFillStyle.h"
#include "./../../model/style/line/ILineStyle.h"
#include <string>

class ButtonView : public BaseView
{
public:
    ButtonView(common::Rect frame, const IFillStylePtr& fillStyle, const ILineStylePtr&  lineStyle, const std::string& text) : m_frame(frame), BaseView(frame)
    {
        m_text = text;
        m_lineStyle = lineStyle;
        m_fillStyle = fillStyle;
    }

    ~ButtonView() override = default;

    void Show(ICanvas &canvas) override
    {
        canvas.SetFillColor(m_fillStyle->GetColor());
        canvas.SetLineColor(m_lineStyle->GetColor());
        canvas.SetLineThickness(2);

        canvas.DrawClosedPolyLine({m_frame.LeftTop(),
                                   m_frame.RightTop(),
                                   m_frame.RightDown(),
                                   m_frame.LeftDown()});

        int textWidth = m_text.length() * 6;
        int textHeight = 16;
        common::Point textPosition(m_frame.LeftTop().X() + (m_frame.GetSize().GetWidth() - textWidth) / 2, m_frame.LeftTop().Y() + (m_frame.GetSize().GetHeight() - textHeight) / 2 );
        canvas.DrawText(m_text, textPosition);
    }
private:
    IFillStylePtr m_fillStyle;
    ILineStylePtr  m_lineStyle;
    common::Rect m_frame;
    std::string m_text;
};

