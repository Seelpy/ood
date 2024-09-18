//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_SHAPE_H
#define INC_1_1_SHAPE_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include "./../Canvas/ICanvas.h"
#include "./ShapeStrategy/IShapeStrategy.h"
#include "./ShapeStrategy/Type.h"

namespace shapes
{

    class Shape
    {
    public:
        Shape(std::string id, std::string color, std::unique_ptr<IShapeStrategy> strategy):
                m_id(std::move(id)), m_color(std::move(color)), m_shapeStrategy(std::move(strategy))
        {}

        void Draw(ICanvas& canvas) const
        {
            m_shapeStrategy->Draw(canvas, m_color);
        }
        void Move(double dx, double dy)
        {
            m_shapeStrategy->Move(dx, dy);
        }

        std::unique_ptr<Shape> Clone(const std::string& newId) const
        {
            return make_unique<Shape>(newId, m_color, m_shapeStrategy->Clone());
        }

        std::string GetId() const
        {
            return m_id;
        }

        void SetColor(const std::string& color)
        {
            m_color = color;
        }

        StrategyType GetType() const
        {
            return m_shapeStrategy->GetType();
        }

        std::string GetShapeInfo() const
        {
            return m_shapeStrategy->GetShapeInfo();
        }

        void SetNewGeometryType(std::unique_ptr<IShapeStrategy> newGeometryType)
        {
            m_shapeStrategy = std::move(newGeometryType);
        }

        ~Shape() = default;
    private:
        std::string m_id;
        std::string m_color;
        std::unique_ptr<IShapeStrategy> m_shapeStrategy;
    };

}

#endif //INC_1_1_SHAPE_H
