#pragma once

#include "./../IInputDataStream.h"

class CInputDataStreamDecorator : public IInputDataStream
{
public:
    bool IsEOF() override
    {
        return m_input->IsEOF();
    }

    uint8_t ReadByte() override
    {
        return m_input->ReadByte();
    }

    std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) override
    {
        return m_input->ReadBlock(dstBuffer, size);
    }

protected:
    CInputDataStreamDecorator(IInputStreamPtr && input): m_input(std::move(input))
    {
    }

    IInputStreamPtr m_input;
};