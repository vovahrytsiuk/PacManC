//
//  CSpirit.hpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CSpirit_hpp
#define CSpirit_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "CField.hpp"
#include "Config.hpp"

class CSpirit
{
public:
    CSpirit(std::pair<int, int> coordinates, int speed = 64);
    CSpirit(const CSpirit& right);
    void setNewPosition(std::pair<int, int> coordinates);
    void move(const CField& field);
    const sf::Sprite& getSprite();
    std::pair<int, int> getPosition() const;
private:
    int m_x;
    int m_y;
    int m_speed;
    /// \brief 1 - move right, -1 - move left, 0 - don't move
    int m_dx;
    /// \brief 1 - move down, -1 - move up, 0 - don't move
    int m_dy;
    sf::Sprite m_Sprite;
    sf::Texture m_Texture;
    void changeDirection();
    
};

#endif /* CSpirit_hpp */
