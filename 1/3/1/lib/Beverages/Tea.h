#pragma once

#include "./../Beverage.h"
#include "TeaPreset.h"
#include <string>

// Чай
class CTea : public CBeverage
{
public:
    CTea(TeaType type)
            :CBeverage(TeaNames().GetInfo(type) + " " + "Tea")
    {
        m_costsByType = TeaPreset();
        m_costsByType.Validate(type);
        m_type = type;
    }

    double GetCost() const override
    {
        return m_costsByType.GetInfo(m_type);
    }
private:

    TeaPreset m_costsByType;
    TeaType m_type;
};