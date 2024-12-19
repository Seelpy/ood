#pragma once

#include "./../shape/IShape.h"
#include <vector>

class IDraft
{
public:
    virtual ~IDraft() = default;

    virtual const std::vector<IShapePtr> &ListShapes() = 0;

    virtual void AddShape(const IShapePtr &shape) = 0;

    virtual void RemoveShape(size_t index) = 0;

    virtual common::Size GetSize() = 0;

    virtual void RegisterObserver(const std::function<void()>& observer) = 0;
};

typedef std::shared_ptr<IDraft> IDraftPtr;