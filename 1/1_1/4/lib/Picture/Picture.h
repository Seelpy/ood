//
// Created by Максим Веселов on 08.09.2024.
//

#ifndef INC_1_1_PICTURE_H
#define INC_1_1_PICTURE_H

#include "Shape.h"
#include <vector>
#include <map>

namespace shapes
{
    class Picture
    {
    public:

        void AddShape(std::unique_ptr<Shape> shape);
        void MoveShape(const std::string& id, double dx, double dy);
        void MovePicture(double dx, double dy);
        void DeleteShape(const std::string& id);

        void PrintShapesInfo() const;

        void ChangeColor(const std::string& id, const std::string& color);
        void ChangeShape(const std::string& id, std::unique_ptr<IShapeStrategy> newShapeStrategy);

        void DrawShape(const std::string& id, ICanvas& canvas) const;
        void DrawPicture(ICanvas& canvas) const;

        void CloneShape(const std::string& id, const std::string& newId);

    private:
        std::map<std::string, std::unique_ptr<Shape>> m_shapes;
        std::vector<std::string> m_ids = {};

        void AssertShapeExist(const std::string& id) const;
    };

}

#endif //INC_1_1_PICTURE_H
