#pragma once

#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iostream>

std::string GetFileExtension(const std::string& path) {
    size_t dotPosition = path.rfind('.');
    if (dotPosition != std::string::npos && dotPosition != path.size() - 1) {
        return path.substr(dotPosition + 1);
    }
    return "";
}


std::string GenerateRandomFilename(const std::string& extension) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    std::stringstream ss;
    ss << "file_"
       << (localTime->tm_year + 1900) << "_"
       << (localTime->tm_mon + 1) << "_"
       << localTime->tm_mday << "_"
       << localTime->tm_hour << "_"
       << localTime->tm_min << "_"
       << localTime->tm_sec << "_"
       << (std::rand() % 10000) << "."
       << extension;

    return ss.str();
}

void CopyFileFromPaths(const std::string& from, const std::string& to)
{
    std::ifstream src(from, std::ios::binary);
    std::ofstream dest(to, std::ios::binary);

    if (!src) {
        std::cerr << "Error opening source file: " << from << std::endl;
        return;
    }

    if (!dest) {
        std::cerr << "Error opening destination file: " << to << std::endl;
        return;
    }

    char buffer[1024];
    while (src.read(buffer, sizeof(buffer))) {
        dest.write(buffer, src.gcount());
    }
    dest.write(buffer, src.gcount());

    src.close();
    dest.close();
}

std::string CopyFile(const std::string& path, const std::string& dir)
{
    auto extension = GetFileExtension(path);
    auto newPath = dir + GenerateRandomFilename(extension);
    CopyFileFromPaths(path, newPath);
    return newPath;
}