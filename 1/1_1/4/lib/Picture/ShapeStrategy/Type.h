//
// Created by Максим Веселов on 17.09.2024.
//

#ifndef INC_1_1_TYPE_H
#define INC_1_1_TYPE_H

#include "string"
#include <stdexcept>
#include "map"

// Убрать enum; string  tagget type

namespace shapes {
    enum StrategyType {
        CIRCLE,
        RECTANGLE,
        LINE,
        TEXT,
        TRIANGLE,
    };


    std::string ConvertTypeToString(StrategyType type);
    StrategyType ConvertTypeFromString(const std::string& type);
};



#endif //INC_1_1_TYPE_H
