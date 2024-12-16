#pragma once

#include "./../../model/shape/IShape.h"
#include "./../../view/shape/Shape.h"
#include "./../BasePresenter.h"
#include "ViewFactory.h"
#include <iostream>

class ShapePresenter : public BasePresenter
{
public:
    explicit ShapePresenter(const IShapePtr &shape): m_shape(ShapeViewFactory::CreateView(shape))
    {
        shape->RegisterObserver([=, *this]() {
            // TODO: add listen
        });
        InitBase(m_shape);
    }

    IViewPtr GetView() override
    {
        return m_shape;
    }

private:
    std::shared_ptr<ShapeView> m_shape;
};