#pragma once

#include "./../model/common/Rect.h"
#include <boost/signals2.hpp>
#include "./../model/common/Point.h"
#include <functional>
#include "IView.h"

class BaseView : public IView
{
public:
    explicit BaseView(Rect frame) : m_frame(frame)
    {
    }

    void OnMouseDown(const Point &p) override
    {
        if (In(p))
        {
            m_observerOnMouseDown(p);
            IterateByViews(
                    [p](const IViewPtr& view) {
                        view->OnMouseDown(p);
                    });
        }
    }

    void OnMouseUp(const Point &p) override
    {
        if (In(p))
        {
            m_observerOnMouseUp(p);
            IterateByViews(
                    [p](const IViewPtr& view) {
                        view->OnMouseUp(p);
                    });
        }
    }

    void OnMouseDrag(const Point &p1, const Point &p2) override
    {
        if (In(p1))
        {
            m_observerOnMouseDrag(p1, p2);
            IterateByViews(
                    [p1, p2](const IViewPtr& view) {
                        view->OnMouseDrag(p1, p2);
                    });
        }
    }

    void RegisterObserverOnMouseDown(std::function<void(const Point &)> &f) override
    {
        m_observerOnMouseDown.connect(f);
    }

    void RegisterObserverOnMouseUp(std::function<void(const Point &)> &f) override
    {
        m_observerOnMouseDown.connect(f);
    }

    void RegisterObserverOnMouseDrag(std::function<void(const Point &, const Point &)> &f) override
    {
        m_observerOnMouseDrag.connect(f);
    }

    bool In(const Point &p)
    {
        return m_frame.In(p);
    }

protected:
    virtual std::vector<IViewPtr> ListViewsImpl()
    {
        return {};
    }

private:

    void IterateByViews(const std::function<void(const IViewPtr&)>& f)
    {
        for (const auto& view: ListViewsImpl())
        {
            f(view);
        }
    }

    boost::signals2::signal<void(const Point &)> m_observerOnMouseDown;
    boost::signals2::signal<void(const Point &)> m_observerOnMouseUp;
    boost::signals2::signal<void(const Point &, const Point &)> m_observerOnMouseDrag;

    Rect m_frame;
};