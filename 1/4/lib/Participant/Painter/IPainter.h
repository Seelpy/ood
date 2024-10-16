#pragma once

#include "./../Designer/CPictureDraft.h"
#include "./../../Canvas/ICanvas.h"

class IPainter
{
public:
    virtual void DrawPicture(const CPictureDraft& draft, gfx::ICanvas& canvas) = 0;

    virtual ~IPainter() = default;
};