#pragma once

#include "./../Beverage.h"
#include <string>
#include "MilkshakePreset.h"

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
    CMilkshake(MilkShakeSizeType type)
            : CBeverage(MilkshakeNames().GetInfo(type) + " " + "Milkshake")
    {
        m_costsByType = MilkshakePreset();
        m_costsByType.Validate(type);
        m_type = type;
    }

    double GetCost() const override
    {
        return m_costsByType.GetInfo(m_type);
    }

private:
    MilkshakePreset m_costsByType;
    MilkShakeSizeType m_type;
};
