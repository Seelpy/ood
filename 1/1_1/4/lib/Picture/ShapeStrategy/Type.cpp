//
// Created by Максим Веселов on 18.09.2024.
//

#include "Type.h"

std::string convertTypeToString(StrategyType type) {
    switch (type) {
        case CIRCLE: return "circle";
        case RECTANGLE: return "rectangle";
        case LINE: return "line";
        case TEXT: return "text";
        case TRIANGLE: return "triangle";
        default: throw std::invalid_argument("invalid shape strategy type");
    }
}

StrategyType ConvertTypeFromString(const std::string& type) {
    static const std::map<std::string, StrategyType> typeMap = {
            {"circle", CIRCLE},
            {"rectangle", RECTANGLE},
            {"line", LINE},
            {"text", TEXT},
            {"triangle", TRIANGLE}
    };

    auto it = typeMap.find(type);
    if (it != typeMap.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Invalid shape strategy type: " + type);
    }
}