#pragma once

#include "./../canvas/ICanvas.h"
#include <memory>

class IShapeViewStrategy
{
public:
    virtual ~IShapeViewStrategy() = default;

    virtual void Show(ICanvas &canvas, common::Rect frame, common::RGBAColor fillColor, common::RGBAColor lineColor, unsigned lineThickness) = 0;
};

typedef std::shared_ptr<IShapeViewStrategy> IShapeViewStrategyPtr;