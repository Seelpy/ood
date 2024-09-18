//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_MOVESHAPEHANDLER_H
#define INC_1_1_MOVESHAPEHANDLER_H

#include "./../../Picture/Picture.h"
#include "ParseFunc.h"
#include "./../../Picture/Shape.h"

void MoveShape(const std::istringstream &iss, shapes::Picture &picture)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto id = ParseString(tmpIss);
    auto dx = ParseDouble(tmpIss);
    auto dy = ParseDouble(tmpIss);
    picture.MoveShape(id, dx, dy);
}

#endif //INC_1_1_MOVESHAPEHANDLER_H
