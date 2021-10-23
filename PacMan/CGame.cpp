//
//  CGame.cpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CGame.hpp"
#include <iostream>

namespace {
const int kBFS = 0;
const int kDFS = 1;
const int kUCS = 2;
const int kAlgorithmCount = 3;
const std::string kBFSName = "BFS";
const std::string kDFSName = "DFS";
const std::string kUCSName = "UCS";
}



CGame::CGame(sf::RenderWindow& window) : m_Menu(CMenu(NSConfig::kMenuItems)), m_Window(window), m_IsGameOver(false), m_Field(NSConfig::kColumnNumber, NSConfig::kRowNumber), m_PacMan(m_Field.getRandomPosition()), m_Wall(CWall()), m_FoodBoard(m_Field), m_Graph(m_Field), m_Algorithm(kBFS)
{
    m_SpiritList.push_back(CSpirit(m_Field.getRandomPosition()));
    //m_SpiritList.push_back(CSpirit(m_Field.getRandomPosition()));
    //m_SpiritList.push_back(CSpirit(m_Field.getRandomPosition()));
    m_Score = 0;
}

void CGame::displayMenu()
{
    for(const auto& textItem : m_Menu.getTextToDisplay())
    {
        m_Window.draw(textItem);
    }
}

void CGame::processEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        switch (event.type) {
            case sf::Event::Closed:
                m_Window.close();
                break;
            case sf::Event::KeyPressed:
                processKeyPressed(event);
                break;
                
            default:
                break;
        }
    }
}

void CGame::processKeyPressed(const sf::Event& event)
{
    if (m_IsGameOver == true)
    {
        if (event.key.code == sf::Keyboard::Enter)
        {
            switch (m_Menu.getOption()) {
                case EMenuOption::RESTART:
                    // restart game
                    restartGame();
                    break;
                case EMenuOption::EXIT:
                    m_Window.close();
                    break;
                    
                default:
                    break;
            }        }
        else
        {
            m_Menu.processEvents(event);
        }
    }
    else
    {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                m_IsGameOver = true;
                break;
            case sf::Keyboard::Down:
                // move player
                m_PacMan.updateDirection(0, 1);
                break;
            case sf::Keyboard::Up:
                // move player
                m_PacMan.updateDirection(0, -1);
                break;
            case sf::Keyboard::Right:
                //move player
                m_PacMan.updateDirection(1, 0);
                break;
            case sf::Keyboard::Left:
                //move player
                m_PacMan.updateDirection(-1, 0);
                break;
            case sf::Keyboard::Z:
                switchAlgorithm();
                break;
                
            default:
                break;
        }
    }
}


void CGame::draw()
{
    if (m_IsGameOver == true)
    {
        displayMenu();
    }
    else
    {
        drawField();
        drawSortestPath();
        drawPacMan();
        drawSpirits();
        displayScoreAndAlgorithm();
    }
}

namespace{
const int kFoodRadius = 10;
const float offset = (NSConfig::kBlockSize - kFoodRadius) / 2;
}

void CGame::drawField()
{
    sf::Sprite wallSprite = m_Wall.getSprite();
    sf::CircleShape circle;
    circle.setRadius(kFoodRadius);
    circle.setFillColor(sf::Color::White);
    for(int row = 0; row < NSConfig::kRowNumber; row++)
    {
        for(int column = 0; column < NSConfig::kColumnNumber; column++)
        {
            if (m_Field.verifyBlockType(row, column, NSConfig::kWall) == true)
            {
                wallSprite.setPosition(column * NSConfig::kBlockSize, row * NSConfig::kBlockSize);
                m_Window.draw(wallSprite);
            }
            if (m_FoodBoard.isFoodPresent(row, column))
            {
                circle.setPosition(float(column * NSConfig::kBlockSize + offset), float(row * NSConfig::kBlockSize + offset));
                m_Window.draw(circle);
                
            }
        }
    }
}

void CGame::drawPacMan()
{
    m_Window.draw(m_PacMan.getSprite());
}

void CGame::drawSpirits()
{
    for(size_t i = 0; i < m_SpiritList.size(); i++)
    {
        m_Window.draw(m_SpiritList[i].getSprite());
    }
}


void CGame::gameLogic()
{
    m_PacMan.move(m_Field);
    for (size_t i = 0; i < m_SpiritList.size(); i++)
    {
        m_SpiritList[i].move(m_Field);
    }
    if (m_IsGameOver == false)
        m_IsGameOver = detectColisionWithSpirit();
    m_Score += m_FoodBoard.eatFood(m_PacMan.get_position());
    std::cout << m_Score << std::endl;
}

void CGame::restartGame()
{
    m_IsGameOver = false;
    m_Field = CField(NSConfig::kColumnNumber, NSConfig::kRowNumber);
    m_PacMan.setNewPosition(m_Field.getRandomPosition());
    for(size_t i = 0; i < m_SpiritList.size(); i++)
    {
        m_SpiritList[i].setNewPosition(m_Field.getRandomPosition());
    }
    m_Score = 0;
    m_FoodBoard = CFoodBoard(m_Field);
    m_Graph = CGraph(m_Field);
}

bool CGame::detectColisionWithSpirit()
{
    for(size_t i = 0; i < m_SpiritList.size(); i++)
    {
        if(m_SpiritList[i].getSprite().getGlobalBounds().intersects(
                            m_PacMan.getSprite().getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}


void CGame::displayScoreAndAlgorithm()
{
    m_Window.setTitle(NSConfig::kTitle + " Score: " + std::to_string(m_Score) + " Algoritm : " + getAlgorithmName());
}

void CGame::drawSortestPath()
{
    std::pair<int, int> start = m_PacMan.getCoordinates();
    for (auto& spirit : m_SpiritList)
    {
        std::pair<int, int> finish = spirit.getPosition();
        switch (m_Algorithm) {
            case kBFS:
                drawPath(m_Graph.bfsSearch(std::get<0>(start), std::get<1>(start), std::get<0>(finish), std::get<1>(finish)));
                break;
            
            case kDFS:
                drawPath(m_Graph.dfsSearch(std::get<0>(start), std::get<1>(start), std::get<0>(finish), std::get<1>(finish)));
                break;
            
            case kUCS:
                drawPath(m_Graph.ucsSearch(std::get<0>(start), std::get<1>(start), std::get<0>(finish), std::get<1>(finish)));
                break;
                
            default:
                break;
        }
    }
}


void CGame::drawPath(const std::vector<std::pair<int, int> > path)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(NSConfig::kBlockSize, NSConfig::kBlockSize));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    for (auto& node : path)
    {
        int x = std::get<1>(node) * NSConfig::kBlockSize;
        int y = std::get<0>(node) * NSConfig::kBlockSize;
        rectangle.setPosition(x, y);
        m_Window.draw(rectangle);
    }
}


void CGame::switchAlgorithm()
{
    m_Algorithm = (m_Algorithm + 1) % kAlgorithmCount;
}

std::string CGame::getAlgorithmName()
{
    switch (m_Algorithm) {
        case kBFS:
            return kBFSName;
            break;
        case kDFS:
            return kDFSName;
            break;
        case kUCS:
            return kUCSName;
            break;
            
        default:
            break;
    }
}
