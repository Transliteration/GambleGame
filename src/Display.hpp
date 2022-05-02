#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

#include <iostream>

#include "Line.hpp"
#include "Button.hpp"


namespace DisplaySettings
{
    static const int SHAPES_COUNT_IN_EACH_LINE = 30,
                     LINES_COUNT = 5;
};

// handles displaying slot machine lines and updating internal logic of each line
class Display : public sf::Drawable
{
public:
    Display();
    // calls update function on each line
    void update();
    // set random offset and start spinning all lines
    void startSpinning();
    // reduce the distance needed to stop all lines
    void prepareToStop();
    // calculate winnings
    void displayWinnings();
    // check if all lines has stopped
    bool isStopped();

    void bOkHandle();
    const Button &getOkButton();
private:
    void initResultTable();
    std::array<Line, DisplaySettings::LINES_COUNT> lines;
    sf::RectangleShape outline; // rectangle to draw outline
    struct 
    {
        sf::RectangleShape window; // table to show spin result
        Button bOk;
        sf::Text winText;
        bool isHidden;
    }resultTable;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};