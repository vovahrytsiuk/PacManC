#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.hpp"
#include "CGame.hpp"
int main()
{
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(NSConfig::kScreenWidth, NSConfig::kScreenHeight), NSConfig::kTitle);
    window.setFramerateLimit(30);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    CGame game(window);

    while (window.isOpen())
    {
        game.processEvents();

        window.clear();
        //window.draw(shape);
        
        game.draw();
        game.gameLogic();
        window.display();
    }
    return 0;
}
