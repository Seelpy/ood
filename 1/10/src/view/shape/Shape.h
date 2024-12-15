#pragma once

#include <utility>

#include "./../IView.h"
#include "IShapeViewStrategy.h"

class ShapeView : public IView
{
public:
    ShapeView(IShapeViewStrategyPtr strategy, Rect frame, RGBAColor fillColor, RGBAColor lineColor, unsigned int thickness)
            : m_strategy(std::move(strategy)), m_frame(frame)
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

    void SetFrame(const Rect& frame)
    {
        m_frame = frame;
    }

    void SetFillColor(const RGBAColor& fillColor)
    {
        m_fillColor = fillColor;
    }

    void SetLineColor(const RGBAColor& lineColor)
    {
        m_lineColor = lineColor;
    }

    void SetThickness(unsigned int thickness)
    {
        m_thickness = thickness;
    }

private:
    IShapeViewStrategyPtr m_strategy;
    Rect m_frame;
    RGBAColor m_fillColor;
    RGBAColor m_lineColor;
    unsigned int m_thickness;
};