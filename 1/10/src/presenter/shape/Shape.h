#pragma once

#include "./../../model/shape/IShape.h"
#include "./../../view/shape/Shape.h"
#include "./../IPresenter.h"

class ShapePresenter : public IPresenter
{
public:
    ShapePresenter(const IShapePtr &shape)
    {

    }

    IViewPtr GetView() override
    {

    }
private:
    ShapeView shape;
};