#pragma once

#include <vector>
#include "./../../Shape/CShape.h"

class CPictureDraft
{
public:
    typedef std::vector<shapes::CShapePtr> Draft;

    explicit CPictureDraft(std::vector<shapes::CShapePtr> &&shapes) : m_shapes(std::move(shapes))
    {
    }

    Draft::iterator begin() {
        return m_shapes.begin();
    }

    Draft::iterator end() {
        return m_shapes.end();
    }

    Draft::const_iterator begin() const {
        return m_shapes.begin();
    }

    Draft::const_iterator end() const {
        return m_shapes.end();
    }

private:
    std::vector<shapes::CShapePtr> m_shapes;
};