//
//  CSpirit.cpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CSpirit.hpp"
#include "Config.hpp"
#include <random>
#include <iostream>

CSpirit::CSpirit(std::pair<int, int> coordinates, int speed)
{
    setNewPosition(coordinates);
    m_speed = speed;
    m_dx = 0;
    m_dy = 0;
    m_Texture.loadFromFile(NSConfig::kSpiritTexturePath);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.scale(2.0f, 2.0f);
    m_Sprite.setPosition(float(m_x), float(m_y));
    changeDirection();
}

void CSpirit::setNewPosition(std::pair<int, int> coordinates)
{
    m_y = std::get<0>(coordinates) * NSConfig::kBlockSize;
    m_x = std::get<1>(coordinates) * NSConfig::kBlockSize;
    m_Sprite.setPosition(m_x, m_y);
}

namespace {
    const std::vector<std::pair<int, int> > availbleDirections
    {   //dx,   dy
        {-1,    0},
        {1,     0},
        {0,     -1},
        {0,     1}
    };
    const std::vector<int> directions
    {
        -1, 1
    };
}


void CSpirit::changeDirection()
{
    const int newDirection = rand() % availbleDirections.size();
    std::cout << newDirection << std::endl;
    m_dx = std::get<0>(availbleDirections[newDirection]);
    m_dy = std::get<1>(availbleDirections[newDirection]);
}

void CSpirit::move(const CField& field)
{
    if (field.verifyBlockType(int(m_y / NSConfig::kBlockSize), int(m_x / NSConfig::kBlockSize), NSConfig::kHorisontalRoad))
    {
        m_dy = 0;
        if (m_dx == 0)
        {
            m_dx = directions[rand()%2];
        }
    }
    if (field.verifyBlockType(int(m_y / NSConfig::kBlockSize), int(m_x / NSConfig::kBlockSize), NSConfig::kVerticalRoad))
    {
        m_dx = 0;
        if (m_dy == 0)
        {
            m_dy = directions[rand()%2];
        }
    }

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
    int r = m_y / NSConfig::kBlockSize;
    int c = m_x / NSConfig::kBlockSize;
    if (m_x % NSConfig::kBlockSize == 0 && m_y % NSConfig::kBlockSize == 0 && field.verifyBlockType(r, c, NSConfig::kCrossRoad))
    {
        std::cout << "change direction" << std::endl;
        changeDirection();
    }
    m_Sprite.setPosition(m_x, m_y);
}


const sf::Sprite& CSpirit::getSprite()
{
    return m_Sprite;
}

CSpirit::CSpirit(const CSpirit& right)
{
    m_speed = right.m_speed;
    m_x = right.m_x;
    m_y = right.m_y;
    m_Texture.loadFromFile(NSConfig::kSpiritTexturePath);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.scale(2.0f, 2.0f);
    m_Sprite.setPosition(float(m_x), float(m_y));
    changeDirection();
}

std::pair<int, int> CSpirit::getPosition() const
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
