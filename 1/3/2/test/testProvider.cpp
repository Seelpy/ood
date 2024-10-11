#include <gtest/gtest.h>
#include <istream>
#include "./../lib/Beverages/Milkshake.h"
#include "./../lib/Condiments/Chocolate.h"
#include "./../lib/Condiments/CondimentMaker.h"

TEST(condiments, too_many_count_of_chocolate)
{
    ASSERT_ANY_THROW(
            std::make_unique<CMilkshake>(MilkShakeSizeType::BIG)
                    << MakeCondiment<CChocolate>(10));
}

TEST(condiments, chocolate)
{
    auto bigMilkshakeWithIce =
            std::make_unique<CMilkshake>(MilkShakeSizeType::SMALL)
                    << MakeCondiment<CChocolate>(5);

    ASSERT_EQ(bigMilkshakeWithIce->GetDescription(), "Small Milkshake, Chocolate x5");
    ASSERT_EQ(bigMilkshakeWithIce->GetCost(), 50 + 10*5); // cost big milkshake + count ice * water ice cost
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}