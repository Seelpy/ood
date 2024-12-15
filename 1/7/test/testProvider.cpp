#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include "./../lib/Shape/GroupShape/GroupShape.h"
#include "./../lib/Shape/Shapes/Rectangle.h"
#include "./../lib/Shape/Shapes/Triangle.h"
#include "./../lib/Slide/SlideService.h"

void AssertFrame(std::optional<RectD> actualFrame, std::optional<RectD> expectedFrame)
{
    EXPECT_EQ(actualFrame.has_value(), expectedFrame.has_value());
    if (actualFrame.has_value())
    {
        EXPECT_EQ(actualFrame->top, expectedFrame->top);
        EXPECT_EQ(actualFrame->width, expectedFrame->width);
        EXPECT_EQ(actualFrame->height, expectedFrame->height);
        EXPECT_EQ(actualFrame->left, expectedFrame->left);
    }
}

class GroupShapeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        groupShape = std::make_shared<GroupShape>();
    }

    std::shared_ptr<GroupShape> groupShape;
};

class GroupStyleTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        groupStyle = std::make_shared<GroupStyle>();
    }

    std::shared_ptr<GroupStyle> groupStyle;
};

/// STYLE TESTS ///

TEST_F(GroupStyleTest, add_style)
{
    Style style(0xFF0000FF);

    groupStyle->InsertStyle(style);
    EXPECT_EQ(groupStyle->GetStylesCount(), 1);
}

TEST_F(GroupStyleTest, remove_style)
{
    Style style(0xFF0000FF);

    groupStyle->RemoveStyleAtIndex(0);
    EXPECT_EQ(groupStyle->GetStylesCount(), 0);
}


TEST_F(GroupStyleTest, get_style_at)
{
    Style style(0xFF0000FF);
    groupStyle->InsertStyle(style, 0);
    EXPECT_EQ(groupStyle->GetStyleAtIndex(0).GetColor(), style.GetColor());
}

TEST_F(GroupStyleTest, set_color)
{
    Style style1(0xFF0000FF);
    Style style2(0xFF0FF000);
    groupStyle->InsertStyle(style1, 0);
    groupStyle->InsertStyle(style1, 1);
    groupStyle->SetColor(0xFFFFFFFF);
    EXPECT_EQ(groupStyle->GetColor(), 0xFFFFFFFF);
}

TEST_F(GroupStyleTest, add_group_to_group)
{
    Style style1(0xFF0000FF);
    Style style2(0xFF0FF000);
    Style style3(0xFF0FFFFF);
    groupStyle->InsertStyle(style1, 0);
    groupStyle->InsertStyle(style1, 1);

    GroupStyle groupStyle2;

    groupStyle2.InsertStyle(style3, 0);
    groupStyle->InsertStyle(style1, 0);
    groupStyle->InsertStyle(style2, 1);
    groupStyle->InsertStyle(groupStyle2, 3);

    EXPECT_EQ(groupStyle->GetStylesCount(), 3);
}

TEST_F(GroupStyleTest, get_style_if_not_equal)
{
    Style style1(0xFF0000FF);
    Style style2(0xFF0FF000);
    groupStyle->InsertStyle(style1, 0);
    groupStyle->InsertStyle(style2, 1);
    EXPECT_EQ(groupStyle->GetColor(), std::nullopt);
}

TEST_F(GroupStyleTest, get_style_if_equal)
{
    Style style1(0xFFFFFFFF);
    Style style2(0xFFFFFFFF);
    groupStyle->InsertStyle(style1, 0);
    groupStyle->InsertStyle(style1, 1);
    EXPECT_EQ(groupStyle->GetColor(), 0xFFFFFFFF);
}

TEST_F(GroupStyleTest, get_empty_style_count)
{
    EXPECT_EQ(groupStyle->GetStylesCount(), 0);
}

/// SHAPE TESTS ///

TEST_F(GroupShapeTest, add_shape)
{
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    groupShape->InsertShape(rectangle);
    size_t actualCount = groupShape->GetShapesCount();
    EXPECT_EQ(actualCount, 1);
}

