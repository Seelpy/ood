#pragma once

#include "./../IShapeViewStrategy.h"

class CircleViewStrategy : public IShapeViewStrategy
{
public:
    CircleViewStrategy() = default;

    void Show(ICanvas &canvas, common::Rect frame, common::RGBAColor fillColor, common::RGBAColor lineColor, unsigned lineThickness) override
    {
        canvas.SetFillColor(fillColor);
        canvas.FillEllipse(frame);

        canvas.SetLineColor(lineColor);

        canvas.SetLineThickness(lineThickness);

        canvas.DrawEllipse(frame);
    }

private:
};