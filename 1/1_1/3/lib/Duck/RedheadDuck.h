#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Duck.h"
#include "Fly/FlyWithWings.h"
#include "Quack/Quack.h"
#include "Dance/DanceMinuet.h"

#include <memory>

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(std::make_unique<FlyStrategy>(NewFlyWithWings()), std::make_unique<QuackStrategy>(NewQuack()), std::make_unique<DanceStrategy>(NewDanceMinuet()))
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};

#endif
