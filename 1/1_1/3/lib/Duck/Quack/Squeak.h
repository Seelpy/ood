#ifndef SQUEAKBEHAVIOR_H
#define SQUEAKBEHAVIOR_H

#include "QuakBehavior.h"
#include <iostream>

QuackStrategy NewSqueak()
{
    return []() {
        std::cout << "Squeek!!!" << std::endl;
    };
}

#endif
