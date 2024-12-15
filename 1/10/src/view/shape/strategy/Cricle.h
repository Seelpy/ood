#pragma once

#include "./../IShapeViewStrategy.h"

class CircleViewStrategy : public IShapeViewStrategy
{
public:
    CircleViewStrategy() = default;

    void Show(ICanvas &canvas, Rect frame, RGBAColor fillColor, RGBAColor lineColor, unsigned lineThickness) override
    {
        canvas.SetFillColor(fillColor);
        canvas.FillEllipse(frame);

        canvas.SetLineColor(lineColor);

        canvas.SetLineThickness(lineThickness);

        canvas.DrawEllipse(frame);
    }

private:
};