#pragma once

#include "../InfoByType.h"
#include <map>

enum LiquorType
{
    NUTTY,
    CHOCOLATE
};

class LiquorCosts : public InfoByType<LiquorType, double>
{
public:
    LiquorCosts() : InfoByType<LiquorType, double>(
            {{LiquorType::NUTTY,  50},
             {LiquorType::CHOCOLATE, 50}})
    {
    }
};

class LiquorNames : public InfoByType<LiquorType, std::string>
{
public:
    LiquorNames() : InfoByType<LiquorType, std::string>(
            {{LiquorType::NUTTY,  "Green"},
             {LiquorType::CHOCOLATE, "Oolang"}})
    {
    }
};