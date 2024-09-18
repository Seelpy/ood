//
// Created by Максим Веселов on 17.09.2024.
//

#include <algorithm>
#include "Picture.h"

using namespace std;

void shapes::Picture::AddShape(std::unique_ptr<Shape> shape)
{
    if (m_shapes.contains(shape->GetId()))
    {
        throw invalid_argument("Shape with given ID already exists");
    }
    m_shapes.emplace(shape->GetId(), std::move(shape));
}

void shapes::Picture::MoveShape(const string &id, double dx, double dy)
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID does not exist");
    }
    return m_shapes.at(id)->Move(dx, dy);
}

void shapes::Picture::MovePicture(double dx, double dy)
{
    for (auto &shape: m_shapes)
    {
        shape.second->Move(dx, dy);
    }
}

void shapes::Picture::DeleteShape(const string &id)
{
    auto it = m_shapes.find(id);
    if (it == m_shapes.end())
    {
        throw invalid_argument("Shape with given ID does not exist");
    }
    m_shapes.erase(it);
}

void shapes::Picture::PrintShapesInfo() const
{
    int number = 1;
    for (const auto &shape: m_shapes)
    {
        cout << number++ << " " << shape.second->GetType() << " " << shape.second->GetId()
             << shape.second->GetShapeInfo() << endl;
    }
}

string shapes::Picture::GetShapeById(const string &id) const
{
    if (!m_shapes.contains(id))
    {
        return "";
    }

    auto shape = m_shapes.at(id).get();
    return convertTypeToString(shape->GetType()) + " " + shape->GetShapeInfo();
}

void shapes::Picture::ChangeColor(const string &id, const string &color)
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID does not exist");
    }

    return m_shapes.at(id)->SetColor(color);
}

void shapes::Picture::ChangeShape(const string &id, std::unique_ptr<IShapeStrategy> newShapeGeometryType)
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID does not exist");
    }

    m_shapes.at(id)->SetNewGeometryType(std::move(newShapeGeometryType));
}

void shapes::Picture::DrawShape(const string &id, ICanvas &canvas) const
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID does not exist");
    }
    m_shapes.at(id)->Draw(canvas);
}

void shapes::Picture::DrawPicture(ICanvas &canvas) const
{
    for (const auto &shape: m_shapes)
    {
        shape.second->Draw(canvas);
    }
}

void shapes::Picture::CloneShape(const string &id, const string &newId)
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID not found");
    }

    auto newShape = m_shapes.at(id)->Clone(newId);
    AddShape(std::move(newShape));
}
