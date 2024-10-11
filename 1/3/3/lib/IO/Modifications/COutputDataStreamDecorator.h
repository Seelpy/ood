#pragma once

#include "./../IOutputDataStream.h"

class COutputDataStreamDecorator : public IOutputDataStream
{
public:
    void WriteByte(uint8_t data)
    {
        m_output->WriteByte(data);
    }

    void WriteBlock(const void *srcData, std::streamsize size)
    {
        m_output->WriteBlock(srcData, size);
    }

    void Close()
    {
        m_output->Close();
    }

protected:
    COutputDataStreamDecorator(IOutputStreamPtr &&output): m_output(std::move(output))
    {
    }

    IOutputStreamPtr m_output;
};