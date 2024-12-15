#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include "./image/image.h"

class ImageLoader
{
public:
    static Image LoadImageFromString(const std::string& pixels)
    {
        std::istringstream s(pixels);
        Size size{};
        std::string line;
        while (std::getline(s, line))
        {
            size.width = std::max(size.width, static_cast<unsigned int>(line.length()));
            ++size.height;
        }

        Image img(size);

        s = std::istringstream(pixels);
        for (int y = 0; y < size.height; ++y)
        {
            if (!std::getline(s, line))
            {
                break;
            }

            int x = 0;
            for (char ch : line)
            {
                img.SetPixel({ x++, y }, ch);
            }
        }

        return img;
    }

    static void SaveImageToPPM(const Image& image, const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open the file for writing");
        }

        file << "P3\n";
        file << image.GetSize().width << " " << image.GetSize().height << "\n";
        file << "255\n";

        for (int y = 0; y < image.GetSize().height; ++y)
        {
            for (int x = 0; x < image.GetSize().width; ++x)
            {
                uint32_t color = image.GetPixel({x, y});

                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;

                file << static_cast<int>(r) << " "
                     << static_cast<int>(g) << " "
                     << static_cast<int>(b) << " ";
            }
            file << "\n";
        }

        file.close();
    }


};