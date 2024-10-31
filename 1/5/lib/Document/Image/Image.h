#pragma once

#include "IImage.h"

const int MAX_SIZE = 10000;
const int MIN_SIZE = 1;

class Image : public IImage
{
public:
    Image(std::string &path, int width, int height)
            : m_path(std::move(path)), m_width(width), m_height(height)
    {
        validateSize(width);
        validateSize(height);
        m_width = width;
        m_height = height;
    }

    [[nodiscard]] std::string GetPath() const override
    {
        return m_path;
    }

    [[nodiscard]] int GetWidth() const override
    {
        return m_width;
    }

    [[nodiscard]] int GetHeight() const override
    {
        return m_height;
    }

    void Resize(int width, int height) override
    {
        m_width = width;
        m_height = height;
    }

private:
    void validateSize(int s)
    {
        if (s >= MIN_SIZE && s <= MAX_SIZE)
        {
            return;
        }
        throw std::invalid_argument("invalid size");
    }

    std::string m_path;
    int m_width;
    int m_height;
};