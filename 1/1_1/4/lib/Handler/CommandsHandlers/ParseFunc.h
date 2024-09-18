//
// Created by Максим Веселов on 18.09.2024.
//

#ifndef INC_1_1_PARSEFUNC_H
#define INC_1_1_PARSEFUNC_H

#include "./../../Picture/ShapeStrategy/Type.h"
#include "./../../Picture/ShapeStrategy/CircleStrategy.h"
#include "./../../Picture/ShapeStrategy/LineStrategy.h"
#include "./../../Picture/ShapeStrategy/RectangleStrategy.h"
#include "./../../Picture/ShapeStrategy/TextStrategy.h"
#include "./../../Picture/ShapeStrategy/TriangleStrategy.h"
#include "CommandType.h"
#include <string>
#include <stdexcept>
#include <sstream>

void AssertNotEmpty(const std::string &data)
{
    if (data.empty())
    {
        throw std::invalid_argument("invalid empty param");
    }
}

std::string GetNextCommandPart(std::istringstream &command)
{
    std::string part;
    command >> part;
    AssertNotEmpty(part);
    return part;
}


StrategyType ParseShapeType(std::istringstream &command)
{
    auto part = GetNextCommandPart(command);
    return ConvertTypeFromString(part);
}

double ParseDouble(std::istringstream &command)
{
    auto part = GetNextCommandPart(command);
    try
    {
        return std::stod(part);
    } catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument("Invalid input: not a valid number.");
    } catch (const std::out_of_range &e)
    {
        throw std::invalid_argument("Input is out of range for a double.");
    }
}

std::string ParseColor(std::istringstream &command)
{
    return GetNextCommandPart(command);
}

std::string ParseString(std::istringstream &command)
{
    return GetNextCommandPart(command);
}

std::string ParseText(std::istringstream& command)
{
    std::string text;
    getline(command, text);
    return text;
}

CommandType ParseCommandType(std::istringstream &command)
{
    return ConvertCommandTypeFromString(GetNextCommandPart(command));
}

CircleStrategy ParseCircleStrategy(std::istringstream &iss)
{
    auto x = ParseDouble(iss);
    auto y = ParseDouble(iss);
    auto r = ParseDouble(iss);
    return {x, y, r};
}

RectangleStrategy ParseRectangleStrategy(std::istringstream &iss)
{
    auto left = ParseDouble(iss);
    auto top = ParseDouble(iss);
    auto width = ParseDouble(iss);
    auto height = ParseDouble(iss);
    return {left, top, width, height};
}

TriangleStrategy ParseTriangleStrategy(std::istringstream &iss)
{
    auto x1 = ParseDouble(iss);
    auto y1 = ParseDouble(iss);
    auto x2 = ParseDouble(iss);
    auto y2 = ParseDouble(iss);
    auto x3 = ParseDouble(iss);
    auto y3 = ParseDouble(iss);
    return {x1, y1, x2, y2, x3, y3};
}

LineStrategy ParseLineStrategy(std::istringstream &iss)
{
    auto x1 = ParseDouble(iss);
    auto y1 = ParseDouble(iss);
    auto x2 = ParseDouble(iss);
    auto y2 = ParseDouble(iss);
    return {x1, y1, x2, y2};
}

TextStrategy ParseTextStrategy(std::istringstream &iss)
{
    auto x1 = ParseDouble(iss);
    auto y1 = ParseDouble(iss);
    auto size = ParseDouble(iss);
    auto text = ParseText(iss);
    return {x1, y1, size, text};
}

std::unique_ptr<IShapeStrategy> ParseShapeStrategy(StrategyType shapeType, std::istringstream &iss)
{
    switch (shapeType)
    {
        case StrategyType::CIRCLE: return std::make_unique<CircleStrategy>(ParseCircleStrategy(iss));
        case StrategyType::RECTANGLE: return std::make_unique<RectangleStrategy>(ParseRectangleStrategy(iss));
        case StrategyType::LINE: return std::make_unique<LineStrategy>(ParseLineStrategy(iss));
        case StrategyType::TEXT:return std::make_unique<TextStrategy>(ParseTextStrategy(iss));
        case StrategyType::TRIANGLE:return std::make_unique<TriangleStrategy>(ParseTriangleStrategy(iss));
        default: throw std::invalid_argument("unexpected shape type");
    }
}

#endif //INC_1_1_PARSEFUNC_H
