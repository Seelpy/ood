#pragma once

#include "IDraft.h"
#include <stdexcept>
#include <boost/signals2.hpp>

class Draft : public IDraft
{
public:
    Draft(const Rect &frame) : m_frame(frame)
    {
    }

    const std::vector<ConstIShapePtr> &ListShapes() override
    {
        static std::vector<ConstIShapePtr> shapes;
        shapes.reserve(m_shapes.size());
        for (const auto &shape: m_shapes)
        {
            shapes.push_back((shape));
        }
        return shapes;
    }

    void AddShape(const IShapePtr &shape) override
    {
        m_shapes.push_back(shape);
        Notify();
    }

    void RemoveShape(size_t index) override
    {
        if (index >= m_shapes.size())
        {
            throw std::invalid_argument("invalid index");
        }
        m_shapes.erase(m_shapes.begin() + index);
        Notify();
    }

    Rect GetFrame() override
    {
        return m_frame;
    }

    void RegisterObserver(const std::function<void()>& observer) override
    {
        m_observer.connect(observer);
    }

private:
    void Notify()
    {
        m_observer();
    }

    Rect m_frame;
    std::vector<IShapePtr> m_shapes;
    boost::signals2::signal<void()> m_observer;
};