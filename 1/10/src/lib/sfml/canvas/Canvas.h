#pragma once

#include "./../../../view/canvas/ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas
{
public:
    explicit Canvas(sf::RenderTarget &target);

    void DrawLine(const common::Point &from, const common::Point &to) override;

    void DrawClosedPolyLine(const std::vector<common::Point> &) override;

    void DrawEllipse(common::Rect frame) override;

    void FillEllipse(common::Rect frame) override;

    void FillPolygon(const std::vector<common::Point> &) override;

    void SetFillColor(uint32_t) override;

    void SetLineColor(uint32_t) override;

    void SetLineThickness(unsigned int) override;

    void DrawText(const std::string &, const common::Point &position) override;

    void Capture(const std::string &outputFileName) const;

private:
    void DrawClosedPolyLineSegment(size_t index, const std::vector<common::Point> &points);

    sf::Color m_lineColor = sf::Color::White;
    sf::Color m_fillColor = sf::Color::Black;
    sf::Color m_backgroundColor;
    unsigned int m_lineThickness;
    sf::RenderTarget &m_renderTarget;
    sf::Font m_font;
};