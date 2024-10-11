#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include "../IOutputDataStream.h"

// TODO : формативр

class CMemoryOutputStream : public IOutputDataStream
{
public:
    CMemoryOutputStream(std::vector<uint8_t> &data)
            : m_buffer(data)
    {
    }

    void WriteByte(uint8_t data) override
    {
        m_buffer.push_back(data);
    }

    void WriteBlock(const void *srcData, std::streamsize size) override
    {
        const uint8_t *byteData = static_cast<const uint8_t *>(srcData);
        m_buffer.insert(m_buffer.end(), byteData, byteData + size);
    }

    void Close() override
    {
    }

private:
    std::vector<uint8_t> &m_buffer;
};