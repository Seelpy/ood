#pragma once

#include "COutputDataStreamDecorator.h"
#include "UtilsFunc.h"
#include "RLE.h"
#include <optional>

class CompressDecorator : public COutputDataStreamDecorator
{
public:
    CompressDecorator(IOutputStreamPtr &&output): COutputDataStreamDecorator(std::move(output))
    {
    }

    void WriteByte(uint8_t data) override
    {
        auto entry = AddToRLEEntryOrNew(m_entry, data);
        if (entry != std::nullopt)
        {
            WriteRLEEntry(entry.value());
        }
    }

    void WriteBlock(const void *srcData, std::streamsize size) override
    {
        auto byteData = static_cast<const uint8_t *>(srcData);
        std::vector<uint8_t> toWrite;

        for (std::streamsize i = 0; i < size; ++i)
        {
            auto entry = AddToRLEEntryOrNew(m_entry, byteData[i]);
            if (entry != std::nullopt)
            {
                toWrite.push_back(entry->count);
                toWrite.push_back(entry->value);
                m_entry.count = 0;
            }
        }

        m_output->WriteBlock(toWrite.data(), size);
    }

    void Close() override
    {
        if (m_entry.count != 0)
        {
            WriteRLEEntry(m_entry);
        }
        m_output->Close();
    }

private:
    static std::optional<RLEEntry> AddToRLEEntryOrNew(RLEEntry &entry, uint8_t data)
    {
        auto copy = entry;
        if (entry.count == 0)
        {
            entry.value = data;
        }

        if (entry.value == data && entry.count < 255)
        {
            entry.count++;
        }
        else
        {
            entry.count = 1;
            entry.value = data;
            return copy;
        }

        return std::nullopt;
    }

    void WriteRLEEntry(RLEEntry entry)
    {
        m_output->WriteByte(entry.count);
        m_output->WriteByte(entry.value);
    }

    RLEEntry m_entry{};
};