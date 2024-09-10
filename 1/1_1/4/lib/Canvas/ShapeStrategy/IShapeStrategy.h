//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_ISHAPESTRATEGY_H
#define INC_1_1_ISHAPESTRATEGY_H

struct IShapeStrategy
{
    virtual ~IShapeStrategy(){};
    virtual void Move(double dx, double dy) = 0;
    virtual void Draw(double dx, double dy) = 0;
};

#endif //INC_1_1_ISHAPESTRATEGY_H
