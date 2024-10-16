#pragma once

#include "CShape.h"

namespace shapes
{
    class IShapeFactory
    {
    public:
        virtual CShapePtr CreateShape(const std::string &description) const = 0;

        virtual ~IShapeFactory() = default;
    };
}

