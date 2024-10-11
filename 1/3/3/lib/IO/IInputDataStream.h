#pragma once

#include <cstdint>
#include <ios>

class IInputDataStream
{
public:
    virtual bool IsEOF() = 0;

    virtual uint8_t ReadByte() = 0;

    virtual std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) = 0;

    virtual ~IInputDataStream() = default;
};

typedef std::unique_ptr<IInputDataStream> IInputStreamPtr;