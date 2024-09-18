//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_DELETESHAPEHANDLER_H
#define INC_1_1_DELETESHAPEHANDLER_H

#include "ParseFunc.h"
#include "./../../Picture/Shape.h"
#include "./../../Picture/Picture.h"

void DeleteShape(const std::istringstream &iss, shapes::Picture &picture)
{
    std::istringstream tmpIss(iss.str());
    auto _ = ParseCommandType(tmpIss);
    auto id = ParseString(tmpIss);
    picture.DeleteShape(id);
}


#endif //INC_1_1_DELETESHAPEHANDLER_H
