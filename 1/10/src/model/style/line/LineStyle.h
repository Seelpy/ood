#pragma once

#include "ILineStyle.h"

class LineStyle : public ILineStyle
{
public:
    LineStyle(RGBAColor color, unsigned int thickness)
    {
        m_color = color;
        m_thickness = thickness;
    }

    RGBAColor GetColor() override
    {
        return m_color;
    }

    unsigned int GetThickness() override
    {
        return m_thickness;
    }

private:
    RGBAColor m_color;
    unsigned int m_thickness;
};