//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_CHANGECOLORHANDLER_H
#define INC_1_1_CHANGECOLORHANDLER_H

#include "ParseFunc.h"
#include "./../../Picture/Shape.h"
#include "./../../Picture/Picture.h"

void ChangeColor(const std::istringstream &iss, shapes::Picture &picture)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto id = ParseString(tmpIss);
    auto color = ParseColor(tmpIss);
    picture.ChangeColor(id, color);
}


#endif //INC_1_1_CHANGECOLORHANDLER_H
