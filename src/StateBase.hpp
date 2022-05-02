#pragma once

#include <memory>

#include "GameObjects.hpp"
// #include "ResourceManager.hpp"
#include <SFML/Window/Event.hpp>

namespace State
{
    enum _state
    {
        NotChanged = -1,
        WaitStart, 
        GameEnd, 
        GameStarted, 
        _size
    };
}


class StateBase
{
public:
    virtual State::_state handleEvents(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<GameObjects> objectsStorage) = 0;
    virtual void update(std::shared_ptr<GameObjects> objectsStorage) = 0;
    virtual void onStart(std::shared_ptr<GameObjects> objectsStorage) = 0;
    virtual ~StateBase() = default;
    StateBase() = default;
};