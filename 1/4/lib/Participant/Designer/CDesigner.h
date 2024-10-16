#pragma once

#include "IDesigner.h"
#include "istream"

class Designer : public IDesigner
{
public:
    explicit Designer(shapes::IShapeFactory &factory)
            : m_factory(factory)
    {}

    CPictureDraft CreateDraft(std::istream &inputData) override
    {
        std::vector<shapes::CShapePtr> listShapes;
        std::string line;
        while (getline(inputData, line))
        {
            listShapes.push_back(std::move(m_factory.CreateShape(line)));
        }
        return CPictureDraft(std::move(listShapes));
    }

private:
    shapes::IShapeFactory &m_factory;
};
