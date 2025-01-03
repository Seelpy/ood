#include <gtest/gtest.h>
#include "./../lib/Gumball/GumballMachine.h"

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}