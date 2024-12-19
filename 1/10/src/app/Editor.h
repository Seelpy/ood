#pragma once

#include "./../model/draft/Draft.h"
#include "./../model/shape/Shape.h"
#include "./../model/style/fill/FIllStyle.h"
#include "./../model/style/line//LineStyle.h"
#include "./../lib/command/History.h"
#include "./../lib/common/Point.h"
#include "./../lib/sfml/canvas/Canvas.h"
#include "./../presenter/draft/Draft.h"
#include "./../presenter/button/Button.h"
#include "../presenter/editor/Editor.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

class Editor
{
public:
    Editor(IDraftPtr draft): m_draft(std::move(draft))
    {

    }

    void Run()
    {
        InitEditWindow();
    }
// Shapes View
private:
    void InitEditWindow()
    {
        m_commandsHistory = std::make_shared<History>();

        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8;
        auto renderWindow = sf::RenderWindow(
                sf::VideoMode({m_draft->GetSize().GetWidth(), m_draft->GetSize().GetHeight()}), "ShapesEditor",
                sf::Style::Default, sf::State::Windowed, settings);
        auto canvas = Canvas(renderWindow);

        auto draftPresent = DraftPresenter({0, 0}, m_draft);
        auto view = draftPresent.GetView();

        auto buttonPresenter1 = std::make_shared<ButtonPresenter>(common::Rect{{0, 950}, {100, 30}}, std::make_shared<FillStyle>(100), std::make_shared<LineStyle>(100, 5), "Ellipse", [](){std:: cout << "Ellipse" << std::endl;});
        auto buttonPresenter2 = std::make_shared<ButtonPresenter>(common::Rect{{200, 950}, {100, 30}}, std::make_shared<FillStyle>(100), std::make_shared<LineStyle>(100, 5), "Square", [](){std:: cout << "Square" << std::endl;});
        auto buttonPresenter3 = std::make_shared<ButtonPresenter>(common::Rect{{400, 950}, {100, 30}}, std::make_shared<FillStyle>(100), std::make_shared<LineStyle>(100, 5), "Triangle", [](){std:: cout << "Triangle" << std::endl;});
        auto menuButtons = {buttonPresenter1, buttonPresenter2, buttonPresenter3};
        auto menu = std::make_shared<MenuPresenter>(menuButtons);

        auto editorPresenter = EditorPresenter(draftPresent.GetView(), menu->GetView());
        auto editorView = editorPresenter.GetView();

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
                    common::Point p = common::Point{(unsigned int)mouseEvent->position.x, (unsigned int)mouseEvent->position.y};
                    m_pressedMousePoint = p;
                    editorView->OnMouseDown(p);
                }
                if (event->is<sf::Event::MouseButtonReleased>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonReleased>();
                    if (m_pressedMousePoint.has_value())
                    {
                        auto p1 = m_pressedMousePoint.value();
                        auto pRaw = sf::Mouse::getPosition(renderWindow);
                        auto p2 = common::Point{(unsigned int) pRaw.x, (unsigned int )pRaw.y};
                        editorView->OnMouseDrag(p1, p2);
                    }
                    m_pressedMousePoint = std::nullopt;
                    editorView->OnMouseUp(common::Point{(unsigned int)mouseEvent->position.x, (unsigned int)mouseEvent->position.y});

                }
            }
            renderWindow.clear(sf::Color::White);
            editorView->Show(canvas);
            renderWindow.display();
        }
    }

    IDraftPtr m_draft;
    std::shared_ptr<History> m_commandsHistory;
    std::optional<common::Point> m_pressedMousePoint;
};