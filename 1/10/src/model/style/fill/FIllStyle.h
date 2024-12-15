#pragma once

#include "IFillStyle.h"

class FillStyle : public IFillStyle
{
public:
    FillStyle(RGBAColor color)
    {
        m_color = color;
    }

    RGBAColor GetColor() override
    {
        return m_color;
    }

private:
    RGBAColor m_color;
};