//
//  CMenu.hpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CMenu_hpp
#define CMenu_hpp

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

enum EMenuOption
{
    RESTART = 1,
    EXIT = 0
};

class CMenu
{
public:
    CMenu(std::vector<std::string> items, sf::Color fontColor = sf::Color::White, sf::Color activeItemColor = sf::Color::Green, int fontSize = 150);
    std::vector<sf::Text> getTextToDisplay();
    
    void processEvents(const sf::Event& event);
    EMenuOption getOption();
private:
    sf::Color m_fontColor;
    sf::Color m_acriveItemColor;
    int m_fontSize;
    std::vector<std::string> m_items;
    int m_currentItem;
    sf::Font m_font;
    
    void goToNextMenuItem();
    void goToPreviousMenuItem();
};

#endif /* CMenu_hpp */
