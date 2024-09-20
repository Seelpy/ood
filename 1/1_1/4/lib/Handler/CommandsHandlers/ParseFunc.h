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


shapes::StrategyType ParseShapeType(std::istringstream &command)
{
    auto part = GetNextCommandPart(command);
    return shapes::ConvertTypeFromString(part);
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

std::string ParseText(std::istringstream &command)
{
    std::string text;
    getline(command, text);
    return text;
}

CommandType ParseCommandType(std::istringstream &command)
{
    return ConvertCommandTypeFromString(GetNextCommandPart(command));
}

shapes::CircleStrategy ParseCircleStrategy(std::istringstream &iss)
{
    auto x = ParseDouble(iss);
    auto y = ParseDouble(iss);
    auto r = ParseDouble(iss);
    return {shapes::Point{.x =  x, .y =  y}, r};
}

shapes::RectangleStrategy ParseRectangleStrategy(std::istringstream &iss)
{
    auto left = ParseDouble(iss);
    auto top = ParseDouble(iss);
    auto width = ParseDouble(iss);
    auto height = ParseDouble(iss);
    return {shapes::Point{.x = left, .y =   top}, width, height};
}

shapes::TriangleStrategy ParseTriangleStrategy(std::istringstream &iss)
{
    auto x1 = ParseDouble(iss);
    auto y1 = ParseDouble(iss);
    auto x2 = ParseDouble(iss);
    auto y2 = ParseDouble(iss);
    auto x3 = ParseDouble(iss);
    auto y3 = ParseDouble(iss);
    return {shapes::Point{.x = x1, .y = y1}, shapes::Point{.x = x2, .y = y2}, shapes::Point{.x = x3, .y = y3}};
}

shapes::LineStrategy ParseLineStrategy(std::istringstream &iss)
{
    auto x1 = ParseDouble(iss);
    auto y1 = ParseDouble(iss);
    auto x2 = ParseDouble(iss);
    auto y2 = ParseDouble(iss);
    return {shapes::Point{.x = x1, .y = y1}, shapes::Point{.x = x2, .y = y2}};
}

shapes::TextStrategy ParseTextStrategy(std::istringstream &iss)
{
    auto x1 = ParseDouble(iss);
    auto y1 = ParseDouble(iss);
    auto size = ParseDouble(iss);
    auto text = ParseText(iss);
    return {shapes::Point{.x =x1, .y = y1}, size, text};
}

std::unique_ptr<shapes::IShapeStrategy> ParseShapeStrategy(shapes::StrategyType shapeType, std::istringstream &iss)
{
    switch (shapeType)
    {
        case shapes::StrategyType::CIRCLE:
            return std::make_unique<shapes::CircleStrategy>(ParseCircleStrategy(iss));
        case shapes::StrategyType::RECTANGLE:
            return std::make_unique<shapes::RectangleStrategy>(ParseRectangleStrategy(iss));
        case shapes::StrategyType::LINE:
            return std::make_unique<shapes::LineStrategy>(ParseLineStrategy(iss));
        case shapes::StrategyType::TEXT:
            return std::make_unique<shapes::TextStrategy>(ParseTextStrategy(iss));
        case shapes::StrategyType::TRIANGLE:
            return std::make_unique<shapes::TriangleStrategy>(ParseTriangleStrategy(iss));
        default:
            throw std::invalid_argument("unexpected shape type");
    }
}

#endif //INC_1_1_PARSEFUNC_H
