#include <gtest/gtest.h>
#include <istream>
#include "./../lib/Beverages/Milkshake.h"
#include "./../lib/Condiments/IceCubes.h"
#include "./../lib/Condiments/CondimentMaker.h"

TEST(type_test, big_milkshake)
{
    auto bigMilkshakeWithIce =
            std::make_unique<CMilkshake>(MilkShakeSizeType::BIG)
            << MakeCondiment<CIceCubes>(10);

    ASSERT_EQ(bigMilkshakeWithIce->GetDescription(), "Big Milkshake, Water ice cubes x 10");
    ASSERT_EQ(bigMilkshakeWithIce->GetCost(), 80 + 5*10); // cost big milkshake + count ice * water ice cost
}

TEST(type_test, small_milkshake)
{
    auto bigMilkshakeWithIce =
            std::make_unique<CMilkshake>(MilkShakeSizeType::SMALL)
                    << MakeCondiment<CIceCubes>(15);

    ASSERT_EQ(bigMilkshakeWithIce->GetDescription(), "Small Milkshake, Water ice cubes x 15");
    ASSERT_EQ(bigMilkshakeWithIce->GetCost(), 50 + 5*15); // cost big milkshake + count ice * water ice cost
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}