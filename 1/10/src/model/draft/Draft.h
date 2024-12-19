#pragma once

#include "IDraft.h"
#include <stdexcept>
#include <boost/signals2.hpp>

class Draft : public IDraft
{
public:
    Draft(const common::Size &size) : m_size(size)
    {
    }

    const std::vector<IShapePtr> &ListShapes() override
    {
        return m_shapes;
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

    common::Size GetSize() override
    {
        return m_size;
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

    common::Size m_size;
    std::vector<IShapePtr> m_shapes;
    boost::signals2::signal<void()> m_observer;
};