//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_COMMANDTYPE_H
#define INC_1_1_COMMANDTYPE_H

#include <map>
#include <string>

enum CommandType {
    ADD_SHAPE,
    CHANGE_SHAPE,
    MOVE_SHAPE,
    CHANGE_COLOR,
    MOVE_PICTURE,
    DELETE_SHAPE,
    LIST_SHAPES,
    DRAW_SHAPE,
    DRAW_PICTURE,
    CLONE_SHAPE,
};

CommandType ConvertCommandTypeFromString(const std::string& type) {
    static const std::map<std::string, CommandType> commandMap = {
            {"AddShape", ADD_SHAPE},
            {"ChangeShape", CHANGE_SHAPE},
            {"MoveShape", MOVE_SHAPE},
            {"ChangeColor", CHANGE_COLOR},
            {"MovePicture", MOVE_PICTURE},
            {"DeleteShape", DELETE_SHAPE},
            {"List", LIST_SHAPES},
            {"DrawShape", DRAW_SHAPE},
            {"DrawPicture", DRAW_PICTURE},
            {"CloneShape", CLONE_SHAPE}
    };

    auto it = commandMap.find(type);
    if (it != commandMap.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Invalid command type: " + type);
    }
}

#endif //INC_1_1_COMMANDTYPE_H
