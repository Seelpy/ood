#pragma once

#include "../InfoByType.h"
#include <map>

enum MilkShakeSizeType
{
    SMALL,
    MEDIUM,
    BIG
};


class MilkshakePreset : public InfoByType<MilkShakeSizeType, double>
{
public:
    MilkshakePreset() : InfoByType<MilkShakeSizeType, double>(
            {{MilkShakeSizeType::SMALL, 50},
             {MilkShakeSizeType::MEDIUM, 60},
             {MilkShakeSizeType::BIG, 80}})
    {
    }
};

class MilkshakeNames : public InfoByType<MilkShakeSizeType, std::string>
{
public:
    MilkshakeNames() : InfoByType<MilkShakeSizeType, std::string>(
            {{MilkShakeSizeType::SMALL, "Small"},
             {MilkShakeSizeType::MEDIUM, "Medium"},
             {MilkShakeSizeType::BIG, "Big"}})
    {
    }
};