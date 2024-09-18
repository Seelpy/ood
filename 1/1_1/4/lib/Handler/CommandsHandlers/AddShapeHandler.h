//
// Created by Максим Веселов on 17.09.2024.
//

#ifndef INC_1_1_ADDSHAPEHANDLER_H
#define INC_1_1_ADDSHAPEHANDLER_H

#include "ParseFunc.h"
#include "./../../Picture/Shape.h"
#include "./../../Picture/Picture.h"

void AddShape(const std::istringstream &iss, shapes::Picture &picture)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto id = ParseString(tmpIss);
    auto color = ParseColor(tmpIss);
    auto strategy = ParseShapeStrategy(ParseShapeType(tmpIss), tmpIss);
    picture.AddShape(std::move(std::make_unique<shapes::Shape>(id, color, std::move(strategy))));
}

#endif //INC_1_1_ADDSHAPEHANDLER_H
