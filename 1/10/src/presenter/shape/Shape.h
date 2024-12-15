#pragma once

#include "./../../model/shape/IShape.h"
#include "./../../view/shape/Shape.h"
#include "./../IPresenter.h"
#include "ViewFactory.h"

class ShapePresenter : public IPresenter
{
public:
    ShapePresenter(const IShapePtr &shape): m_shape(ShapeViewFactory::CreateView(shape))
    {
        shape->RegisterObserver([=, *this]() {
            // TODO: add listen
        });
    }

    IViewPtr GetView() override
    {
        return m_shape;
    }
private:
    std::shared_ptr<ShapeView> m_shape;
};