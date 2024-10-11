#pragma once

#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>

template <typename EnumType, typename InfoType>
class InfoByType
{
    static_assert(std::is_enum<EnumType>::value, "EnumType must be an enum type.");

public:
    InfoByType(std::map<EnumType, InfoType> infoByType)
    {
        if (infoByType.empty())
        {
            throw std::invalid_argument("there should be at least one type");
        }
        m_costByType = std::move(infoByType);
    }

    InfoType GetInfo(EnumType type) const
    {
        auto cost = m_costByType.find(type);
        if (cost != m_costByType.end())
        {
            return cost->second;
        }
        throw std::invalid_argument("invalid type");
    }

    void Validate(EnumType type) const
    {
        if (m_costByType.find(type) == m_costByType.end())
        {
            throw std::invalid_argument("invalid type");
        }
    }

private:
    std::map<EnumType, InfoType> m_costByType;
};