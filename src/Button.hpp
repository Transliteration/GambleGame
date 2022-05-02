#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

#include <memory>

class Button : public sf::Drawable
{
public :
    explicit Button(const sf::Vector2f& pos
                  , const sf::Vector2f& size
                  , sf::Font &font
                  , std::string text);

    const sf::FloatRect getGlobalBounds() const;
    void setActive(bool active);
    bool getActive() const;

    Button() = default;

private :
    void setOriginToCenter(auto *obj);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape rect;
    sf::Text text;
    bool active;
};