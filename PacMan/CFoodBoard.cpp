//
//  CFoodBoard.cpp
//  PacMan
//
//  Created by Volodymyr on 18.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CFoodBoard.hpp"
#include "Config.hpp"

CFoodBoard::CFoodBoard(const CField& field)
{
    m_RowNumber = field.get_m_rowNumber();
    m_ColumnNumber = field.get_m_columnNumber();
    for(size_t row = 0; row < m_RowNumber; row++)
    {
        std::vector<bool> food;
        for(size_t column = 0; column < m_ColumnNumber; column++)
        {
            food.push_back(!field.verifyBlockType(row, column, NSConfig::kWall));
        }
        m_Food.push_back(food);
    }
}

int CFoodBoard::eatFood(std::pair<int, int> coordinates)
{
    int row = std::get<1>(coordinates) / NSConfig::kBlockSize;
    if (row < 0)
        row = 0;
    if (row >= NSConfig::kRowNumber)
        row = NSConfig::kRowNumber - 1;
    int column = std::get<0>(coordinates) / NSConfig::kBlockSize;
    if (column < 0)
        column = 0;
    if (column >= NSConfig::kColumnNumber)
        column = NSConfig::kColumnNumber - 1;
    int eated = 0;
    if (m_Food[row][column] == true)
    {
        eated++;
        m_Food[row][column] = false;
    }
    return eated;
}


bool CFoodBoard::isFoodPresent(const int row, const int column)
{
    return m_Food[row][column];
}
