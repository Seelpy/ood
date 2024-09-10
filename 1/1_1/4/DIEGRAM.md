classDiagram

class ShapeCommandHandler{
Handle(string command)
}

class ICanvas{
SetColor(Color c)
MoveTo(double x, double y)
LineTo(double x, double y)
DrawEllipse(double cx, double cy, double rx, double ry)
DrawText(double left, double top, double fontSize, const string& text)
}

class Picture{
+AddShape(Shape shape)
+ChangeShapeStrategy(string id, IShapeStrategy strategy)
+RemoveShape(string id)
+MoveShape(string id, double dx, double dy)
+MovePicture(double dx, double dy)
+WriteShapesInfo(ostream out)
+DrawShape(string id)
}

class Shape{
+Move(double dx, double dy)
+Draw(ICanvas canvas)
+ChangeColor(string color)
+SetShapeStrategy(IShapeStrategy strategy)
-string id
}

class ShapeStrategy{
+Move(double dx, double dy)
+Draw(ICanvas canvas)
}

class IShapeStrategy{
<<interface>>
+Move(double dx, double dy)
+Draw(ICanvas canvas)
}

class TriangleStrategy{
+Draw(ICanvas canvas)
}


class CircleStrategy{
+Draw(ICanvas canvas)
}

class TriangleStrategy{
+Draw(ICanvas canvas)
}

class RectangleStrategy{
+Draw(ICanvas canvas)
}

class TextStrategy{
+Draw(ICanvas canvas)
}

class LineStrategy{
+Draw(ICanvas canvas)
}


ShapeStrategy <|-- TriangleStrategy
ShapeStrategy <|-- CircleStrategy
ShapeStrategy <|-- RectangleStrategy
ShapeStrategy <|-- LineStrategy
ShapeStrategy <|-- TextStrategy

IShapeStrategy <|.. ShapeStrategy

Shape *-- IShapeStrategy

Picture o-- Shape

ShapeCommandHandler o--Picture

ShapeStrategy --> ICanvas
Picture *-- ICanvas
