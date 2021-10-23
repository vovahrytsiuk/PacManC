//
//  Config.cpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include <stdio.h>
#include "Config.hpp"


namespace NSConfig
{
    const int kScreenWidth = 1280;
    const int kScreenHeight = 768;
    const int kBlockSize = 64;
    const std::string kTitle = "PacMan by vhrytsiuk";
    const int kHorisontalRoad = 1;
    const int kVerticalRoad = 2;
    const int kCrossRoad = 3;
    const int kWall = 0;
    const std::vector<std::string> kMenuItems = {"Restart", "Exit"};
    const std::string kPacManTexturePath = "/Users/vova/Desktop/PacMan/PacManC/PacMan/Resources/pacman.png";
    const std::string kWallTexturePath = "/Users/vova/Desktop/PacMan/PacManC/PacMan/Resources/wall.png";
    const std::string kPacManWalkTexturePath = "/Users/vova/Desktop/PacMan/PacManC/PacMan/Resources/walk.png";
    const std::string kSpiritTexturePath = "/Users/vova/Desktop/PacMan/PacManC/PacMan/Resources/spirit.png";
    const int kRowNumber = int(kScreenHeight / kBlockSize);
    const int kColumnNumber = int(kScreenWidth / kBlockSize);
}

