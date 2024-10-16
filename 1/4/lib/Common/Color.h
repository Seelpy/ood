#pragma once

#include <string>

enum Color
{
    GREEN,
    RED,
    BLUE,
    YELLOW,
    PINK,
    BLACK
};

Color ColorFromString(const std::string &data)
{
    if (data == "green") return Color::GREEN;
    if (data == "red") return Color::RED;
    if (data == "blue") return Color::BLUE;
    if (data == "yellow") return Color::YELLOW;
    if (data == "pink") return Color::PINK;
    if (data == "black") return Color::BLACK;
    throw std::invalid_argument("Unknown color");
}