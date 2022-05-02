#include "Game.hpp"

#include <iostream>

#include "ResourceManager.hpp"

Game::Game(std::shared_ptr<sf::RenderWindow> window)
: window(window)
, objectsStorage(std::make_shared<GameObjects>())
{
    
}

void Game::run()
{
    sm.getCurrentState()->onStart(objectsStorage);
    // run the program as long as the window is open
    while (window->isOpen())
    {
        State::_state next_state = sm.getCurrentState()->handleEvents(window, objectsStorage);
        if (next_state != State::NotChanged)
        {
            sm.setCurrentState(next_state);
            sm.getCurrentState()->onStart(objectsStorage);
        }
        sm.getCurrentState()->update(objectsStorage);
        drawScene();
    }
}


void Game::drawScene() const
{
    window->clear(sf::Color::Black);
    window->draw(*objectsStorage);
    window->display();
}