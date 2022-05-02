#include "StateGameStarted.hpp"

#include <iostream>

State::_state StateGameStarted::handleEvents(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<GameObjects> objectsStorage)
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
                {
                    forceStop(objectsStorage);

                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    [[maybe_unused]] double x, y;
                    x = event.mouseButton.x;
                    y = event.mouseButton.y;
                    if (objectsStorage->bStop.getGlobalBounds().contains(x, y))
                    {
                        // objectsStorage->disp.prepareToStop();
                        // return State::GameEnd;
                        forceStop(objectsStorage);
                    }
                }
            default:
                break;
        }
    }
    if (stopped) return State::GameEnd;
    return State::NotChanged;
}

void StateGameStarted::update(std::shared_ptr<GameObjects> objectsStorage)
{
    objectsStorage->disp.update();
    if (objectsStorage->disp.isStopped())
    {
        stopped = true;
        objectsStorage->bStop.setActive(false);
    }

}

void StateGameStarted::onStart(std::shared_ptr<GameObjects> objectsStorage)
{
    stopped = false;
    objectsStorage->disp.startSpinning();
    objectsStorage->bStart.setActive(false);
    objectsStorage->bStop.setActive(true);
    std::cout << "GameStarted" << std::endl;
}

void StateGameStarted::forceStop(std::shared_ptr<GameObjects> objectsStorage)
{
    if (objectsStorage->bStop.getActive())
    {
        objectsStorage->disp.prepareToStop();
        objectsStorage->bStop.setActive(false);

    }
}
