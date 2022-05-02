#include "ResourceManager.hpp"

ResourceManager& ResourceManager::getInstance()
{
  static ResourceManager s;
  return s;
}

bool ResourceManager::setFont(std::string pathToFont)
{
    static sf::Font newFont;
    if (newFont.loadFromFile("materials/" + pathToFont))
    {
        font = newFont;
        return true;
    }
    return false;
}

sf::Font &ResourceManager::getFont()
{
    return font;
}