#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "Fly/FlyWithWings.h"
#include "Quack/Quack.h"
#include "Dance/DanceWaltz.h"

// TOOD: сделать так чтобы не компилировался

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(NewFlyWithWings, NewQuack(), NewDanceWaltz())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

#endif
