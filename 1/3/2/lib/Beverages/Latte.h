#pragma once

#include "Cofee.h"
#include "../InfoByType.h"
#include "LattePreset.h"
#include <string>

// Латте
class CLatte : public CCoffee
{
public:
    CLatte(LatteSizeType type =  STANDART)
            : CCoffee(LatteNames().GetInfo(type) + " " + "Latte")
    {
        m_costsByType = LattePreset();
        m_costsByType.Validate(type);
        m_type = type;
    }

    double GetCost() const override
    {
        return m_costsByType.GetInfo(m_type);
    }

private:
    LattePreset m_costsByType;
    LatteSizeType m_type;
};
