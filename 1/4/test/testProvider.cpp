#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <istream>
#include "./../lib/Canvas/ICanvas.h"
#include "./../lib/Shape/CShape.h"
#include "../lib/Shape/IFactory.h"
#include "../lib/Participant/Designer/IDesigner.h"
#include "../lib/Participant/Painter/IPainter.h"
#include "../lib/Shape/Strategy/CEllipseStrategy.h"
#include "../lib/Shape/Strategy/CReqularPolygonStrategy.h"
#include "../lib/Shape/Strategy/CRectangeStrategy.h"
#include "../lib/Shape/Strategy/CTriangleStrategy.h"

using namespace shapes;
using namespace gfx;

using ::testing::_;
using ::testing::Return;

class MockShape : public CShape
{
public:
    explicit MockShape(Color color, IShapeStrategyPtr strategy) : CShape(color, std::move(strategy)) {}

    MOCK_METHOD(void, Draw, (ICanvas &canvas), (const));
};

class MockShapeFactory : public IShapeFactory
{
public:
    MOCK_METHOD(std::unique_ptr<CShape>, CreateShape, (const std::string& description), (override));
};

class MockDesigner : public IDesigner
{
public:
    MOCK_METHOD(CPictureDraft, CreateDraft, (std::istream & inputData), (override));
};

class MockPainter : public IPainter {
public:
    MOCK_METHOD(void, DrawPicture, (const CPictureDraft& draft, gfx::ICanvas& canvas), (override));
};

class MockCanvas : public ICanvas {
public:
    MOCK_METHOD(void, SetColor, (Color color), (override));
    MOCK_METHOD(void, DrawLine, (Point from, Point to), (override));
    MOCK_METHOD(void, DrawEllipse, (Point c, double rx, double ry), (override));
};

void AssertEqualPoint(Point expectedPoint, Point actualPoint)
{
    EXPECT_EQ(expectedPoint.x, actualPoint.x);
    EXPECT_EQ(expectedPoint.y, actualPoint.y);
}

TEST(rectangle, draw_success)
{
    Color color = Color::BLACK;
    Point lt(10, 20);
    Point rb(40, 70);

    CShape rectangle(color, std::make_unique<CRectangleStrategy>(lt, rb));

    MockCanvas mockCanvas;

    Point p1(10, 20), p2(40, 20);
    EXPECT_CALL(mockCanvas, SetColor(color))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(Point{10, 20}, Point{40, 20}))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(40, 20, 40, 70))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(40, 70, 10, 70))
            .Times(1);
    EXPECT_CALL(mockCanvas, DrawLine(10, 70, 10, 20))
            .Times(1);

    rectangle.Draw(mockCanvas);
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}