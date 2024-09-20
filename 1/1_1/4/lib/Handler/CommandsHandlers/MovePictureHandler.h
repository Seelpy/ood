//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_MOVEPICTUREHANDLER_H
#define INC_1_1_MOVEPICTUREHANDLER_H

#include "./../../Picture/Picture.h"
#include "ParseFunc.h"
#include "./../../Picture/Shape.h"

void MovePicture(const std::istringstream &iss, shapes::Picture &picture)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto dx = ParseDouble(tmpIss);
    auto dy = ParseDouble(tmpIss);
    picture.MovePicture(dx, dy);
}

#endif //INC_1_1_MOVEPICTUREHANDLER_H
