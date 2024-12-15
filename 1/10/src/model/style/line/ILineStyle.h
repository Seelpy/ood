#pragma once

#include "./../../common/Color.h"
#include <memory>

class ILineStyle {
public:
    ~ILineStyle();
    virtual RGBAColor GetColor();
    virtual unsigned int GetThickness();
};

typedef std::shared_ptr<ILineStyle> ILineStylePtr;