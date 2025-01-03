#pragma once

#include <utility>
#include <boost/signals2.hpp>
#include "IShape.h"

// TODO: активная или пассивная

class Shape : public IShape
{
public:
    Shape(
            const ShapeType& type,
            const common::Rect &frame,
            ILineStylePtr lineStyle,
            IFillStylePtr fillStyle
    ) : m_frame(frame),
        m_type(type),
        m_lineStyle(std::move(lineStyle)),
        m_fillStyle(std::move(fillStyle))
    {
    }

    ShapeType GetType() override
    {
        return m_type;
    }

    common::Rect GetFrame() override
    {
        return m_frame;
    }

    void SetFrame(common::Rect frame) override
    {
        m_frame = frame;
        Notify();
    }

    IFillStylePtr GetFillStyle() override
    {
        return m_fillStyle;
    }

    void SetFillStyle(IFillStylePtr style) override
    {
        m_fillStyle = style;
        Notify();
    }

    ILineStylePtr GetLineStyle() override
    {
        return m_lineStyle;
    }

    void SetLineStyle(ILineStylePtr style) override
    {
        m_lineStyle = style;
        Notify();
    }

    // TODO: Отдвать коннекшен чтобы прекратить коннекшен
    void RegisterObserver(const std::function<void()>& observer) override
    {
        m_observer.connect(observer);
    }

private:
    void Notify()
    {
        m_observer();
    }

    ShapeType m_type;
    common::Rect m_frame;
    ILineStylePtr m_lineStyle;
    IFillStylePtr m_fillStyle;
    boost::signals2::signal<void()> m_observer;
};