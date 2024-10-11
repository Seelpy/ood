#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <stdexcept>
#include "../IOutputDataStream.h"

class CFileOutputStream : public IOutputDataStream {
private:
    std::ofstream outFile;

public:
    CFileOutputStream(const std::string& filename) {
        outFile.open(filename, std::ios::binary);
        if (!outFile.is_open()) {
            throw std::logic_error("Failed to open file: " + filename);
        }
    }

    void WriteByte(uint8_t data) override {
        outFile.put(static_cast<char>(data));
        if (outFile.fail()) {
            throw std::logic_error("Failed to write byte to file.");
        }
    }

    void WriteBlock(const void* srcData, std::streamsize size) override {
        outFile.write(static_cast<const char*>(srcData), size);
        if (outFile.fail()) {
            throw std::logic_error("Failed to write block to file.");
        }
    }

    // Close the file
    void Close() override {
        if (outFile.is_open()) {
            outFile.close();
        }
    }

    ~CFileOutputStream() override {
        Close();
    }
};