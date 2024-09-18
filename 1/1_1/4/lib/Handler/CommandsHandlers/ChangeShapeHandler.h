//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_CHANGESHAPEHANDLER_H
#define INC_1_1_CHANGESHAPEHANDLER_H

#include "ParseFunc.h"
#include "./../../Picture/Shape.h"
#include "./../../Picture/Picture.h"

void ChangeShape(const std::istringstream &iss, shapes::Picture &picture)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto id = ParseString(tmpIss);
    auto type = ParseShapeType(tmpIss);
    auto strategy = ParseShapeStrategy(type, tmpIss);
    picture.ChangeShape(id, std::move(strategy));
}

#endif //INC_1_1_CHANGESHAPEHANDLER_H
