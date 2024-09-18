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
		: Duck(NewFlyNoWay(), NewMuteQuack(), NewDanceNoWay())
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}

	void Dance() override {}
};

#endif
