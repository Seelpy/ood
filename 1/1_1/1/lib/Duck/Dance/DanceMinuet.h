#ifndef DANCEMINUET_H
#define DANCEMINUET_H

#include "IDanceBehavior.h"
#include <iostream>

class DanceMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dance minuet" << std::endl;
	}
};

#endif
