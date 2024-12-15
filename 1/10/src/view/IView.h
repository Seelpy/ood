#pragma once

#include "canvas/ICanvas.h"
#include <memory>

class IView
{
public:
    virtual ~IView() = default;

    virtual void Show(ICanvas &) = 0;
};

typedef std::shared_ptr<IView> IViewPtr;