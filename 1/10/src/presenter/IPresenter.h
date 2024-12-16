#pragma once

#include "./../view/IView.h"

class IPresenter
{
public:
    virtual ~IPresenter() = default;

    virtual IViewPtr GetView() = 0;
};

typedef std::shared_ptr<IPresenter> IPresenterPtr;