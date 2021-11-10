//
//  CBrain.cpp
//  PacMan
//
//  Created by Volodymyr on 26.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CBrain.hpp"



CBrain::CBrain(const CField& field) : CGraphInterface(field), m_FoodBoard(field), m_PathMemory()
{
}

std::pair<int, int> CBrain::makeStep(const std::pair<int, int>& pacManCoordinates)
{
    if (m_PathMemory.empty())
    {
        findNewPath(m_FoodBoard.getRandomFood(), pacManCoordinates);
    }
    const std::pair<int, int> newCoordinates = m_PathMemory[0];
    m_PathMemory.erase(m_PathMemory.begin());
    return newCoordinates;
}


void CBrain::findNewPath(const std::pair<int, int>& goalCoordinates, const std::pair<int, int>& pacManCoordinates)
{
}


