#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>
// TODO:
class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
        std::cout << "Flight number: " << m_countOfFlights + 1 << std::endl;
		std::cout << "I'm flying with wings!!" << std::endl;

        m_countOfFlights++;
	}
private:
    uint m_countOfFlights = 0;
};

#endif
