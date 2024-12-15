#pragma once

#include "./../../common/Color.h"
#include <memory>

class IFillStyle {
public:
    virtual ~IFillStyle() = default;
    virtual RGBAColor GetColor() = 0;
};

typedef std::shared_ptr<IFillStyle> IFillStylePtr;