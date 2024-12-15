#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include "./../lib/Graphic//graphics_lib.h"
#include "./..//lib/Graphic/modern_graphics_lib.h"
#include "./..//lib/Adapter/ModernGraphicsToGraphicsObjectAdapter.h"
#include "./..//lib/Adapter/ModernGraphicsToGraphicsClassAdapter.h"


namespace mgl = modern_graphics_lib;
namespace gl = graphics_lib;
namespace ad = adapter;

mgl::RGBAColor ConvertColorHEXToRGBAColor(uint32_t rgbColor)
{
    float a = float(((rgbColor >> 24) & 0xFF)) / 255.0f;
    float r = float(((rgbColor >> 16) & 0xFF)) / 255.0f;
    float g = float(((rgbColor >> 8) & 0xFF)) / 255.0f;
    float b = float((rgbColor & 0xFF)) / 255.0f;

    mgl::RGBAColor color = {r, g, b, a};
    return color;
}

void DrawWithCanvas(gl::ICanvas& canvas, const std::vector<mgl::Point>& points, uint32_t color)
{
    canvas.SetColor(color);

    if (points.empty())
    {
        return;
    }

    auto first = points.begin();
    canvas.MoveTo((*first).x, (*first).y);

    for (auto it = first + 1; it != points.end(); ++it)
    {
        canvas.LineTo((*it).x, (*it).y);
    }
}

void DrawWithModern(mgl::ModernGraphicsRenderer& render, const std::vector<mgl::Point>& points, uint32_t color)
{
    render.BeginDraw();

    const auto first = points.begin();

    if (points.empty())
    {
        return;
    }

    auto rgbaColor = ConvertColorHEXToRGBAColor(color);

    for (auto it = first; it != points.end() - 1; ++it)
    {
        render.DrawLine(*it, *(it + 1), rgbaColor);
    }
}

void EqualDraw(gl::ICanvas& adapter, mgl::ModernGraphicsRenderer& render, const std::vector<mgl::Point>& points, uint32_t color)
{
    DrawWithCanvas(adapter, points, color);
    DrawWithModern(render, points, color);
}

void ExpectObjectAdapterDrawEq(const std::vector<mgl::Point>& points, uint32_t color)
{
    std::stringstream ssAdapter;
    std::stringstream ssRender;

    mgl::ModernGraphicsRenderer render(ssRender);
    mgl::ModernGraphicsRenderer renderToAdapter(ssAdapter);
    ad::ModernGraphicsToGraphicsObjectAdapter adapter(renderToAdapter);

    EqualDraw(adapter, render, points, color);
    EXPECT_EQ(ssAdapter.str(), ssRender.str());
}

void ExpectClassAdapterDrawEq(const std::vector<mgl::Point>& points, uint32_t color)
{
    std::stringstream ssAdapter;
    std::stringstream ssRender;

    mgl::ModernGraphicsRenderer render(ssRender);
    ad::ModernGraphicsToGraphicsClassAdapter adapter(ssAdapter);

    EqualDraw(adapter, render, points, color);
    EXPECT_EQ(ssAdapter.str(), ssRender.str());
}

void RunAdapterTests(const std::function<void(const std::vector<mgl::Point>&, uint32_t)>& eqFunc)
{
    {
        uint32_t color = 0x01234567;
        eqFunc({}, color);
    }

    {
        uint32_t color = 0x01234567;
        eqFunc({{1, 1}}, color);
    }

    {
        uint32_t color = 0x01234567;
        std::vector<mgl::Point> points;
        for (int i = 10; i < 100; i += 10)
        {
            for (int j = 10; j < 100; j += 10)
            {
                points.push_back({i, j});
            }
        }
        eqFunc(points, color);
    }
}

TEST(object_adapter, tests)
{
    RunAdapterTests(ExpectObjectAdapterDrawEq);
}

TEST(class_adapter, tests)
{
    RunAdapterTests(ExpectClassAdapterDrawEq);
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}