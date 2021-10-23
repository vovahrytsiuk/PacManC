//
//  CWall.cpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CWall.hpp"

CWall::CWall()
{
    m_Texture.loadFromFile(NSConfig::kWallTexturePath);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setTextureRect(sf::IntRect(0, 0, NSConfig::kBlockSize, NSConfig::kBlockSize));
    
}

sf::Sprite& CWall::getSprite()
{
    return m_Sprite;
}
