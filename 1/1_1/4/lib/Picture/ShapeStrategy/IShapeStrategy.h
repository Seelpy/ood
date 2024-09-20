//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_ISHAPESTRATEGY_H
#define INC_1_1_ISHAPESTRATEGY_H

#include "./../../Canvas/ICanvas.h"
#include "Type.h"
#include <string>

namespace shapes
{
    class IShapeStrategy
    {
    public:
        virtual ~IShapeStrategy() = default;

        virtual shapes::StrategyType GetType() = 0;

        virtual void Draw(ICanvas &canvas, const std::string &color) = 0;

        virtual void Move(double dx, double dy) = 0;

        virtual std::string GetShapeInfo() = 0;

        virtual std::unique_ptr<IShapeStrategy> Clone() const = 0;
    };
}
#endif //INC_1_1_ISHAPESTRATEGY_H
