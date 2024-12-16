#pragma once

#include "canvas/ICanvas.h"
#include <memory>

class IView
{
public:
    virtual ~IView() = default;

    virtual void Show(ICanvas &) = 0;

    virtual void RegisterObserverOnMouseDown(std::function<void(const Point &)> &f) = 0;

    virtual void RegisterObserverOnMouseUp(std::function<void(const Point &)> &f) = 0;

    virtual void RegisterObserverOnMouseDrag(std::function<void(const Point &, const Point &)> &f) = 0;

    virtual void OnMouseDown(const Point & p) = 0;

    virtual void OnMouseUp(const Point & p) = 0;

    virtual void OnMouseDrag(const Point & p1, const Point & p2) = 0;
};

typedef std::shared_ptr<IView> IViewPtr;