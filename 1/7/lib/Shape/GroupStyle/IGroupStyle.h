#pragma once

#include <cstdint>
#include <limits>
#include <memory>
#include "./../IStyle.h"

class IGroupStyle: public IStyle
{
public:
    virtual void InsertStyle(IStyle & style, size_t position = 0) = 0;
    virtual void RemoveStyleAtIndex(size_t index) = 0;
    virtual int GetStylesCount() = 0;
    virtual const IStyle & GetStyleAtIndex(size_t index) const = 0;

    virtual ~IGroupStyle() = default;
};
