#pragma once

#include "Point.h"
#include "Size.h"
#include "stdexcept"

class Rect
{
public:
    Rect(Point leftTop, Size size)
    {
        Validate(leftTop, size);
        m_leftTop = leftTop;
        m_size = size;
    }

    Point LeftTop() {
        return m_leftTop;
    }

    Point LeftDown() {
        return {m_leftTop.X(), m_leftTop.Y() - m_size.GetHeight()};
    }

    Point RightTop() {
        return {m_leftTop.X() + m_size.GetWidth() , m_leftTop.Y()};
    }

    Point RightDown() {
        return {m_leftTop.X() + m_size.GetWidth() , m_leftTop.Y() - m_size.GetHeight()};
    }

    Size GetSize() {
        return m_size;
    }
private:
    static void Validate(Point leftTop, Size size) {
        if (leftTop.X() - size.GetWidth() < 0)
        {
            throw std::invalid_argument("invalid rectangle params");
        }

        if (leftTop.Y() - size.GetHeight() < 0)
        {
            throw std::invalid_argument("invalid rectangle params");
        }
    }

    Point m_leftTop;
    Size m_size;

};