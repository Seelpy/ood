//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_DRAWSHAPEHANDLER_H
#define INC_1_1_DRAWSHAPEHANDLER_H

#include "ParseFunc.h"
#include "./../../Picture/Shape.h"
#include "./../../Picture/Picture.h"
#include "./../../Canvas/ICanvas.h"

void DrawShape(const std::istringstream &iss, shapes::Picture &picture, ICanvas &canvas)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto id = ParseString(tmpIss);
    picture.DrawShape(id, canvas);
}

#endif //INC_1_1_DRAWSHAPEHANDLER_H
