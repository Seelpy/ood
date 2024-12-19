#pragma once

#include "IFillStyle.h"

class FillStyle : public IFillStyle
{
public:
    FillStyle(common::RGBAColor color)
    {
        m_color = color;
    }

    common::RGBAColor GetColor() override
    {
        return m_color;
    }

private:
    common::RGBAColor m_color;
};