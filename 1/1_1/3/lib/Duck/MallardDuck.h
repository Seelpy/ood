#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "Fly/FlyWithWings.h"
#include "Quack/Quack.h"
#include "Dance/DanceWaltz.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(std::make_unique<FlyStrategy>(NewFlyWithWings()), std::make_unique<QuackStrategy>(NewQuack()), std::make_unique<DanceStrategy>(NewDanceWaltz()))
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

#endif
