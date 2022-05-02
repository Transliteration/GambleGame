#include "Line.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


#include <iostream>

using namespace LineSettings;

std::shared_ptr<sf::Shape> ShapeFactory::createRandomShape(float radius)
{
    int rand = std::rand()%15;
    std::shared_ptr<sf::Shape> shape;
    switch (rand)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        shape = std::make_shared<sf::CircleShape>(sf::CircleShape(radius, 3));
        shape->setFillColor(sf::Color::Blue);
        break;
    case 4:
    case 5:
    case 6:
        shape = std::make_shared<sf::CircleShape>(sf::CircleShape(radius, 4));
        shape->setFillColor(sf::Color::Green);
        break;
    case 7:
    case 8:
        shape = std::make_shared<sf::CircleShape>(sf::CircleShape(radius, 30));
        shape->setFillColor(sf::Color::Red);
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        shape = std::make_shared<sf::RectangleShape>(sf::RectangleShape({radius*2.f, radius*2.f}));
        shape->setFillColor(sf::Color::White);
        break;
    
    default:
        std::cerr << "In ShapeFactory::createRandomShape: default constructed shape returned." << std::endl;
        break;
    }

    return shape;    
}

Line::Line() 
: isSpinning(false)
, isStoped(true)
, currSpeed(0)
, currOffset(0)
, stopOffset(10'000)
{
    setOffsetToStop();
}

const sf::Sprite &Line::getSprite() const
{
    return sprite;
}

void Line::initShapes(size_t shapesCount)
{
    for (size_t i = 0; i < shapesCount; i++)
    {
        shapes.push_back(ShapeFactory::createRandomShape(SHAPE_DIAMETER/2));
        shapes[i]->move(MARGIN/2, CELL_SIZE*i+MARGIN);
    }
}

void Line::setTextureReady()
{
    texture.create(CELL_SIZE, CELL_SIZE*shapes.size());
    // draw shapes on texture
    for (auto &&shape : shapes)
    {
        texture.draw(*shape.get());
    }

    // draw line
    sf::Vertex line[2];
    line[0].position = sf::Vector2f(1, 0);
    line[0].color  = sf::Color::White;
    line[1].position = sf::Vector2f(1, CELL_SIZE*shapes.size());
    line[1].color = sf::Color::White;
    texture.draw(line, 2, sf::Lines);

    texture.setRepeated(true);

    sprite.setTexture(texture.getTexture());
    sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE*NUM_OF_DISPLAYED_SHAPES));
}

void Line::moveSprite(float xOffset, float yOffset)
{
    sprite.move(xOffset, yOffset);
}

void Line::incTextureOffset(int yOffset)
{
    auto intRect = sprite.getTextureRect();
    intRect.top += yOffset;
    sprite.setTextureRect(intRect);
}

void Line::setTextureOffset(float yOffset)
{
    auto intRect = sprite.getTextureRect();
    intRect.top = yOffset;
    // currOffset = yOffset;
    sprite.setTextureRect(intRect);
}

void Line::setOffsetToStop()
{
    stopOffset = currOffset + 200*SPEED_LIM + std::rand() % (150*(int)SPEED_LIM);
}

void Line::prepareForStop()
{
    float newStopOffset = currOffset + CELL_SIZE*(std::rand() % 8 + 2);
    // if line already stopped or close to it, dont change offset 
    if (newStopOffset < stopOffset)
        stopOffset = newStopOffset;
}

void Line::prepareToStart()
{
    setOffsetToStop();
    isSpinning = true;
    isStoped = false;
}

void Line::updateLine()
{
    
    if (isSpinning && currOffset < stopOffset) 
    {
        // raise speed till maximum speed is reached
        currSpeed += SPEEDCHANGE;
        if (currSpeed > SPEED_LIM) currSpeed = SPEED_LIM;
    }
    else if (!isStoped)
    {
        // check if the line rotates slowly and the line is close to the correct position to stop
        if (currSpeed < SPEEDSLOW && (int)currOffset % CELL_SIZE >= CELL_SIZE-std::max(SPEEDSLOW*3, 1.f))
        {
            // if so stop spinning and set correct offset
            currSpeed = 0;
            currOffset += CELL_SIZE - (int)currOffset%CELL_SIZE;
            currOffset = (int)currOffset % ((shapes.size())*CELL_SIZE);
            isStoped = true;
            isSpinning = false;
            // std::cout << currOffset << std::endl;
            setTextureOffset(currOffset);
            setOffsetToStop();
            return;
        }
        // else decrease rotation speed 
        else if (currSpeed >= SPEEDSLOW)
        {
            if (currSpeed > SPEEDSLOW) currSpeed -= SPEEDCHANGE;
            if (currSpeed < 0) currSpeed = 0; // probably not needed
        }
        
    }
    // update position
    currOffset += currSpeed;
    // update texture offset
    setTextureOffset(currOffset);
}

bool Line::isStopped()
{
    return isStoped;
}

std::array<std::shared_ptr<sf::Shape>, NUM_OF_DISPLAYED_SHAPES> Line::getDisplayedShapes()
{
    std::array<std::shared_ptr<sf::Shape>, NUM_OF_DISPLAYED_SHAPES> ret;
    
    if (!isStoped) std::cerr << "ERROR: Line::getDisplayedShapes() was called before all lines was stopped." << std::endl;

    for (int i = 0; i < NUM_OF_DISPLAYED_SHAPES; i++)
    {
        int index = (int)(shapes.size()*2 - 1 - i - currOffset/CELL_SIZE)%shapes.size();
        // std::cout << index << std::endl;
        ret[i] = shapes[index];
    }
    
    return ret;
}

