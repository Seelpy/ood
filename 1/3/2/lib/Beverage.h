#pragma once

#include <utility>

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
    CBeverage(std::string description)
            : m_description(std::move(description))
    {}

    std::string GetDescription() const override final
    {
        return m_description;
    }

private:
    std::string m_description;
};
