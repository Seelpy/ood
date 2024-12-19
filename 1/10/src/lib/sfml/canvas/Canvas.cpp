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
    if (!m_font.openFromFile("/Users/maksimveselov/Projects/ood/1/10/src/lib/sfml/font/Roboto-Regular.ttf"))
    {
        throw std::invalid_argument("Unable to load specified font");
    }
}

void Canvas::DrawLine(const common::Point &from, const common::Point &to)
{
    sf::VertexArray line(sf::PrimitiveType::Lines, 2);
    line[0].position = sf::Vector2f(static_cast<float>(from.X()), static_cast<float>(from.Y()));
    line[1].position = sf::Vector2f(static_cast<float>(to.X()), static_cast<float>(to.Y()));
    line[0].color = sf::Color(m_fillColor);
    line[1].color = sf::Color(m_fillColor);

    m_renderTarget.draw(line);
}

void Canvas::DrawClosedPolyLine(const std::vector<common::Point> &points)
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

void Canvas::DrawClosedPolyLineSegment(size_t index, const std::vector<common::Point> &points)
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

void Canvas::DrawEllipse(common::Rect frame)
{
    auto ellipse = sf::CircleShape((float) frame.GetSize().GetWidth() / 2, CIRCLE_SHAPE_POINT_COUNT);

    ellipse.setPosition({(float) frame.LeftTop().X(), (float) frame.LeftTop().Y()});
    ellipse.setScale({1, (float) (frame.GetSize().GetHeight() / frame.GetSize().GetWidth())});

    ellipse.setOutlineColor(m_lineColor);
    ellipse.setOutlineThickness((float) m_lineThickness);

    ellipse.setFillColor(sf::Color::Transparent);

    m_renderTarget.draw(ellipse);
}

void Canvas::FillEllipse(common::Rect frame)
{
    auto ellipse = sf::CircleShape((float) frame.GetSize().GetWidth() / 2, CIRCLE_SHAPE_POINT_COUNT);

    ellipse.setPosition({(float) frame.LeftTop().X(), (float) frame.LeftTop().Y()});
    ellipse.setScale({1,  ((float) frame.GetSize().GetHeight() / frame.GetSize().GetWidth())});

    ellipse.setOutlineThickness(1);
    ellipse.setFillColor(m_fillColor);

    m_renderTarget.draw(ellipse);
}

void Canvas::FillPolygon(const std::vector<common::Point> &points)
{
    sf::ConvexShape convex;

    auto pointCount = points.size();
    convex.setPointCount(pointCount);

    for (size_t index = 0; index < pointCount; ++index)
    {
        common::Point point = points[index];
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

void Canvas::DrawText(const std::string &string, const common::Point &position)
{
    sf::Text text(m_font);
    text.setFont(m_font);
    text.setString(string);
    text.setCharacterSize(16);
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