#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/Squeak.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(std::make_unique<FlyStrategy>(NewFlyNoWay()), std::make_unique<QuackStrategy>(NewSqueak()), std::make_unique<DanceStrategy>(NewDanceNoWay()))
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}

	void Dance() override {}
};

#endif
