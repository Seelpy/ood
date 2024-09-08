#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/Quack.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(std::make_unique<FlyStrategy>(NewFlyNoWay()), std::make_unique<QuackStrategy>(NewQuack()), std::make_unique<DanceStrategy>(NewDanceNoWay()))
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}

	void Dance() override {}
};

#endif
