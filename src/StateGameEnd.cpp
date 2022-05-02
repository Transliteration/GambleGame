#include "StateGameEnd.hpp"

#include <iostream>

State::_state StateGameEnd::handleEvents(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<GameObjects> objectsStorage)
{   
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window->pollEvent(event))
    {
        // check the type of the event...
        switch (event.type)
        {
            // window closed
            case sf::Event::Closed:
                window->close();
                break;

            // key pressed
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                else if (event.key.code == sf::Keyboard::Space)
                    return startNewGame(objectsStorage);
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    [[maybe_unused]] double x, y;
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    if (objectsStorage->disp.getOkButton().getGlobalBounds().contains(x,y))
                    {
                        return startNewGame(objectsStorage);
                    }
                }
            default:
                break;
        }
    }

    return State::NotChanged;
}

void StateGameEnd::update(std::shared_ptr<GameObjects> objectsStorage)
{
    objectsStorage->disp.update();
}

void StateGameEnd::onStart(std::shared_ptr<GameObjects> objectsStorage)
{
    // std::cout << "GameEnd" << std::endl;
    objectsStorage->disp.displayWinnings();
}

State::_state StateGameEnd::startNewGame(std::shared_ptr<GameObjects> objectsStorage)
{
    objectsStorage->disp.bOkHandle();
    return State::WaitStart;
}