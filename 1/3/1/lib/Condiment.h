#pragma once

#include "IBeverage.h"

// Базовый декоратор "Добавка к напитку". Также является напитком
class CCondimentDecorator : public IBeverage
{
public:
	std::string GetDescription()const override
	{
		// Описание декорированного напитка добавляется к описанию оборачиваемого напитка
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost()const override
	{
		// Стоимость складывается из стоимости добавки и стоимости декорируемого напитка
		return m_beverage->GetCost() + GetCondimentCost();
	}

	// Стоимость и описание добавки вычисляется в классах конкретных декораторов
	virtual std::string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;
protected:
	CCondimentDecorator(IBeveragePtr && beverage)
		: m_beverage(std::move(beverage))
	{
	}
private:
	IBeveragePtr m_beverage;
};
