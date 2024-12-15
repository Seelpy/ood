#pragma once

class Point
{
public:
    Point(unsigned int x = 0, unsigned int y = 0)
    {
        m_x = x;
        m_y = y;
    }

    unsigned int X() const
    {
        return m_x;
    }

    unsigned int Y() const
    {
        return m_y;
    }

private:
    unsigned int m_x;
    unsigned int m_y;
};