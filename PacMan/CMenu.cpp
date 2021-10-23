//
//  CMenu.cpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CMenu.hpp"

CMenu::CMenu(std::vector<std::string> items, sf::Color fontColor, sf::Color activeItemColor, int fontSize)
{
    m_items = items;
    m_fontColor = fontColor;
    m_acriveItemColor = activeItemColor;
    m_fontSize = fontSize;
    m_currentItem = 0;
    if(!m_font.loadFromFile("/Users/vova/Desktop/PacMan/PacMan/PacMan/Resources/AnotherDayV2.ttf")) return EXIT_FAILURE;
}

std::vector<sf::Text> CMenu::getTextToDisplay()
{
    std::vector<sf::Text> textList;
    for(size_t i = 0; i < m_items.size(); i++)
    {
        sf::Text text;
        text.setString(m_items[i]);
        if (i == m_currentItem)
        {
            text.setFillColor(m_acriveItemColor);
        }
        else
        {
            text.setFillColor(m_fontColor);
        }
        text.setFont(m_font);
        text.setCharacterSize(m_fontSize);
        text.move(500.f, 200.f + i * 200.f);
        textList.push_back(text);
    }
    return textList;
}


void CMenu::processEvents(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code) {
            case sf::Keyboard::Down:
                goToNextMenuItem();
                break;
            case sf::Keyboard::Up:
                goToPreviousMenuItem();
                break;

            default:
                break;
        }
        
    }
}

EMenuOption CMenu::getOption()
{
    switch (m_currentItem) {
        case 0:
            return EMenuOption::RESTART;
            break;
        case 1:
            return EMenuOption::EXIT;
            
        default:
            return EMenuOption::EXIT;
            break;
    }
}


void CMenu::goToPreviousMenuItem()
{
    if (m_currentItem == 0)
    {
        m_currentItem = m_items.size() - 1;
    }
    else
    {
        --m_currentItem;
    }
}

void CMenu::goToNextMenuItem()
{
    ++m_currentItem;
    if (m_currentItem == m_items.size())
    {
        m_currentItem = 0;
    }
}
