#ifndef DANCEWALTZ_H
#define DANCEWALTZ_H

#include "DanceBehavior.h"
#include <iostream>

DanceStrategy NewDanceWaltz()
{
    return []() {
        std::cout << "I'm dance waltz!!" << std::endl;
    };
}

#endif
