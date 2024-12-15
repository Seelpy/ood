#pragma once

#include "./../IView.h"
#include <vector>

class DraftView : public IView
{
public:
    DraftView(Rect frame, std::vector<IViewPtr> shapes) : m_shapes(shapes), m_frame(frame)
    {

    }

    void Show(ICanvas &canvas)
    {
        canvas.DrawClosedPolyLine({m_frame.LeftTop(), m_frame.RightTop(), m_frame.RightDown(), m_frame.LeftDown()});
        for (auto shape: m_shapes)
        {
            shape->Show(canvas);
        }
    }

private:
    std::vector<IViewPtr> m_shapes;
    Rect m_frame;
};