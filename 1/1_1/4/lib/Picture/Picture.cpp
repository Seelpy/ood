//
// Created by Максим Веселов on 17.09.2024.
//

#include <algorithm>
#include "Picture.h"

// TODO: Сделать получение фигуры и выпелить те методы которые можно вызвать напрямую из фигуры
// TODO: draw O(n)
// TODO: Класс picture не должен выводить информацию callback
//  TODO: namespaces

using namespace std;

void shapes::Picture::AddShape(std::unique_ptr<Shape> shape)
{
    if (m_shapes.contains(shape->GetId()))
    {
        throw invalid_argument("Shape with given ID already exists");
    }
    auto id = shape->GetId();
    m_shapes.emplace(id, std::move(shape));
    m_ids.push_back(id);
}

void shapes::Picture::MoveShape(const string &id, double dx, double dy)
{
    AssertShapeExist(id);
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
    AssertShapeExist(id);
    auto it = m_shapes.find(id);
    m_shapes.erase(it);
    std::erase(m_ids, id);
}

void shapes::Picture::PrintShapesInfo() const
{
    int number = 1;
    for (const auto &id: m_ids)
    {
        auto& shape = m_shapes.at(id);
        cout << number++ << " " << shapes::ConvertTypeToString(shape->GetType()) << " " << shape->GetId() << " "
             << shape->GetShapeInfo() << endl;
    }
}

void shapes::Picture::ChangeColor(const string &id, const string &color)
{
    AssertShapeExist(id);
    return m_shapes.at(id)->SetColor(color);
}

void shapes::Picture::ChangeShape(const string &id, std::unique_ptr<IShapeStrategy> newShapeStrategy)
{
    AssertShapeExist(id);
    m_shapes.at(id)->SetNewGeometryType(std::move(newShapeStrategy));
}

void shapes::Picture::DrawShape(const string &id, ICanvas &canvas) const
{
    AssertShapeExist(id);
    m_shapes.at(id)->Draw(canvas);
}

void shapes::Picture::DrawPicture(ICanvas &canvas) const
{
    for (const auto &id: m_ids)
    {
        m_shapes.at(id)->Draw(canvas);
    }
}

void shapes::Picture::CloneShape(const string &id, const string &newId)
{
    AssertShapeExist(id);
    auto newShape = m_shapes.at(id)->Clone(newId);
    AddShape(std::move(newShape));
}

void shapes::Picture::AssertShapeExist(const string &id) const
{
    if (!m_shapes.contains(id))
    {
        throw invalid_argument("Shape with given ID does not exist");
    }
}
