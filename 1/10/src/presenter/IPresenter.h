#pragma once

#include "./../view/IView.h"

class IPresenter
{
    virtual IViewPtr GetView();
};