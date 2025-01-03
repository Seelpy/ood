#pragma once

#include "./../../model/shape/IShape.h"
#include "./../../view/shape/Shape.h"
#include "./../../view/shape/strategy/Cricle.h"

class ShapeViewFactory
{
public:
    static std::shared_ptr<ShapeView> CreateView(const IShapePtr &shape)
    {
        return std::make_shared<ShapeView>(
                CreateStrategy(shape),
                shape->GetFrame(),
                shape->GetFillStyle()->GetColor(),
                shape->GetLineStyle()->GetColor(),
                shape->GetLineStyle()->GetThickness()
        );
    }

private:
    static IShapeViewStrategyPtr CreateStrategy(const IShapePtr &shape)
    {
        if (shape->GetType() == "circle")
        {
            return std::make_shared<CircleViewStrategy>();
        }
        if (shape->GetType() == "rectangle")
        {
            return nullptr;
        }
        if (shape->GetType() == "triangle")
        {
            return nullptr;
        }
        return nullptr;
    }
};