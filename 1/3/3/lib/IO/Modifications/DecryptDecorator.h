#pragma once

#include "CInputDataStreamDecorator.h"
#include "UtilsFunc.h"

class DecryptDecorator : public CInputDataStreamDecorator
{
public:
    DecryptDecorator(IInputStreamPtr &&stream, int key) : CInputDataStreamDecorator(std::move(stream)), m_table(GenerateReverseSubstitutionTable(key))
    {
    }

    uint8_t ReadByte() override
    {
        auto data = m_input->ReadByte();
        return m_table[data];
    }

    std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) override
    {
        std::streamsize bytesRead = m_input->ReadBlock(dstBuffer, size);
        auto byteData = static_cast<uint8_t*>(dstBuffer);

        for (std::streamsize i = 0; i < bytesRead; ++i) {
            byteData[i] = m_table[byteData[i]];
        }

        return bytesRead;
    }

private:
    SubstitutionTable m_table;
};