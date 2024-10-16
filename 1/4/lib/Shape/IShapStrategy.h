#pragma once

#include "./../Canvas/ICanvas.h"
#include "memory"

namespace shapes
{
    class IShapeStrategy
    {
    public:
        virtual ~IShapeStrategy() = default;

        virtual void Draw(gfx::ICanvas &canvas) = 0;
    };

    typedef std::unique_ptr<IShapeStrategy> IShapeStrategyPtr;
}
