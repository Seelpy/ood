#pragma once

#include "./../Condiment.h"
#include "LiquorPreset.h"
#include <exception>
#include <string>

// Лимонная добавка
class CLiquor : public CCondimentDecorator
{
public:
    CLiquor(IBeveragePtr &&beverage, LiquorType type)
            : CCondimentDecorator(std::move(beverage))
    {
        m_costsByType = LiquorCosts();
        m_namesByType = LiquorNames();
        m_costsByType.Validate(type);
        m_namesByType.Validate(type);
        m_type = type;
    }

protected:
    double GetCondimentCost() const override
    {
        return m_costsByType.GetInfo(m_type);
    }

    std::string GetCondimentDescription() const override
    {
        return  m_namesByType.GetInfo(m_type) + " " + "Chocolate";
    }

private:
    LiquorCosts m_costsByType;
    LiquorNames m_namesByType;
    LiquorType m_type;
};