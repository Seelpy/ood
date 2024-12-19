#pragma once

#include "./../BaseView.h"
#include <functional>
#include <optional>
#include "./../../model/style/fill/IFillStyle.h"
#include "./../../model/style/line/ILineStyle.h"
#include <string>
#include <utility>
#include <algorithm>

class ContainerView : public BaseView
{
public:
    ContainerView(common::Rect frame, const std::vector<IViewPtr> &views): m_views(views), m_frame(frame), BaseView(frame)
    {
    }

    ~ContainerView() override = default;

    void Show(ICanvas &canvas) override
    {
        for (const auto& view: ListViewsImpl())
        {
            view->Show(canvas);
        }
    }

    std::vector<IViewPtr> ListViewsImpl() override
    {
        return m_views;
    }

    common::Rect GetFrame() override
    {
        std::vector<common::Rect> frames;
        for (auto view: m_views)
        {
            frames.push_back(view->GetFrame());
        }

        if (frames.empty())
        {
            return m_frame;
        }

        unsigned int minX = frames[0].LeftTop().X();
        unsigned int minY = frames[0].LeftTop().Y();
        unsigned int maxX = frames[0].RightDown().X();
        unsigned int maxY = frames[0].RightDown().Y();

        for (auto& frame : frames) {
            if (minX > frame.LeftTop().X())
            {
                minX = frame.LeftTop().X();
            }
            if (minY > frame.LeftTop().Y())
            {
                minY = frame.LeftTop().Y();
            }
            if (maxX < frame.RightDown().X())
            {
                maxX = frame.RightDown().X();
            }
            if (maxY < frame.RightDown().Y())
            {
                maxY = frame.RightDown().Y();
            }
        }
        return common::Rect{{minX, minY}, {maxX -  minX, maxY - minY}};
    }

private:
    std::vector<IViewPtr> m_views;
    common::Rect m_frame;
};

