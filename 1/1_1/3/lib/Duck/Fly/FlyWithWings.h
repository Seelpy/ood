#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "FlyBehavior.h"
#include <iostream>
#include <functional>

FlyStrategy NewFlyWithWings()
{
    uint countOfFlights;
    return [&countOfFlights]() {
        std::cout << "Flight number: " << countOfFlights + 1 << std::endl;
        std::cout << "I'm flying with wings!!" << std::endl;

        countOfFlights++;
    };
}

#endif