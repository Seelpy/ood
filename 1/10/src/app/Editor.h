#pragma once

#include "./../model/draft/Draft.h"
#include "./../model/shape/Shape.h"
#include "./../model/style/fill/FIllStyle.h"
#include "./../model/style/line//LineStyle.h"
#include "./../presenter/command/History.h"
#include <SFML/Graphics.hpp>
#include "./../model/common/Point.h"
#include "./../lib/sfml/canvas/Canvas.h"
#include "./../presenter/draft/Draft.h"

class Editor
{
public:
    Editor()
    {

    }

    void Run()
    {
        InitEditWindow();
    }

private:
    void InitEditWindow()
    {
        m_draft = std::make_shared<Draft>(Size{500, 500});
        m_draft->AddShape(std::make_shared<Shape>("circle", Rect{{100, 100}, {50, 50}}, std::make_shared<LineStyle>(100, 1), std::make_shared<FillStyle>(100)));
        m_commandsHistory = std::make_shared<History>();

        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8;
        auto renderWindow = sf::RenderWindow(
                sf::VideoMode({m_draft->GetSize().GetWidth(), m_draft->GetSize().GetHeight()}), "ShapesEditor",
                sf::Style::Default, sf::State::Windowed, settings);
        auto canvas = Canvas(renderWindow);

        auto draftPresent = DraftPresenter({0, 0}, m_draft);
        auto view = draftPresent.GetView();

        sf::Clock clock;
        while (renderWindow.isOpen())
        {
            while (true)
            {
                auto event = renderWindow.pollEvent();
                if (!event.has_value())
                {
                    break;
                }
                if (event->is<sf::Event::Closed>())
                {
                    renderWindow.close();
                    break;
                }
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    Point p = Point{(unsigned int)mouseEvent->position.x, (unsigned int)mouseEvent->position.y};
                    m_pressedMousePoint = p;
                    view->OnMouseDown(p);
                }
                if (event->is<sf::Event::MouseButtonReleased>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonReleased>();
                    if (m_pressedMousePoint.has_value())
                    {
                        auto p1 = m_pressedMousePoint.value();
                        auto pRaw = sf::Mouse::getPosition(renderWindow);
                        auto p2 = Point{(unsigned int) pRaw.x, (unsigned int )pRaw.y};
                        view->OnMouseDrag(p1, p2);
                    }
                    m_pressedMousePoint = std::nullopt;
                    view->OnMouseUp(Point{(unsigned int)mouseEvent->position.x, (unsigned int)mouseEvent->position.y});

                }
            }
            renderWindow.clear(sf::Color::White);
            view->Show(canvas);
            renderWindow.display();
        }
    }

    std::shared_ptr<Draft> m_draft;
    std::shared_ptr<History> m_commandsHistory;
    std::optional<Point> m_pressedMousePoint;
};