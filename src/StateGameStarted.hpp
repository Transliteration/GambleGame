#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "StateBase.hpp"


class StateGameStarted : public StateBase
{
    bool stopped;
public:

    virtual State::_state handleEvents(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<GameObjects> objectsStorage);
    virtual void update(std::shared_ptr<GameObjects> objectsStorage);
    virtual void onStart(std::shared_ptr<GameObjects> objectsStorage);
    void forceStop(std::shared_ptr<GameObjects> objectsStorage);
};