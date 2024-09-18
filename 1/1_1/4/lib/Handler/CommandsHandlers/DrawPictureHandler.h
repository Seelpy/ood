//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_DRAWPICTUREHANDLER_H
#define INC_1_1_DRAWPICTUREHANDLER_H

#include "ParseFunc.h"
#include "./../../Picture/Shape.h"
#include "./../../Picture/Picture.h"
#include "./../../Canvas/ICanvas.h"

void DrawPicture(shapes::Picture &picture, ICanvas &canvas)
{
    picture.DrawPicture(canvas);
}

#endif //INC_1_1_DRAWPICTUREHANDLER_H
