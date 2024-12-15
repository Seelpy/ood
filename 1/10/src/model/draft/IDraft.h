#pragma once

#include "./../shape/IShape.h"
#include <vector>

class IDraft
{
public:
    virtual ~IDraft();

    virtual const std::vector<ConstIShapePtr> &ListShapes();

    virtual void AddShape(const IShapePtr &shape);

    virtual void RemoveShape(size_t index);

    virtual Rect GetFrame();

    virtual void RegisterObserver(const std::function<void()>& observer);
};