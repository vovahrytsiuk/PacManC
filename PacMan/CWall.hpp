//
//  CWall.hpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CWall_hpp
#define CWall_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

class CWall
{
public:
    CWall();
    sf::Sprite& getSprite();
private:
    sf::Sprite m_Sprite;
    sf::Texture m_Texture;
};

#endif /* CWall_hpp */
