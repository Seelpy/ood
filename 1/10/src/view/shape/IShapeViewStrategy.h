#pragma once

#include "./../canvas/ICanvas.h"
#include <memory>

class IShapeViewStrategy
{
public:
    virtual ~IShapeViewStrategy() = default;

    virtual void Show(ICanvas &canvas, Rect frame, RGBAColor fillColor, RGBAColor lineColor, unsigned lineThickness) = 0;
};

typedef std::shared_ptr<IShapeViewStrategy> IShapeViewStrategyPtr;