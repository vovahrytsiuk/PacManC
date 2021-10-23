//
//  CPath.cpp
//  PacMan
//
//  Created by Volodymyr on 18.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CPath.hpp"

std::vector<std::pair<int, int> > CPath::get_m_Path() const
{
    return m_Path;
}


void CPath::addVertexToPath(const std::pair<int, int> coordinates)
{
    m_Path.push_back(coordinates);
}

