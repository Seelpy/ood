#pragma once

#include "./../Condiment.h"

enum class IceCubeType
{
    Dry,	// Сухой лед (для суровых сибирских мужиков)
    Water	// Обычные кубики из воды
};

// Добавка "Кубики льда". Определяется типом и количеством кубиков, что влияет на стоимость
// и описание
class CIceCubes : public CCondimentDecorator
{
public:
    CIceCubes(IBeveragePtr && beverage, unsigned quantity, IceCubeType type = IceCubeType::Water)
            : CCondimentDecorator(move(beverage))
            , m_quantity(quantity)
            , m_type(type)
    {}
protected:
    double GetCondimentCost()const override
    {
        // Чем больше кубиков, тем больше стоимость.
        // Сухой лед стоит дороже
        return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
    }
    std::string GetCondimentDescription()const override
    {
        return std::string(m_type == IceCubeType::Dry ? "Dry" : "Water")
               + " ice cubes x " + std::to_string(m_quantity);
    }
private:
    unsigned m_quantity;
    IceCubeType m_type;
};