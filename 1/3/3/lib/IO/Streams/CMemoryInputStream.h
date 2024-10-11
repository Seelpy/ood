#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include "../IInputDataStream.h"
#include <vector>

class CMemoryInputStream : public IInputDataStream
{
public:
    CMemoryInputStream(const std::vector<uint8_t> &data)
            : m_buffer(data)
    {}

    // Check if EOF is reached
    bool IsEOF() override
    {
        return currentPosition >= m_buffer.size();
    }

    // Read a single byte from the vector
    uint8_t ReadByte() override
    {
        if (IsEOF())
        {
            throw std::runtime_error("End of stream reached while reading byte.");
        }
        return m_buffer[currentPosition++];
    }

    std::streamsize ReadBlock(void *dstm_buffer, std::streamsize size) override
    {
        if (IsEOF())
        {
            return 0;
        }

        std::streamsize bytesToRead = std::min(size, static_cast<std::streamsize>(m_buffer.size() - currentPosition));
        std::memcpy(dstm_buffer, m_buffer.data() + currentPosition, bytesToRead);
        currentPosition += bytesToRead;

        return bytesToRead;
    }

private:
    const std::vector<uint8_t> &m_buffer;
    std::size_t currentPosition = 0;
};
