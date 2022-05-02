#include "Display.hpp"

#include "ResourceManager.hpp"

using namespace LineSettings;
using namespace DisplaySettings;

Display::Display()
{
    int count = 0;
    for (auto &&line : lines)
    {
        line.initShapes(SHAPES_COUNT_IN_EACH_LINE);
        line.setTextureReady();

        line.moveSprite(40 + (SHAPE_DIAMETER + MARGIN)*count, 120);
        count++;
    }

    outline.setFillColor(sf::Color::Black);
    outline.setOutlineThickness(1);
    outline.setOutlineColor(sf::Color::White);
    outline.move(40, 120);
    outline.setSize({(SHAPE_DIAMETER+MARGIN)*LINES_COUNT, CELL_SIZE*NUM_OF_DISPLAYED_SHAPES});

    initResultTable();
}

void Display::update()
{
    for (auto &&line : lines)
    {
        line.updateLine();
    }
}

void Display::startSpinning()
{
    for (auto &&line : lines)
    {
        line.prepareToStart();
    }
}

void Display::prepareToStop()
{
    for (auto &&line : lines)
    {
        line.prepareForStop();
    }
}

void Display::displayWinnings()
{
    std::array<std::array<std::shared_ptr<sf::Shape>, NUM_OF_DISPLAYED_SHAPES>, DisplaySettings::LINES_COUNT> shapeTable;
    std::array<std::shared_ptr<sf::Shape>, LINES_COUNT> row;
    float totalWin = 0.f;
    float prizeForComlitedRow = 10.f;

    // fill shapeTable
    for (size_t i = 0; i < DisplaySettings::LINES_COUNT; i++)
    {
        shapeTable[i] = lines[i].getDisplayedShapes();
    }
    
    // start looking for win rows 
    for (size_t i = 0; i < NUM_OF_DISPLAYED_SHAPES; i++)
    {
        // may be replaced with other checks (here only for horizontal lines)
        for (size_t j = 0; j < LINES_COUNT; j++)
        {
            row[j] = shapeTable[j][i];
        }

        sf::Color prevColor = row[0]->getFillColor();
        bool isRowCompleted = true;

        for (size_t j = 1; j < LINES_COUNT; j++)
        {
            // white square is wildcard
            if (prevColor == sf::Color::White)
                prevColor = row[j]->getFillColor();
            if (row[j]->getFillColor() != sf::Color::White && row[j]->getFillColor() != prevColor)
            {
                isRowCompleted = false;
                break;
            }
        }

        if (isRowCompleted)
        {
            totalWin += prizeForComlitedRow;
        }
        
    }

    { // prepare to show win info
        auto totalWin_s = std::to_string(totalWin);
        auto indexOfPoint = totalWin_s.find('.');
        totalWin_s = totalWin_s.substr(0, indexOfPoint + 3);
        resultTable.winText.setString("You have won: " + totalWin_s);
    }

    resultTable.isHidden = false;
}

bool Display::isStopped()
{
    for (auto &&line : lines)
    {
        if (!line.isStopped()) return false;
    }
    return true;
}

void Display::bOkHandle()
{
    resultTable.isHidden = true;
}

const Button &Display::getOkButton()
{
    return resultTable.bOk;
}

void Display::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(outline, states);
    
    for (auto &&line : lines)
    {
        target.draw(line.getSprite(), states);
    }

    if (!resultTable.isHidden)
    {
        target.draw(resultTable.window, states);
        target.draw(resultTable.bOk, states);
        target.draw(resultTable.winText, states);
    }
}

void Display::initResultTable()
{
    auto &[window, bOk, winText, isHidden] = resultTable;

    isHidden = true;

    window.setOutlineColor({50, 50, 255});
    window.setFillColor({220, 220, 255});
    window.setOutlineThickness(5);
    window.setSize({300, 150});
    window.setOrigin(150, 75);
    {
        auto [x, y] = outline.getPosition();
        auto [w, h] = outline.getSize();
        window.setPosition(x+w/2, y+h/2);
        bOk = Button({x+w/2, y+h/2+20}, {80, 40}, ResourceManager::getInstance().getFont(), "OK");
    }

    {
        auto rect = window.getGlobalBounds();
        winText.setFont(ResourceManager::getInstance().getFont());
        winText.setString("You have won: ");
        winText.setCharacterSize(26);
        winText.setFillColor({0,0,0});
        winText.setStyle(sf::Text::Bold);
        winText.setPosition(rect.left+20, rect.top+20);
    }

    bOk.setActive(true);
}