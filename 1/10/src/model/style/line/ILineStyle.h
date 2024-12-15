#pragma once

#include "./../../common/Color.h"
#include <memory>

class ILineStyle
{
public:
    virtual ~ILineStyle() = default;

    virtual RGBAColor GetColor() = 0;

    virtual unsigned int GetThickness() = 0;
};

typedef std::shared_ptr<ILineStyle> ILineStylePtr;