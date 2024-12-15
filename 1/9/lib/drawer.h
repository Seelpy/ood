#pragma once

#include <iostream>
#include <cassert>
#include "image/image.h"
#include "geom/point.h"
#include <tuple>

class Drawer
{
public:
    static void DrawLine(Image &image, Point from, Point to, uint32_t color)
    {
        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);
        bool isSlopeLine = deltaY <= deltaX;
        DrawLineImpl(isSlopeLine, image, from, to, color);
    }

    static void DrawCircle(Image &image, Point center, int radius, uint32_t color)
    {
        DrawCircleImpl(image, center, radius, color, false);
    }

    static void FillCircle(Image &image, Point center, int radius, uint32_t color)
    {
        DrawCircleImpl(image, center, radius, color, true);
    }

private:
    static void DrawCircleImpl(Image &image, Point center, int radius, uint32_t color, bool fill)
    {
        int x = 0;
        int y = radius;
        int d = 3 - 2 * radius;

        while (x <= y)
        {
            if (fill)
            {
                // TODO: не рисовать 2 раза
                DrawLine(image, {center.x - y, center.y + x}, {center.x + y, center.y + x}, color);
                DrawLine(image, {center.x - y, center.y - x}, {center.x + y, center.y - x}, color);
            }
            else
            {
                image.SetPixel({center.x + x, center.y + y}, color);
                image.SetPixel({center.x - x, center.y + y}, color);
                image.SetPixel({center.x + x, center.y - y}, color);
                image.SetPixel({center.x - x, center.y - y}, color);
                image.SetPixel({center.x + y, center.y + x}, color);
                image.SetPixel({center.x - y, center.y + x}, color);
                image.SetPixel({center.x + y, center.y - x}, color);
                image.SetPixel({center.x - y, center.y - x}, color);
            }

            // TODO: расколдавать алгоритм
            if (d < 0)
            {
                d = d + 4 * x + 6;
            }
            else
            {
                d = d + 4 * (x - y) + 10;
                --y;
            }
            ++x;
        }
    }

    static int Sign(int value)
    {
        return (0 < value) - (value < 0);
    }

    static auto GetLineFuncs(bool isSlopeLine)
    {
        auto swap = [isSlopeLine](Point &p1, Point &p2) {
            int v1 = isSlopeLine ? p1.x : p1.y;
            int v2 = isSlopeLine ? p2.x : p2.y;
            if (v1 > v2)
            {
                std::swap(p1, p2);
            }
        };
        auto less = [isSlopeLine](Point p1, Point p2) {
            return isSlopeLine ? p1.x <= p2.x : p1.y <= p2.y;
        };
        auto inc = [isSlopeLine](Point &p) {
            isSlopeLine ? ++p.x : ++p.y;
        };
        auto sumStep = [isSlopeLine](Point &p, int step) {
            isSlopeLine ? p.y += step : p.x += step;
        };
        auto getStep = [isSlopeLine](Point &p1, Point &p2) {
            return isSlopeLine ? Sign(p2.y - p1.y) : Sign(p2.x - p1.x);
        };
        return std::make_tuple(swap, less, inc, sumStep, getStep);
    }

    static void DrawLineImpl(bool isSlope, Image &image, Point from, Point to, uint32_t color)
    {
        auto [swap, less, inc, sumStep, getStep] = GetLineFuncs(isSlope);

        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);

        swap(from, to);
        const int step = getStep(from, to);

        const int errorThreshold = deltaX + 1;
        const int deltaErr = deltaY + 1;

        int error = deltaErr / 2;

        for (Point p = from; less(p, to); inc(p))
        {
            image.SetPixel({p.x, p.y}, color);

            error += deltaErr;

            if (error >= errorThreshold)
            {
                sumStep(p, step);
                error -= errorThreshold;
            }
        }
    }
};
