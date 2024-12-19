#pragma once

#include "./../IView.h"
#include "./../BaseView.h"
#include <utility>
#include <vector>

class DraftView : public BaseView
{
public:
    DraftView(common::Rect frame, std::vector<IViewPtr> shapes) : m_shapes(std::move(shapes)), m_frame(frame), BaseView(frame)
    {

    }

    void Show(ICanvas &canvas) override
    {
        canvas.DrawClosedPolyLine({m_frame.LeftTop(), m_frame.RightTop(), m_frame.RightDown(), m_frame.LeftDown()});
        for (const auto& shape: m_shapes)
        {
            shape->Show(canvas);
        }
    }

protected:
    std::vector<IViewPtr> ListViewsImpl() override
    {
        return m_shapes;
    }

private:
    std::vector<IViewPtr> m_shapes;
    common::Rect m_frame;
};