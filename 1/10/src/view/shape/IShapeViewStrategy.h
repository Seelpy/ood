#pragma once

#include "./../canvas/ICanvas.h"
#include <memory>

class IShapeViewStrategy
{
public:
    virtual ~IShapeViewStrategy();

    virtual void Show(ICanvas &canvas, Rect frame, RGBAColor fillColor, RGBAColor lineColor, unsigned lineThickness);
};

typedef std::shared_ptr<IShapeViewStrategy> IShapeViewStrategyPtr;