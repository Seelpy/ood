#pragma once

#include <utility>
#include "./../BaseView.h"
#include "./../IView.h"
#include "IShapeViewStrategy.h"

class ShapeView : public BaseView
{
public:
    ShapeView(
            IShapeViewStrategyPtr strategy, common::Rect frame, common::RGBAColor fillColor, common::RGBAColor lineColor,
            unsigned int thickness)
            : m_strategy(std::move(strategy)), m_frame(frame), BaseView(frame)
    {
        m_fillColor = fillColor;
        m_lineColor = lineColor;
        m_thickness = thickness;
    }

    ~ShapeView() override = default;

    void Show(ICanvas &canvas) override
    {
        m_strategy->Show(canvas, m_frame, m_fillColor, m_lineColor, m_thickness);
    }

    void SetFrame(const common::Rect &frame)
    {
        m_frame = frame;
    }

    void SetFillColor(const common::RGBAColor &fillColor)
    {
        m_fillColor = fillColor;
    }

    void SetLineColor(const common::RGBAColor &lineColor)
    {
        m_lineColor = lineColor;
    }

    void SetThickness(unsigned int thickness)
    {
        m_thickness = thickness;
    }

private:
    IShapeViewStrategyPtr m_strategy;
    common::Rect m_frame;
    common::RGBAColor m_fillColor;
    common::RGBAColor m_lineColor;
    unsigned int m_thickness;
};