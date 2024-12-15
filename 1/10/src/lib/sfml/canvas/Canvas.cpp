#include <cmath>
#include "Canvas.h"

const size_t CIRCLE_SHAPE_POINT_COUNT = 90;
const size_t POLYLINE_SEGMENT_VERTICES_COUNT = 5;
const unsigned int DEFAULT_CANVAS_LINE_THICKNESS = 1;
const uint32_t BACKGROUND_COLOR = 0xFFFFFFFF;

sf::Vector2f Normalized(const sf::Vector2f &source)
{
    float length = hypotf(source.x, source.y);

    if (length == 0)
    {
        return source;
    }

    return sf::Vector2f(source.x / length, source.y / length);
}

float DotProduct(const sf::Vector2f &first, const sf::Vector2f &second)
{
    return first.x * second.x + first.y * second.y;
}

Canvas::Canvas(sf::RenderTarget &target)
        : m_renderTarget(target), m_lineThickness(DEFAULT_CANVAS_LINE_THICKNESS)
{
}

void Canvas::DrawLine(const Point &from, const Point &to)
{
    auto distanceX = to.X() - from.X();
    auto distanceY = to.Y() - from.Y();
    auto angle = atan2(distanceY, distanceX);

    auto cosAngle = cos(angle);
    auto width = (distanceX != 0)
                 ? distanceX / cosAngle
                 : distanceY;

    sf::RectangleShape line(sf::Vector2f((float)std::abs(width),(float)
    m_lineThickness));
    line.setPosition({(float) from.X(), (float) from.Y()});
    line.setFillColor(m_fillColor);

    sf::Angle angleDeg = sf::radians(angle * 180 / M_PI);
    if (angle <= M_PI_2)
    {
        line.setOrigin({0, (float) m_lineThickness});

    }
    line.rotate(angleDeg);

    m_renderTarget.draw(line);
}

void Canvas::DrawClosedPolyLine(const std::vector<Point> &points)
{
    auto pointCount = points.size();

    if (pointCount < 3)
    {
        throw std::invalid_argument("Unable to draw polyline with less than 3 vertices");
    }

    for (size_t index = 0; index < pointCount; ++index)
    {
        DrawClosedPolyLineSegment(index, points);
    }

}

void Canvas::DrawClosedPolyLineSegment(size_t index, const std::vector<Point> &points)
{
    auto pointCount = points.size();
    if (pointCount <= index)
    {
        throw std::out_of_range("Polyline segment index is out of range");
    }

    sf::ConvexShape polyLineSegment;
    polyLineSegment.setPointCount(POLYLINE_SEGMENT_VERTICES_COUNT);

    auto thickness = (float) m_lineThickness / 2;

    auto prevIndex = ((index - 1) + pointCount) % pointCount;
    auto nextIndex = (index + 1) % pointCount;
    sf::Vector2f prevPoint((float) points[prevIndex].X(), (float) points[prevIndex].Y());
    sf::Vector2f currPoint((float) points[index].X(), (float) points[index].Y());
    auto lineVector = currPoint - prevPoint;
    auto normal = Normalized(sf::Vector2f(-lineVector.y, lineVector.x));
    sf::Vector2f a = prevPoint - thickness * normal;
    sf::Vector2f b = prevPoint + thickness * normal;

    sf::Vector2f nextPoint((float) points[nextIndex].X(), (float) points[nextIndex].Y());
    auto nextLineVector = nextPoint - currPoint;
    auto nextNormal = Normalized(sf::Vector2f(-nextLineVector.y, nextLineVector.x));
    sf::Vector2f nextA = currPoint - thickness * nextNormal;

    sf::Vector2f tangent = Normalized(Normalized(nextPoint - currPoint) + Normalized(currPoint - prevPoint));
    sf::Vector2f miter = sf::Vector2f(-tangent.y, tangent.x); // normal of the tangent
    float length = thickness / DotProduct(miter, normal);

    sf::Vector2f m1 = currPoint - length * miter;
    sf::Vector2f m2 = currPoint + length * miter;

    polyLineSegment.setPoint(0, a);
    polyLineSegment.setPoint(1, b);
    polyLineSegment.setPoint(2, m2);
    polyLineSegment.setPoint(3, nextA);
    polyLineSegment.setPoint(4, m1);

    polyLineSegment.setFillColor(m_lineColor);

    m_renderTarget.draw(polyLineSegment);
}

void Canvas::DrawEllipse(Rect frame)
{
    auto ellipse = sf::CircleShape((float) frame.GetSize().GetWidth() / 2, CIRCLE_SHAPE_POINT_COUNT);

    ellipse.setPosition({(float) frame.LeftTop().X(), (float) frame.LeftTop().Y()});
    ellipse.setScale({1, (float) (frame.GetSize().GetHeight() / frame.GetSize().GetWidth())});

    ellipse.setOutlineColor(m_lineColor);
    ellipse.setOutlineThickness((float) m_lineThickness);

    ellipse.setFillColor(sf::Color::Transparent);

    m_renderTarget.draw(ellipse);
}

void Canvas::FillEllipse(Rect frame)
{
    auto ellipse = sf::CircleShape((float) frame.GetSize().GetWidth() / 2, CIRCLE_SHAPE_POINT_COUNT);

    ellipse.setPosition({(float) frame.LeftTop().X(), (float) frame.LeftTop().Y()});
    ellipse.setScale({1, (float) (frame.GetSize().GetHeight() / frame.GetSize().GetWidth())});

    ellipse.setOutlineThickness(1);
    ellipse.setFillColor(m_fillColor);

    m_renderTarget.draw(ellipse);
}

void Canvas::FillPolygon(const std::vector<Point> &points)
{
    sf::ConvexShape convex;

    auto pointCount = points.size();
    convex.setPointCount(pointCount);

    for (size_t index = 0; index < pointCount; ++index)
    {
        Point point = points[index];
        convex.setPoint(index, sf::Vector2f((float) point.X(), (float) point.Y()));
    }

    convex.setFillColor(m_fillColor);

    m_renderTarget.draw(convex);
}

void Canvas::SetFillColor(uint32_t color)
{
    m_fillColor = sf::Color(color);
}

void Canvas::SetLineColor(uint32_t color)
{
    m_lineColor = sf::Color(color);
}

void Canvas::SetLineThickness(unsigned int thickness)
{
    m_lineThickness = thickness;
}

void Canvas::DrawText(const std::string &string, const Point &position)
{
    sf::Font font;
    if (!font.openFromFile("Fonts/Roboto-Regular.ttf"))
    {
        throw std::invalid_argument("Unable to load specified font");
    }
    sf::Text text(font);
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setPosition({(float)position.X(), (float)position.Y()});

    m_renderTarget.draw(text);
}

void Canvas::Capture(const std::string &outputFileName) const
{
    sf::Vector2u renderSize = m_renderTarget.getSize();
    sf::Texture texture;
    texture.resize({renderSize.x, renderSize.y});

    try
    {
        sf::RenderWindow &window = dynamic_cast<sf::RenderWindow &>(m_renderTarget);
        texture.update(window);
        sf::Image screenshot = texture.copyToImage();
        screenshot.saveToFile(outputFileName);
    }
    catch (const std::bad_cast &)
    {
        throw std::runtime_error("Unable to capture canvas with not sf::RenderWindow render target type");
    }
}