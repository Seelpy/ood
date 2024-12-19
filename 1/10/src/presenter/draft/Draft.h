#pragma once

#include "./../IPresenter.h"
#include "./../BasePresenter.h"
#include "./../../model/draft/IDraft.h"
#include "./../../view//draft/Draft.h"
#include "./../shape/Shape.h"

class DraftPresenter : public BasePresenter
{
public:
    DraftPresenter(common::Point position, const IDraftPtr &draft)
    {
        m_shapes.reserve(draft->ListShapes().size());
        for (const auto &shape: draft->ListShapes())
        {
            m_shapes.push_back(std::make_shared<ShapePresenter>(shape));
        }
        std::vector<IViewPtr> shapeViews;
        shapeViews.reserve(m_shapes.size());
        for (auto shape: m_shapes)
        {
            shapeViews.push_back(shape->GetView());
        }
        m_draft = std::make_shared<DraftView>(common::Rect{position, draft->GetSize()}, shapeViews);
        draft->RegisterObserver(
                [=, *this]() {
                    // TODO: add listen
                });

        InitBase(m_draft);
    }

    IViewPtr GetView() override
    {
        return m_draft;
    }

private:
    std::shared_ptr<DraftView> m_draft = nullptr;
    std::vector<IPresenterPtr> m_shapes;
};