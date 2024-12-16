#pragma once

#include "./../view/IView.h"
#include "IPresenter.h"
#include <memory>
#include <iostream>

class BasePresenter : public IPresenter
{
public:
    BasePresenter() = default;

protected:
    void InitBase(const IViewPtr &view)
    {
        m_f1 = [this](auto && PH1) { HandleMouseDownImpl(std::forward<decltype(PH1)>(PH1)); };
        m_f2 = [this](auto && PH1) { HandleMouseUpImpl(std::forward<decltype(PH1)>(PH1)); };
        m_f3 = [this](auto && PH1, auto && PH2) { HandleMouseDragImpl(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2)); };

        view->RegisterObserverOnMouseDown(m_f1);
        view->RegisterObserverOnMouseUp(m_f2);
        view->RegisterObserverOnMouseDrag(m_f3);
    }

    virtual void HandleMouseDownImpl(const Point & p)
    {
        std::cout << "Down: " << p.X() << " " << p.Y() << std::endl;
    }

    virtual void HandleMouseUpImpl(const Point & p)
    {
        std::cout << "Up: " << p.X() << " " << p.Y() << std::endl;
    }

    virtual void HandleMouseDragImpl(const Point & p1, const Point & p2)
    {
        std::cout << "Mouse: " << p1.X() << " " << p1.Y() << " | " << p2.X() << " " << p2.Y()  << std::endl;
    }

private:
    std::function<void(const Point &, const Point &)> m_f3 = [this](const Point &p1, const Point &p2) { HandleMouseDragImpl(p1, p2); };
    std::function<void(const Point &)> m_f2 = [this](const Point &p) { HandleMouseUpImpl(p); };
    std::function<void(const Point &)> m_f1 = [this](const Point &p) { HandleMouseDownImpl(p); };
};