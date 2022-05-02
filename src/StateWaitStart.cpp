#include "StateWaitStart.hpp"

#include <iostream>


State::_state StateWaitStart::handleEvents(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<GameObjects> objectsStorage)
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
                    return start(objectsStorage);
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    [[maybe_unused]] double x, y;
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    if (objectsStorage->bStart.getGlobalBounds().contains(x, y))
                    {
                        return start(objectsStorage);
                    }
                }
            default:
                break;
        }
    }

    return State::NotChanged;
}

void StateWaitStart::update(std::shared_ptr<GameObjects> objectsStorage)
{
    objectsStorage->disp.update();
}

void StateWaitStart::onStart(std::shared_ptr<GameObjects> objectsStorage)
{
    // objectsStorage->disp.displayWinnings();
    objectsStorage->bStart.setActive(true);
    objectsStorage->bStop.setActive(false);
    std::cout << "WaitStart" << std::endl;
}

State::_state StateWaitStart::start(std::shared_ptr<GameObjects> objectsStorage)
{
    if (objectsStorage->bStart.getActive())
    {
        objectsStorage->disp.prepareToStop();
        objectsStorage->bStart.setActive(false);
        return State::GameStarted;
    }
    return State::NotChanged;
}
