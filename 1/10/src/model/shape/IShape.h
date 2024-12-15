#pragma once

#include <string>
#include "./../common/Rect.h"
#include "./../style/fill/IFillStyle.h"
#include "./../style/line/ILineStyle.h"
#include <memory>
#include <functional>

typedef std::string ShapeType;

class IShape
{
public:
    virtual ~IShape() = default;

    virtual ShapeType GetType() = 0;

    virtual Rect GetFrame() = 0;

    virtual void SetFrame(Rect frame) = 0;

    virtual IFillStylePtr GetFillStyle() = 0;

    virtual void SetFillStyle(IFillStylePtr style) = 0;

    virtual ILineStylePtr GetLineStyle() = 0;

    virtual void SetLineStyle(ILineStylePtr style) = 0;

    virtual void RegisterObserver(const std::function<void()> &observer) = 0;
};

typedef std::shared_ptr<IShape> IShapePtr;
typedef std::shared_ptr<const IShape> ConstIShapePtr;