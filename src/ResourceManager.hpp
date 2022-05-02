#pragma once

#include <SFML/Graphics/Font.hpp>

class ResourceManager
{
public:

    bool setFont(std::string pathToFont);
    sf::Font &getFont();
    
    static ResourceManager &getInstance();
private:
    ResourceManager() = default;
    sf::Font font;
};