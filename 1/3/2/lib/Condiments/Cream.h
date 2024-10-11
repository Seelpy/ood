#pragma once

#include "./../Condiment.h"

// Кокосовая стружка
class CCream : public CCondimentDecorator
{
public:
    CCream(IBeveragePtr && beverage)
            : CCondimentDecorator(move(beverage))
    {}

protected:
    double GetCondimentCost()const override
    {
        return 25;
    }
    std::string GetCondimentDescription()const override
    {
        return "Cream";
    }
};
