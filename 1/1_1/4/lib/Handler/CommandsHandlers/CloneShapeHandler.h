//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_CLONESHAPEHANDLER_H
#define INC_1_1_CLONESHAPEHANDLER_H


#include "ParseFunc.h"
#include "./../../Picture/Shape.h"
#include "./../../Picture/Picture.h"

void CloneShape(const std::istringstream &iss, shapes::Picture &picture)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto id = ParseString(tmpIss);
    auto newId = ParseString(tmpIss);
    picture.CloneShape(id, newId);
}

#endif //INC_1_1_CLONESHAPEHANDLER_H
