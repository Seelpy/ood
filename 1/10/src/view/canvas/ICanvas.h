#pragma once

#include <vector>
#include "./../../lib/common/Point.h"
#include "./../../lib/common/Color.h"
#include "./../../lib/common/Rect.h"
class ICanvas
{
public:
    virtual ~ICanvas() = default;

    virtual void DrawLine(const common::Point& from, const common::Point& to) = 0;
    virtual void DrawClosedPolyLine(const std::vector<common::Point>&) = 0;
    virtual void DrawEllipse(common::Rect) = 0;
    virtual void FillEllipse(common::Rect) = 0;
    virtual void FillPolygon(const std::vector<common::Point>&) = 0;
    virtual void SetFillColor(common::RGBAColor) = 0;
    virtual void SetLineColor(common::RGBAColor) = 0;
    virtual void SetLineThickness(unsigned int) = 0;
    virtual void DrawText(const std::string&, const common::Point& position) = 0;
};