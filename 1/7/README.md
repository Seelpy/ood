classDiagram
Client o-- SlideService
ICanvas <.. Client : "Use"

    SlideService o-- IShapeFactory
    SlideService *-- ISlide

    ICanvas <|.. PNGCanvas
    ICanvas <.. IDrawable : "Use"
    ICanvas <.. SlideService : "Use"
    ICanvas <.. ISlide : "Use"

    IDrawable <|.. ISlide
    ISlide <|.. Slide
    Slide o-- IShape

    IDrawable <|.. IShape
    IShape <|.. Shape
    
    IShape <|-- IGroupShape
    IGroupShape <|.. GroupShape
    GroupShape o-- IShape
    GroupShape *-- IGroupStyle

    IStyle <|.. Style
    GroupStyle o-- IStyle
    IStyle <|-- IGroupStyle
    IGroupStyle <|.. GroupStyle

    Shape *-- IStyle
    Shape o-- RectD 
    Shape <|.. Rectangle
    Shape <|.. Ellipse
    Shape <|.. Triangle

    IShapeFactory <|.. ShapeFactory
    IShape <.. IShapeFactory : "Create"

    class Client {
        + HandleCommand(istream inputData, ICanvas canvas)
        - SlideService m_slideService
    }

    namespace CanvasNamespace {
        class ICanvas {
            + SetWidth(double width)*
            + SetHeight(double width)*
            + SetLineColor(RGBAColor color)*
            + BeginFill(RGBAColor color)*
            + EndFill()*
            + DrawLine(double fromX, double fromY, double toX, double toY)*
            + DrawEllipse(double centerX, double centerY, double radiusX, double radiusY)*
        }

        class PNGCanvas {
            + SetWidth(double width)
            + SetHeight(double width)
            + SetLineColor(RGBAColor color)
            + BeginFill(RGBAColor color)
            + EndFill()
            + DrawLine(double fromX, double fromY, double toX, double toY)
            + DrawEllipse(double centerX, double centerY, double radiusX, double radiusY)
        }

        class IDrawable {
            + Draw(ICanvas canvas)
        }
    }

    namespace SlideNamespace {
        class SlideService {
            + CreateSlide(istream inputData) ISlide
            + DrawSlide(ICanvas canvas)
        }

        class ISlide {
            + GetWidth()*
            + GetHeight()*
            + GetShapes() IShape[]
            + Draw(ICanvas canvas)
        }

        class Slide {
            + GetWidth()
            + GetHeight()
            + GetShapes() IShape[]
            + Draw(ICanvas canvas)

            - m_shapes: IShape[] 
        }
    }    

    namespace FactoryNamespace {
        class IShapeFactory {
            + CreateShape(string description) IShape
        }

        class ShapeFactory {
            + CreateShape(string description) IShape
        }
    }

    namespace StyleNamespace {

        class IGroupStyle {
            + InsertStyle(IStyle & style, size_t position = 0)
            + RemoveStyleAtIndex(size_t index)
        }

        class IStyle {
            + IsEnabled() optional<bool>*
            + Enable(bool enable)*
            + GetColor() optional<RGBAColor>*
            + SetColor(RGBAColor color)*
        }

        class Style {
            + IsEnabled() optional<bool>
            + Enable(bool enable)
            + GetColor() optional<RGBAColor>
            + SetColor(RGBAColor color)

            - optional bool  m_enabled
            - optional RGBAColor m_color
        }

        class GroupStyle {
            + IsEnabled() optional<bool>
            + Enable(bool enable)
            + GetColor() optional<RGBAColor>
            + SetColor(RGBAColor color)

            - m_enabled: bool 
            - m_color: RGBAColor 
            - m_styles: unordered_map size_t IStyle 
        }
    }

    namespace ShapeNamespace {
        class RectD {
            + left: T 
            + top: T
            + width: T 
            + height: T 
        }

        class IShape {
            + GetFrame() RectD*
            + SetFrame(const RectD & rect)*
            + GetOutlineStyle() IStyle*
            + GetFillStyle() IStyle*
        }

        class Shape {
            + GetFrame() RectD
            + SetFrame(RectD rect)
            + GetOutlineStyle() IStyle
            + GetFillStyle() IStyle

            - RectD m_frame
            - IStyle m_outlineStyle
            - IStyle m_fillStyle
        }

        class IGroupShape {
            + GetShapesCount() size_t*
            + GetShapeAtIndex(size_t index)Shape*
            + AddShape(Shape shape, size_t position)*
            + RemoveShape(size_t index)*
        }

        class GroupShape {
            + GetFrame() RectD
            + SetFrame(const RectD & rect)
            + GetLineStyle() IStyle
            + GetFillStyle() IStyle
            + GetShapesCount() size_t
            + GetShapeAtIndex(size_t index) Shape
            + AddShape(Shape shape, size_t position)
            + RemoveShape(size_t index)
            
            - unordered_map size_t, IShape m_shapes
            - IGroupStyle m_outlineStyle
            - IGroupStyle m_fillStyle
        }

        class Rectangle {
            + Draw(ICanvas canvas)
        }

        class Ellipse {
            + Draw(ICanvas canvas)
        }

        class Triangle {
            + Draw(ICanvas canvas, Color color)
        }
    }
