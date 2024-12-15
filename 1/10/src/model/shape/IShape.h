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
    virtual ~IShape();

    virtual ShapeType GetType();

    virtual Rect GetFrame();

    virtual void SetFrame(Rect frame);

    virtual IFillStylePtr GetFillStyle();

    virtual void SetFillStyle(IFillStylePtr style);

    virtual ILineStylePtr GetLineStyle();

    virtual void SetLineStyle(ILineStylePtr style);

    virtual void RegisterObserver(const std::function<void()> &observer);
};

typedef std::shared_ptr<IShape> IShapePtr;
typedef std::shared_ptr<const IShape> ConstIShapePtr;