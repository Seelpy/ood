#pragma once

#include "../InfoByType.h"

// TODO: STANDART
enum LatteSizeType
{
    STANDART,
    DOUBLE
};


class LattePreset : public InfoByType<LatteSizeType, double>
{
public:
    LattePreset() : InfoByType<LatteSizeType, double>(
            {{LatteSizeType::STANDART, 90},
             {LatteSizeType::DOUBLE, 130}})
    {
    }
};

class LatteNames : public InfoByType<LatteSizeType, std::string>
{
public:
    LatteNames() : InfoByType<LatteSizeType, std::string>(
            {{LatteSizeType::STANDART, "Standart"},
             {LatteSizeType::DOUBLE, "Double"}})
    {
    }
};