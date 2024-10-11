#pragma once

#include "./../Condiment.h"
#include <exception>

const unsigned MAX_CHOCOLATE_COUNT = 5;

// Лимонная добавка
class CChocolate : public CCondimentDecorator
{
public:
    CChocolate(IBeveragePtr &&beverage, unsigned quantity = 1)
            : CCondimentDecorator(std::move(beverage))
    {
        if (quantity > MAX_CHOCOLATE_COUNT)
        {
            throw std::invalid_argument("invalid chocolate count");
        }
        m_quantity = quantity;
    }

protected:
    double GetCondimentCost() const override
    {
        return 10.0 * m_quantity;
    }

    std::string GetCondimentDescription() const override
    {
        return "Chocolate x" + std::to_string(m_quantity);
    }

private:
    unsigned m_quantity;
};