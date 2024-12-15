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

        auto draftPresent = DraftPresenter({200, 200}, m_draft);

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
            }
        }

        sf::Clock clock;
        while (renderWindow.isOpen())
        {
            renderWindow.clear(sf::Color::White);
            draftPresent.GetView()->Show(canvas);
            renderWindow.display();
        }
    }

    std::shared_ptr<Draft> m_draft;
    std::shared_ptr<History> m_commandsHistory;
};