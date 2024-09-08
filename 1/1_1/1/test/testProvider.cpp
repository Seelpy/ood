#include <gtest/gtest.h>
#include "./../lib/Duck/DecoyDuck.h"
#include "./../lib/Duck/MallardDuck.h"
#include "./../lib/Duck/ModelDuck.h"
#include "./../lib/Duck/RedheadDuck.h"
#include "./../lib/Duck/RubberDuck.h"
#include <sstream>

const std::string danceNoWayOutput;
const std::string danceMinuetOutput = "I'm dance minuet\n";
const std::string danceWaltzOutput = "I'm dance waltz!!\n";

void assertDance(Duck &duck, const std::string& danceOutput)
{
    std::stringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());
    duck.Dance();
    ASSERT_EQ(buffer.str(), danceOutput);
}

TEST (dance, dance_with_decoy_duck)
{
    DecoyDuck duck;
    assertDance(duck, danceNoWayOutput);
}

TEST (dance, dance_with_mallard_duck)
{
    MallardDuck duck;
    assertDance(duck, danceWaltzOutput);
}

TEST (dance, dance_with_model_duck)
{
    ModelDuck duck;
    assertDance(duck, danceNoWayOutput);
}

TEST (dance, dance_with_readhead_duck)
{
    RedheadDuck duck;
    assertDance(duck, danceMinuetOutput);
}

TEST (dance, dance_with_rubber_duck)
{
    RubberDuck duck;
    assertDance(duck, danceNoWayOutput);
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}