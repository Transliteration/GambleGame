#include "Button.hpp"
#include <iostream>
#include "ResourceManager.hpp"

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, sf::Font &font, std::string buttonText)
: active(true)
{
    // set the color
    text.setFillColor(sf::Color::Black);
    // select the font
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    // set the string to display
    text.setString(buttonText);
    // set the character size
    text.setCharacterSize(32);
    setOriginToCenter(&text);
    text.setPosition(pos);

    rect.setSize(size);
    rect.setFillColor(sf::Color::White);
    setOriginToCenter(&rect);
    rect.setPosition(pos);
}

const sf::FloatRect Button::getGlobalBounds() const
{
    return rect.getGlobalBounds();
}

void Button::setOriginToCenter(auto *obj)
{
    sf::FloatRect shapeRectangle = obj->getLocalBounds();
    obj->setOrigin(shapeRectangle.left + shapeRectangle.width/ 2.0f,
                   shapeRectangle.top  + shapeRectangle.height/2.0f);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rect, states);
    target.draw(text, states);
}

void Button::setActive(bool active)
{
    this->active = active;
    if (active)
        text.setFillColor(sf::Color::Green);
    else
        text.setFillColor(sf::Color::Red);
}

bool Button::getActive() const
{
    return active;
}