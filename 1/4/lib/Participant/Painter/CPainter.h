#pragma once

#include "./../Designer/CPictureDraft.h"
#include "./../../Canvas/ICanvas.h"
#include "IPainter.h"

class CPainter: public IPainter
{
public:
    void DrawPicture(const CPictureDraft& draft, gfx::ICanvas& canvas) override
    {
        for (const auto& shape : draft) {
            shape->Draw(canvas);
        }
    }
};
