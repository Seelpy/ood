#pragma once

namespace common {
    class Size
    {
    public:
        Size(unsigned int width = 0, unsigned height = 0)
        {
            m_width = width;
            m_height = height;
        }

        unsigned int GetWidth() const
        {
            return m_width;
        }

        unsigned int GetHeight() const
        {
            return m_height;
        }

    private:
        unsigned int m_width;
        unsigned int m_height;

    };
}
