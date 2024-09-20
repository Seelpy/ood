classDiagram

class ICanvas{
SetColor(Color c)
MoveTo(double x, double y)
LineTo(double x, double y)
DrawEllipse(double cx, double cy, double rx, double ry)
DrawText(double left, double top, double fontSize, const string& text)
}

namespace shapes {

class Picture{
+AddShape(Shape shape)
+ChangeShapeStrategy(string id, IShapeStrategy strategy)
+DeleteShape(string id)
+MoveShape(string id, double dx, double dy)
+MovePicture(double dx, double dy)
+PrintShapesInfo()
+DrawShape(string id)

-vector shapes
}

class Shape{
+Move(double dx, double dy)
+Draw(ICanvas canvas)
+ChangeColor(string color)
+SetShapeStrategy(IShapeStrategy strategy)
-string id
-string color
-IShapeStrategy strategy
}


class IShapeStrategy{
<<interface>>
+GetType() StrategyType
+Draw(ICanvas canvas, string color)
+Move(double dx, double dy)
+GetShapeInfo() string
+Clone() IShapeStrategy
}

class CircleStrategy{
+GetType() StrategyType
+Draw(ICanvas canvas, string color)
+Move(double dx, double dy)
+GetShapeInfo() string
+Clone() IShapeStrategy

-Point center
-double r
}

class TriangleStrategy{
+GetType() StrategyType
+Draw(ICanvas canvas, string color)
+Move(double dx, double dy)
+GetShapeInfo() string
+Clone() IShapeStrategy

-Point p1, p2, p3
}

class RectangleStrategy{
+GetType() StrategyType
+Draw(ICanvas canvas, string color)
+Move(double dx, double dy)
+GetShapeInfo() string
+Clone() IShapeStrategy

-Point leftTop
-double w, h
}

class TextStrategy{
+GetType() StrategyType
+Draw(ICanvas canvas, string color)
+Move(double dx, double dy)
+GetShapeInfo() string
+Clone() IShapeStrategy

-Point leftTop
-double fontSize
-string text
}

class LineStrategy{
+GetType() StrategyType
+Draw(ICanvas canvas, string color)
+Move(double dx, double dy)
+GetShapeInfo() string
+Clone() IShapeStrategy

-Point p1, p2
}

}



IShapeStrategy <|.. TriangleStrategy
IShapeStrategy <|.. CircleStrategy
IShapeStrategy <|.. RectangleStrategy
IShapeStrategy <|.. LineStrategy
IShapeStrategy <|.. TextStrategy

Shape *-- IShapeStrategy

IShapeStrategy ..> ICanvas

Picture *-- Shape
Picture ..> Shape
Picture ..> IShapeStrategy

Picture ..> ICanvas
