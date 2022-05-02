#pragma once
#include "Button.hpp"
#include "Display.hpp"

class GameObjects : public sf::Drawable
{
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    GameObjects();

    Button bStart, bStop;
    Display disp;
};