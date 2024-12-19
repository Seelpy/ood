#pragma once

#include "canvas/ICanvas.h"
#include <memory>

class IView
{
public:
    virtual ~IView() = default;

    virtual void Show(ICanvas &) = 0;

    virtual void RegisterObserverOnMouseDown(std::function<void(const common::Point &)> &f) = 0;

    virtual void RegisterObserverOnMouseUp(std::function<void(const common::Point &)> &f) = 0;

    virtual void RegisterObserverOnMouseDrag(std::function<void(const common::Point&, const common::Point &)> &f) = 0;

    virtual void OnMouseDown(const common::Point & p) = 0;

    virtual void OnMouseUp(const common::Point & p) = 0;

    virtual void OnMouseDrag(const common::Point & p1, const common::Point & p2) = 0;

    virtual common::Rect GetFrame() = 0;
};

typedef std::shared_ptr<IView> IViewPtr;