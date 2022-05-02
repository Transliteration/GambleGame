#pragma once

#include "StateMachine.hpp"

// handles drawing on window all game information
// contains game objects, game state 
class Game
{
public:
    StateMachine sm;
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<GameObjects> objectsStorage;
    Game(std::shared_ptr<sf::RenderWindow> window);

    void run();
    void drawScene() const;
    
};