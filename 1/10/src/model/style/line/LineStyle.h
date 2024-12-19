#pragma once

#include "ILineStyle.h"

class LineStyle : public ILineStyle
{
public:
    LineStyle(common::RGBAColor color, unsigned int thickness)
    {
        m_color = color;
        m_thickness = thickness;
    }

    common::RGBAColor GetColor() override
    {
        return m_color;
    }

    unsigned int GetThickness() override
    {
        return m_thickness;
    }

private:
    common::RGBAColor m_color;
    unsigned int m_thickness;
};