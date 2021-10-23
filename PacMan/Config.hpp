//
//  Config.hpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef Config_h
#define Config_h

#include <string>
#include <vector>

namespace NSConfig
{
    extern const int kScreenWidth;
    extern const int kScreenHeight;
    extern const int kBlockSize;
    extern const std::string kTitle;
    extern const int kHorisontalRoad;
    extern const int kVerticalRoad;
    extern const int kCrossRoad;
    extern const int kWall;
    extern const std::vector<std::string> kMenuItems;
    extern const std::string kPacManTexturePath;
    extern const int kRowNumber;
    extern const int kColumnNumber;
    extern const std::string kWallTexturePath;
    extern const std::string kPacManWalkTexturePath;
    extern const std::string kSpiritTexturePath;
}

#endif /* Config_h */
