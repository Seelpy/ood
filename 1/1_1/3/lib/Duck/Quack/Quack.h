#ifndef QUACKBEHAVIOR_H
#define QUACKBEHAVIOR_H

#include "QuakBehavior.h"
#include <iostream>

QuackStrategy NewQuack()
{
    return []() {
        std::cout << "Quack Quack!!!" << std::endl;
    };
}

#endif
