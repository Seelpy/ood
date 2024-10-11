#pragma once

#include "COutputDataStreamDecorator.h"
#include "UtilsFunc.h"

class EncryptDecorator : public COutputDataStreamDecorator
{
public:
    EncryptDecorator(IOutputStreamPtr &&stream, int key) : COutputDataStreamDecorator(std::move(stream)), m_table(GenerateSubstitutionTable(key))
    {
    }

    void WriteByte(uint8_t data) override
    {
        m_output->WriteByte(m_table[data]);
    }

    void WriteBlock(const void *srcData, std::streamsize size) override
    {
        auto byteData = static_cast<const uint8_t *>(srcData);
        std::vector<uint8_t> encryptedData(size);

        for (std::streamsize i = 0; i < size; ++i)
        {
            encryptedData[i] = m_table[byteData[i]];
        }

        m_output->WriteBlock(encryptedData.data(), size);
    }

private:
    SubstitutionTable m_table;
};