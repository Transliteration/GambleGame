#include "main.hpp"

int main()
{
    // create the window
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Application");

    window->setFramerateLimit(240);
    
    std::srand(std::time(nullptr));

    // Load font for buttons
    auto &rm = ResourceManager::getInstance();
    if (!rm.setFont("UbuntuMono-B.ttf"))
        std::cerr << "ERROR: font was not loaded (probably wrong path)." << std::endl;

    Game game(window);
    game.run();

    return 0;
}