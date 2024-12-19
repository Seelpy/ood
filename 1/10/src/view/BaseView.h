#pragma once

#include "./../lib/common/Rect.h"
#include <boost/signals2.hpp>
#include "./../lib/common/Point.h"
#include <functional>
#include "IView.h"

class BaseView : public IView
{
public:
    explicit BaseView(common::Rect frame) : m_frame(frame)
    {
    }

    void OnMouseDown(const common::Point &p) override
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

    void OnMouseUp(const common::Point &p) override // TODO: если поташим то может up не у той фигуры поставиться
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

    void OnMouseDrag(const common::Point &p1, const common::Point &p2) override
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

    void RegisterObserverOnMouseDown(std::function<void(const common::Point &)> &f) override
    {
        m_observerOnMouseDown.connect(f);
    }

    void RegisterObserverOnMouseUp(std::function<void(const common::Point &)> &f) override
    {
        m_observerOnMouseDown.connect(f);
    }

    void RegisterObserverOnMouseDrag(std::function<void(const common::Point &, const common::Point &)> &f) override
    {
        m_observerOnMouseDrag.connect(f);
    }

    bool In(const common::Point &p)
    {
        return GetFrame().In(p);
    }

    common::Rect GetFrame() override
    {
        return m_frame;
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

    boost::signals2::signal<void(const common::Point &)> m_observerOnMouseDown;
    boost::signals2::signal<void(const common::Point &)> m_observerOnMouseUp;
    boost::signals2::signal<void(const common::Point &, const common::Point &)> m_observerOnMouseDrag;

    common::Rect m_frame;
};