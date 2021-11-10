//
//  CPlayer.cpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CPlayer.hpp"
#include "Config.hpp"
#include <iostream>

CPlayer::CPlayer(const CField& field, std::pair<int, int> coordinates, int speed): m_Brain(field)
{
    setNewPosition(coordinates);
    m_speed = speed;
    m_dx = 0;
    m_dy = 0;
    m_PacManTexture.loadFromFile(NSConfig::kPacManTexturePath);
    m_PacManSprite.setTexture(m_PacManTexture);
    m_PacManSprite.scale(2.0f, 2.0f);
    m_PacManSprite.setPosition(float(m_x), float(m_y));
}

void CPlayer::setNewPosition(std::pair<int, int> coordinates)
{
    m_y = std::get<0>(coordinates) * NSConfig::kBlockSize;
    m_x = std::get<1>(coordinates) * NSConfig::kBlockSize;
    m_PacManSprite.setPosition(m_x, m_y);
}

std::pair<int, int> CPlayer::get_position() const
{
    return std::pair<int, int>{m_x, m_y};
}

const sf::Sprite& CPlayer::getSprite()
{
    return m_PacManSprite;
}


void CPlayer::move(const CField& field)
{
        int row = (m_y + NSConfig::kBlockSize / 2) / NSConfig::kBlockSize;
        int column = (m_x + NSConfig::kBlockSize / 2) / NSConfig::kBlockSize;
    //    if (field.verifyBlockType(row, column, NSConfig::kVerticalRoad) == true)
    //    {
    //        m_dx = 0;
    //    }
    //    if (field.verifyBlockType(row, column, NSConfig::kHorisontalRoad) == true)
    //    {
    //        m_dy = 0;
    //    }
        m_x += m_dx * m_speed;
        m_y += m_dy * m_speed;
        if(m_x > NSConfig::kScreenWidth)
        {
            m_x = 0;
        }
        if(m_y > NSConfig::kScreenHeight)
        {
            m_y = 0;
        }
        if(m_x < -NSConfig::kBlockSize)
        {
            m_x = NSConfig::kScreenWidth;
        }
        if(m_y < -NSConfig::kBlockSize)
        {
            m_y = NSConfig::kScreenHeight;
        }
        
        m_PacManSprite.setPosition(m_x, m_y);
        // check for walls colisions
        sf::Sprite wall;
        wall.setTextureRect(sf::IntRect(0, 0, NSConfig::kBlockSize, NSConfig::kBlockSize));
        int wall_r = row;
        int wall_c = column - 1;
        if (field.verifyBlockType(wall_r, wall_c, NSConfig::kWall))
        {
            wall.setPosition(float(wall_c) * NSConfig::kBlockSize, float(wall_r) * NSConfig::kBlockSize);
            if (wall.getGlobalBounds().intersects(m_PacManSprite.getGlobalBounds()))
            {
                // colision detected
                m_x += m_speed;
            }
        }
        ++wall_c;
        --wall_r;
        if (field.verifyBlockType(wall_r, wall_c, NSConfig::kWall))
        {
            wall.setPosition(float(wall_c) * NSConfig::kBlockSize, float(wall_r) * NSConfig::kBlockSize);
            if (wall.getGlobalBounds().intersects(m_PacManSprite.getGlobalBounds()))
            {
                // colision detected
                m_y += m_speed;
            }
        }
        ++wall_c;
        ++wall_r;
        if (field.verifyBlockType(wall_r, wall_c, NSConfig::kWall))
        {
            wall.setPosition(float(wall_c) * NSConfig::kBlockSize, float(wall_r) * NSConfig::kBlockSize);
            if (wall.getGlobalBounds().intersects(m_PacManSprite.getGlobalBounds()))
            {
                // colision detected
                m_x -= m_speed;
            }
        }
        --wall_c;
        ++wall_r;
        if (field.verifyBlockType(wall_r, wall_c, NSConfig::kWall))
        {
            wall.setPosition(float(wall_c) * NSConfig::kBlockSize, float(wall_r) * NSConfig::kBlockSize);
            if (wall.getGlobalBounds().intersects(m_PacManSprite.getGlobalBounds()))
            {
                // colision detected
                m_y -= m_speed;
            }
        }
    
    
    
    m_PacManSprite.setPosition(m_x, m_y);
}

void CPlayer::updateDirection(int dx, int dy)
{
    m_dx = dx;
    m_dy = dy;
}


std::pair<int, int> CPlayer::getCoordinates()
{
    int row = m_y / NSConfig::kBlockSize;
    if (row < 0)
    {
        row = 0;
    }
    if (row >= NSConfig::kRowNumber)
    {
        row = NSConfig::kRowNumber - 1;
    }
    int column = m_x / NSConfig::kBlockSize;
    if (column < 0)
    {
        column = 0;
    }
    if (column >= NSConfig::kColumnNumber)
    {
        column = NSConfig::kColumnNumber - 1;
    }
    return std::make_pair(row, column);
}
