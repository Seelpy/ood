#pragma once

#include "./../IPresenter.h"
#include "./../../model/draft/IDraft.h"
#include "./../../view//draft/Draft.h"
#include "./../shape/Shape.h"

class DraftPresenter : public IPresenter
{
public:
    DraftPresenter(Point position, const IDraftPtr &draft)
    {
        draft->RegisterObserver(
                [=, *this]() {
                    // TODO: add listen
                });

        m_shapes.reserve(draft->ListShapes().size());
        for (const auto& shape: draft->ListShapes())
        {
            m_shapes.push_back(ShapePresenter(shape));
        }

        std::vector<IViewPtr> shapeViews;
        shapeViews.reserve(m_shapes.size());
        for (auto shape: m_shapes)
        {
            shapeViews.push_back(shape.GetView());
        }
        m_draft = std::make_shared<DraftView>(Rect{position, draft->GetSize()}, shapeViews);
    }

    IViewPtr GetView() override
    {
        return m_draft;
    }

private:
    std::shared_ptr<DraftView> m_draft;
    std::vector<ShapePresenter> m_shapes;
};