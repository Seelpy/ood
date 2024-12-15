#pragma once

#include "./../../common/Color.h"
#include <memory>

class IFillStyle {
public:
    virtual ~IFillStyle();
    virtual RGBAColor GetColor();
};

typedef std::shared_ptr<IFillStyle> IFillStylePtr;