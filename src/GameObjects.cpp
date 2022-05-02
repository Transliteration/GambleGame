#include "GameObjects.hpp"
#include "ResourceManager.hpp"
#include <iostream>

GameObjects::GameObjects()
{
    // create buttons
    bStart = Button ({650,140}, {120, 40}, ResourceManager::getInstance().getFont(), "START");
    bStop = Button ({650,460}, {120, 40}, ResourceManager::getInstance().getFont(), "STOP");
}

void GameObjects::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(bStart, states);
    target.draw(bStop, states);
    target.draw(disp, states);
}