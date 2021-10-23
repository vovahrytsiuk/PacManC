//
//  CGame.hpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CGame_hpp
#define CGame_hpp

#include <stdio.h>
#include "CMenu.hpp"
#include <SFML/Graphics.hpp>
#include "Config.hpp"
#include "CPlayer.hpp"
#include "CField.hpp"
#include "CWall.hpp"
#include "CSpirit.hpp"
#include "CFoodBoard.hpp"
#include "CGraph.hpp"
#include "CPathStorage.hpp"

class CGame
{
public:
    CGame(sf::RenderWindow& window);
    void displayMenu();
    void processEvents();
    void draw();
    void gameLogic();
private:
    void processKeyPressed(const sf::Event& event);
    void drawField();
    void drawPacMan();
    void drawSpirits();
    void displayScoreAndAlgorithm();
    void drawSortestPath();
    void drawPath(const std::vector<std::pair<int, int> > path);
    void switchAlgorithm();
    std::string getAlgorithmName();
    
    // private members
    CMenu m_Menu;
    sf::RenderWindow& m_Window;
    bool m_IsGameOver;
    CField m_Field;
    CPlayer m_PacMan;
    CWall m_Wall;
    void restartGame();
    std::vector<CSpirit> m_SpiritList;
    bool detectColisionWithSpirit();
    int m_Score;
    CFoodBoard m_FoodBoard;
    CGraph m_Graph;
    int m_Algorithm;
};

#endif /* CGame_hpp */
