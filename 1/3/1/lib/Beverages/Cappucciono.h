#pragma once

#include "Cofee.h"
#include "CappuccinoPreset.h"
#include <string>


// Капуччино
class CCappuccino : public CCoffee
{
public:
    CCappuccino(CappuccinoSizeType type = STANDART)
            : CCoffee(CappuccinoNames().GetInfo(type) + " " + "Cappuccino")
    {
        m_costsByType = CappuccinoPreset();
        m_costsByType.Validate(type);
        m_type = type;
    }

    double GetCost() const override
    {
        return m_costsByType.GetInfo(m_type);
    }

private:
    CappuccinoPreset m_costsByType;
    CappuccinoSizeType m_type;
};