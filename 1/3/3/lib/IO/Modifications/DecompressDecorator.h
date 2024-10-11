#pragma once

#include "CInputDataStreamDecorator.h"
#include "UtilsFunc.h"
#include "RLE.h"
#include <exception>

class DecompressDecorator : public CInputDataStreamDecorator
{
public:
    DecompressDecorator(IInputStreamPtr &&stream) : CInputDataStreamDecorator(std::move(stream))
    {
    }

    bool IsEOF() override
    {
        return m_input->IsEOF() && m_entry.count == 0;
    }

    uint8_t ReadByte() override
    {
        UpdateIfNeedEntry();
        if (m_entry.count > 0)
        {
            m_entry.count--;
            return m_entry.value;
        }

        throw std::logic_error("unexpected end of stream");
    }

    std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) override
    {
        auto byteData = static_cast<uint8_t *>(dstBuffer);
        std::streamsize totalBytesRead = 0;

        while (totalBytesRead < size)
        {
            UpdateIfNeedEntry();

            if (m_entry.count > 0)
            {
                byteData[totalBytesRead++] = m_entry.value;
                m_entry.count--;
            }
            else
            {
                break;
            }
        }

        return totalBytesRead;
    }

private:
    void UpdateIfNeedEntry()
    {
        if (!m_input->IsEOF() && m_entry.count == 0)
        {
            uint8_t buffer[2];
            auto count = m_input->ReadBlock(buffer, 2);
            if (count != 2)
            {
                throw std::logic_error("unexpected end of stream");
            }
            m_entry = RLEEntry{buffer[0], buffer[1]};
        }
    }

    RLEEntry m_entry{};
};