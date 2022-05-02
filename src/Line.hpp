#pragma once

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <memory>

struct ShapeFactory
{
    static std::shared_ptr<sf::Shape> createRandomShape(float radius);
};

namespace LineSettings
{
    constexpr const int MARGIN = 20, SHAPE_DIAMETER = 80, CELL_SIZE = SHAPE_DIAMETER+2*MARGIN, NUM_OF_DISPLAYED_SHAPES = 3;
    constexpr const float SPEED_LIM = 10.f, SPEEDCHANGE = 0.010f, SPEEDSLOW = SPEEDCHANGE*60;
};

class Line
{
public:
    Line();

    const sf::Sprite &getSprite() const;

    /* Create $shapeCount random shapes and move them so they line up with right spacing */
    void initShapes(size_t shapesCount);

    /* Initialize texture and fill it */
    void setTextureReady();

    // move line in global coords
    void moveSprite(float xOffset, float yOffset);

    // increment current offset of sprite texture by $yOffset
    void incTextureOffset(int yOffset);

    // set current offset of sprite texture to $yOffset
    void setTextureOffset(float yOffset);

    // set a random distance after which the line starts to slow down
    void setOffsetToStop();

    // reduce the distance needed to stop the line
    void prepareForStop();

    // set random offset and start spinning line
    void prepareToStart();

    // update the offset of the sprite and the speed at which it moves (runs every frame)
    void updateLine();

    // check if the line has stopped
    bool isStopped();

    // get shapes displayed on screen
    std::array<std::shared_ptr<sf::Shape>, LineSettings::NUM_OF_DISPLAYED_SHAPES> getDisplayedShapes();
private:
    sf::Sprite sprite;
    std::vector<std::shared_ptr<sf::Shape>> shapes;
    sf::RenderTexture texture;
    bool isSpinning, isStoped;
    float currSpeed;
    float currOffset, stopOffset;
};
