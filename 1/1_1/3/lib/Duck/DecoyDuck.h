#ifndef DECOYDUCK_H
#define DECOYDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/MuteQuack.h"
#include "Dance/DanceNoWay.h"
#include <iostream>
#include <memory>

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(std::make_unique<FlyStrategy>(NewFlyNoWay()), std::make_unique<QuackStrategy>(NewMuteQuack()), std::make_unique<QuackStrategy>(NewDanceNoWay()))
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}

	void Dance() override {}
};

#endif
