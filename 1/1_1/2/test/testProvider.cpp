#include <gtest/gtest.h>
#include "./../lib/Duck/DecoyDuck.h"
#include "./../lib/Duck/MallardDuck.h"
#include "./../lib/Duck/ModelDuck.h"
#include "./../lib/Duck/RedheadDuck.h"
#include "./../lib/Duck/RubberDuck.h"
#include <sstream>

void assertFlyWithCount(Duck& duck, std::stringstream& buffer, int number)
{
    duck.Fly();
    ASSERT_EQ(buffer.str(), "Flight number: " + std::to_string(number) + "\nI'm flying with wings!!\n");
    buffer.str("");
    buffer.clear();
}

TEST (fly, check_nmber_of_flight)
{
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());

    MallardDuck duck;
    assertFlyWithCount(duck, buffer, 1);
    assertFlyWithCount(duck, buffer, 2);
    assertFlyWithCount(duck, buffer, 3);
    duck.SetFlyBehavior(std::make_unique<FlyWithWings>());
    assertFlyWithCount(duck, buffer, 1);
    assertFlyWithCount(duck, buffer, 2);
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}