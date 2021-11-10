//
//  CPlayer.hpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CPlayer_hpp
#define CPlayer_hpp

#include <stdio.h>
#include <utility>
#include <SFML/Graphics.hpp>
#include "CField.hpp"
#include "Config.hpp"
#include "CGraphInterFace.hpp"
#include "CFoodBoard.hpp"
#include "CBrain.hpp"

class CPlayer
{
public:
    CPlayer(const CField& field, std::pair<int, int> coordinates, int speed = 64);
    void move();
    std::pair<int, int> get_position() const;
    const sf::Sprite& getSprite();
    void move(const CField& field);
    void updateDirection(int dx, int dy);
    void setNewPosition(std::pair<int, int> coordinates);
    std::pair<int, int> getCoordinates();
private:
    int m_x;
    int m_y;
    int m_speed;
    /// \brief 1 - move right, -1 - move left, 0 - don't move
    int m_dx;
    /// \brief 1 - move down, -1 - move up, 0 - don't move
    int m_dy;
    sf::Sprite m_PacManSprite;
    sf::Texture m_PacManTexture;
    CBrain m_Brain;
};


#endif /* CPlayer_hpp */
