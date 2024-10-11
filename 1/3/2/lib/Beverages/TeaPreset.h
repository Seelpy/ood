#pragma once

#include "../InfoByType.h"
#include <map>

enum TeaType
{
    GREEN,
    BLACK,
    WHITE,
    OOLANG,
};


class TeaPreset : public InfoByType<TeaType, double>
{
public:
    TeaPreset() : InfoByType<TeaType, double>(
            {{TeaType::GREEN,  30},
             {TeaType::BLACK,  30},
             {TeaType::WHITE,  30},
             {TeaType::OOLANG, 30}})
    {
    }
};

class TeaNames : public InfoByType<TeaType, std::string>
{
public:
    TeaNames() : InfoByType<TeaType, std::string>(
            {{TeaType::GREEN,  "Green"},
             {TeaType::BLACK,  "Black"},
             {TeaType::WHITE,  "White"},
             {TeaType::OOLANG, "Oolang"}})
    {
    }
};