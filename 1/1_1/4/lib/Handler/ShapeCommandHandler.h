//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_SHAPECOMMANDHANDLER_H
#define INC_1_1_SHAPECOMMANDHANDLER_H

#include "./CommandsHandlers/CommandType.h"
#include "./CommandsHandlers/ParseFunc.h"
#include "./CommandsHandlers/AddShapeHandler.h"
#include "./CommandsHandlers/MoveShapeHandler.h"
#include "./CommandsHandlers/MovePictureHandler.h"
#include "./CommandsHandlers/DeleteShapeHandler.h"
#include "./CommandsHandlers/ListShapesHandler.h"
#include "./CommandsHandlers/ChangeColorHandler.h"
#include "./CommandsHandlers/ChangeShapeHandler.h"
#include "./CommandsHandlers/DrawShapeHandler.h"
#include "./CommandsHandlers/DrawPictureHandler.h"
#include "./CommandsHandlers/CloneShapeHandler.h"
#include "./../Canvas/PNGCanvas/PNGCanvas.h"
#include "iostream"

const int CANVAS_WIDTH = 800;
const int CANVAS_HEIGHT = 800;

void HandleCommand(const std::string &line, shapes::Picture &picture, ICanvas &canvas)
{
    std::istringstream iss(line);
    switch (ParseCommandType(iss))
    {
        case CommandType::ADD_SHAPE:
            return AddShape(iss, picture);
        case CommandType::MOVE_SHAPE:
            return MoveShape(iss, picture);
        case CommandType::MOVE_PICTURE:
            return MovePicture(iss, picture);
        case CommandType::DELETE_SHAPE:
            return DeleteShape(iss, picture);
        case CommandType::LIST_SHAPES:
            return ListShapes(picture);
        case CommandType::CHANGE_COLOR:
            return ChangeColor(iss, picture);
        case CommandType::CHANGE_SHAPE:
            return ChangeShape(iss, picture);
        case CommandType::DRAW_SHAPE:
            return DrawShape(iss, picture, canvas);
        case CommandType::DRAW_PICTURE:
            return DrawPicture(picture, canvas);
        case CommandType::CLONE_SHAPE:
            return CloneShape(iss, picture);
        default:
            return;
    }
}

void HandleCommands(std::istream &str)
{
    shapes::Picture picture;
    PNGCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
    std::string line;
    while (getline(str, line))
    {
        if (line == "exit")
        {
            break;
        }

        try
        {
            HandleCommand(line, picture, canvas);
        } catch (const std::exception &e)
        {
            std::cout << e.what();
        }
    }
}

#endif //INC_1_1_SHAPECOMMANDHANDLER_H
