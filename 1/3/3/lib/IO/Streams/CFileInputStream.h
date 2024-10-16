#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include "../IInputDataStream.h"

class CFileInputStream : public IInputDataStream
{
public:
    CFileInputStream(const std::string &filename)
    {
        inFile.open(filename, std::ios::binary);
        if (!inFile.is_open())
        {
            throw std::logic_error("Failed to open file: " + filename);
        }
    }

    bool IsEOF() override
    {
        char c;
        if(!inFile.get(c))
        {
            return true;
        }
        inFile.unget();
        return inFile.eof(); //TODO unget
    }

    uint8_t ReadByte() override
    {
        char byte;
        if (!inFile.get(byte))
        {
            throw std::logic_error("Failed to read byte from file.");
        }
        return static_cast<uint8_t>(byte);
    }

    std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) override
    {
        inFile.read(static_cast<char *>(dstBuffer), size);
        if (inFile.fail() && !inFile.eof())
        {
            throw std::logic_error("Failed to read block from file.");
        }
        return inFile.gcount();
    }

    ~CFileInputStream() override
    {
        if (inFile.is_open())
        {
            inFile.close();
        }
    }
private:
    std::ifstream inFile;
};
