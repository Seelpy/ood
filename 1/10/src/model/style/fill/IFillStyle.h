#pragma once

#include "./../../..//lib/common/Color.h"
#include <memory>

class IFillStyle {
public:
    virtual ~IFillStyle() = default;
    virtual common::RGBAColor GetColor() = 0;
};

typedef std::shared_ptr<IFillStyle> IFillStylePtr;