TEST_F(GroupShapeTest, remove_shape)
{
    auto rectangle = std::make_shared<Rectangle>(
            RectD{0, 0, 100, 100},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    EXPECT_EQ(groupShape->GetShapesCount(), 1);

    groupShape->RemoveShapeAtIndex(0);
    EXPECT_EQ(groupShape->GetShapesCount(), 0);
}

TEST_F(GroupShapeTest, get_frame)
{
    auto rectangle1 = std::make_shared<Rectangle>(
            RectD{100, 100, 200, 200},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    auto rectangle2 = std::make_shared<Rectangle>(
            RectD{150, 150, 100, 100},
            std::make_unique<Style>(0x00FF00FF),
            std::make_unique<Style>(0x0000FFFF)
    );

    groupShape->InsertShape(rectangle1);
    groupShape->InsertShape(rectangle2);

    RectD expectedFrame = {100, 100, 200, 200};
    auto actualFrame = groupShape->GetFrame();
    AssertFrame(actualFrame, expectedFrame);
}

TEST_F(GroupShapeTest, get_shape_at)
{
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(triangle, 0);

    auto retrievedShape = groupShape->GetShapeAtIndex(0);

    EXPECT_NE(retrievedShape, nullptr);
}

TEST_F(GroupShapeTest, set_rect)
{
    auto rectangle1 = std::make_shared<Rectangle>(
            RectD{100, 100, 200, 200},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    auto rectangle2 = std::make_shared<Rectangle>(
            RectD{150, 150, 100, 100},
            std::make_unique<Style>(0x00FF00FF),
            std::make_unique<Style>(0x0000FFFF)
    );

    groupShape->InsertShape(rectangle1);
    groupShape->InsertShape(rectangle2);

    RectD expectedFrame = {100, 100, 200, 200};
    AssertFrame(groupShape->GetFrame(), expectedFrame);

    RectD newFrame = {20, 20, 20, 20};
    groupShape->SetFrame(newFrame);
    AssertFrame(groupShape->GetFrame(), newFrame);
}

// TODO: группа в группе
TEST_F(GroupShapeTest, add_group_to_group)
{
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );
    auto triangleInShape = std::make_shared<Triangle>(
            RectD{300, 300, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );
    auto groupShape2 = std::make_shared<GroupShape>();

    groupShape2->InsertShape(triangleInShape, 0);
    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);
    groupShape->InsertShape(groupShape2, 2);
    size_t actualCount = groupShape->GetShapesCount();

    EXPECT_EQ(actualCount, 3);
}

TEST_F(GroupShapeTest, get_style_if_not_equal)
{
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);

    auto outlineStyleColor = groupShape->GetLineStyle().GetColor();
    EXPECT_TRUE(outlineStyleColor == std::nullopt);

    auto fillStyleColor = groupShape->GetFillStyle().GetColor();
    EXPECT_TRUE(fillStyleColor == std::nullopt);
}

TEST_F(GroupShapeTest, get_style_if_equal)
{
    RGBAColor expectedOutlineStyleColor = 0xFF0000FF;
    RGBAColor expectedFillStyleColor = 0xFF0000FF;
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(expectedOutlineStyleColor),
            std::make_unique<Style>(expectedFillStyleColor)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(expectedOutlineStyleColor),
            std::make_unique<Style>(expectedFillStyleColor)
    );

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);

    EXPECT_EQ(expectedOutlineStyleColor, groupShape->GetLineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape->GetFillStyle().GetColor());
}

TEST_F(GroupShapeTest, set_group_style)
{
    RGBAColor expectedOutlineStyleColor = 0xFF0000FF;
    RGBAColor expectedFillStyleColor = 0xFF0000FF;
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFFFF00FF),
            std::make_unique<Style>(0xFFAA00FF)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0xFFAA00FF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);
    groupShape->GetLineStyle().SetColor(expectedOutlineStyleColor);
    groupShape->GetFillStyle().SetColor(expectedFillStyleColor);

    EXPECT_EQ(expectedOutlineStyleColor, groupShape->GetLineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape->GetFillStyle().GetColor());
}

TEST_F(GroupShapeTest, frame_from_empty_rectangles)
{
    auto rectangle1 = std::make_shared<Rectangle>(
            RectD{0, 0, 0, 0},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    auto rectangle2 = std::make_shared<Rectangle>(
            RectD{150, 150, 0, 0},
            std::make_unique<Style>(0x00FF00FF),
            std::make_unique<Style>(0x0000FFFF)
    );

    groupShape->InsertShape(rectangle1);
    groupShape->InsertShape(rectangle2);

    RectD expectedFrame = {0, 0, 150, 150};
    AssertFrame(groupShape->GetFrame(), expectedFrame);
}

TEST_F(GroupShapeTest, get_empty_shape_count)
{
    EXPECT_EQ(groupShape->GetShapesCount(), 0);
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}