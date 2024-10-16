#pragma once

#include <memory>
#include <algorithm>
#include <cctype>
#include "IFactory.h"
#include "./Strategy//CEllipseStrategy.h"
#include "./Strategy/CRectangeStrategy.h"
#include "./Strategy/CReqularPolygonStrategy.h"
#include "./Strategy/CTriangleStrategy.h"
#include <sstream>

namespace shapes
{
    class CFactory : public IShapeFactory
    {
    public:
        CShapePtr CreateShape(const std::string &description) const override
        {
            std::istringstream iss(description);

            std::string shapeType;
            iss >> shapeType;

            std::string colorStr;
            iss >> colorStr;
            Color color = CFactory::GetColor(colorStr);

            if (shapeType == "triangle") return std::make_unique<CShape>(color, CFactory::CreateTriangleStrategy(iss));
            if (shapeType == "ellipse") return std::make_unique<CShape>(color, CFactory::CreateEllipse(iss));
            if (shapeType == "rectangle") return std::make_unique<CShape>(color, CFactory::CreateRectangle(iss));
            if (shapeType == "rpolygon") return std::make_unique<CShape>(color, CFactory::CreateRegularPolygon(iss));

            throw std::invalid_argument("Unknown shape type");
        }

    private:
        static Color GetColor(const std::string &colorStr)
        {
            return ColorFromString(colorStr);
        }

        static Point GetPoint(std::istream &iss)
        {
            double x, y;
            iss >> x >> y;
            return {x, y};
        }

        static double GetDouble(std::istream &iss)
        {
            double x;
            iss >> x;
            return x;
        }

        static unsigned int GetUnsigned(std::istream &iss)
        {
            unsigned int x;
            iss >> x;
            return x;
        }

        static std::unique_ptr<CTriangleStrategy> CreateTriangleStrategy(std::istringstream &iss)
        {
            return std::make_unique<CTriangleStrategy>(GetPoint(iss), GetPoint(iss), GetPoint(iss));
        }

        static std::unique_ptr<CEllipseStrategy> CreateEllipse(std::istringstream &iss)
        {
            return std::make_unique<CEllipseStrategy>(GetPoint(iss), GetDouble(iss), GetDouble(iss));
        }

        static std::unique_ptr<CRectangleStrategy> CreateRectangle(std::istringstream &iss)
        {
            return std::make_unique<CRectangleStrategy>(GetPoint(iss), GetPoint(iss));
        }

        static std::unique_ptr<CRegularPolygonStrategy> CreateRegularPolygon(std::istringstream &iss)
        {
            return std::make_unique<CRegularPolygonStrategy>(GetPoint(iss), GetUnsigned(iss), GetDouble(iss));
        }
    };
}
