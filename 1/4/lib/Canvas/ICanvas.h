#pragma once

#include <string>
#include "../Common/Color.h"
#include "../Common/Point.h"

namespace gfx
{
    class ICanvas
    {
    public:

        virtual void SetColor(Color color) = 0;

        virtual void DrawLine(Point from, Point to) = 0;

        virtual void DrawEllipse(Point center, double rx, double ry) = 0;

        virtual ~ICanvas() = default;
    };
}
