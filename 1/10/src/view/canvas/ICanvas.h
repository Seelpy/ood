#pragma once

#include <vector>
#include "./../../model/common/Point.h"
#include "./../../model/common/Color.h"
#include "./../../model/common/Rect.h"

class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void DrawLine(const Point& from, const Point& to) = 0;
    virtual void DrawClosedPolyLine(const std::vector<Point>&) = 0;
    virtual void DrawEllipse(Rect) = 0;
    virtual void FillEllipse(Rect) = 0;
    virtual void FillPolygon(const std::vector<Point>&) = 0;
    virtual void SetFillColor(RGBAColor) = 0;
    virtual void SetLineColor(RGBAColor) = 0;
    virtual void SetLineThickness(unsigned int) = 0;
    virtual void DrawText(const std::string&, const Point& position) = 0;
};