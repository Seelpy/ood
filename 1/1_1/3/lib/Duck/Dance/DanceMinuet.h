#ifndef DANCEMINUET_H
#define DANCEMINUET_H

#include "DanceBehavior.h"
#include <iostream>

DanceStrategy NewDanceMinuet()
{
    return []() {
        std::cout << "I'm dance minuet" << std::endl;
    };
}

#endif
