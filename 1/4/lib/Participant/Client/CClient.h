#pragma once

#include "./../../Canvas/ICanvas.h"
#include "./../Painter//IPainter.h"
#include "./../Designer/IDesigner.h"

class Client
{
public:
    void DrawPicture(std::istream &inputData, gfx::ICanvas &canvas, IDesigner &designer, IPainter &painter)
    {
        CPictureDraft pictureDraft = designer.CreateDraft(inputData);

        painter.DrawPicture(pictureDraft, canvas);
    }
};