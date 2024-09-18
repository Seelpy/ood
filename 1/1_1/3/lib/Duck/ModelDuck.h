#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/Quack.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(NewFlyNoWay(), NewQuack(), NewDanceNoWay())
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}

	void Dance() override {}
};

#endif
