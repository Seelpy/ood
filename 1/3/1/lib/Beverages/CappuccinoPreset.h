#pragma once
// TODO: схема
#include "../InfoByType.h"
#include "Cappucciono.h"
#include <map>
#include <string>

enum CappuccinoSizeType
{
    STANDART,
    DOUBLE
};


class CappuccinoPreset : public InfoByType<CappuccinoSizeType, double>
{
public:
    CappuccinoPreset() : InfoByType<CappuccinoSizeType, double>(
            {{CappuccinoSizeType::STANDART, 80},
             {CappuccinoSizeType::DOUBLE, 120}})
    {
    }
};

class CappuccinoNames : public InfoByType<CappuccinoSizeType, std::string>
{
public:
    CappuccinoNames() : InfoByType<CappuccinoSizeType, std::string>(
            {{CappuccinoSizeType::STANDART, "Standart"},
             {CappuccinoSizeType::DOUBLE, "Double"}})
    {
    }
};