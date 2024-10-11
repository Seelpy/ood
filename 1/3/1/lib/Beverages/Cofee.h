#pragma once

#include "./../Beverage.h"
#include <map>

// Кофе
class CCoffee : public CBeverage
{
public:
    CCoffee(const std::string& description = "Coffee")
            :CBeverage(description)
    {}

    double GetCost() const override
    {
        return 60;
    }
};