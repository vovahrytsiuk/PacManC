//
//  CField.cpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CField.hpp"
#include "Config.hpp"
#include <random>
#include <iostream>

CField::CField(int column_number, int row_number, double horisontal_ratio, double vertical_ratio)
{
    m_columnNumber = column_number;
    m_rowNumber = row_number;
    m_horRatio = horisontal_ratio;
    m_vertRatio = vertical_ratio;
    generateField();
}

int CField::get_m_columnNumber() const
{
    return m_columnNumber;
}

int CField::get_m_rowNumber() const
{
    return m_rowNumber;
}

std::pair<int, int> CField::getRandomPosition() const
{
    int randomRow = -1;
    int randomColumn = -1;
    while(1)
    {
        randomRow = rand() % m_rowNumber;
        randomColumn = rand() % m_columnNumber;
        if (m_field[randomRow][randomColumn] != 0)
            return {randomRow, randomColumn};

    }
}

std::vector<int> CField::generateRows() const
{
    std::vector<int> rows;
    for(int i = 1; i < m_rowNumber - 1; i++)
    {
        int random = rand() % 100;
        if (random < m_horRatio * 100)
        {
            rows.push_back(i);
            i++;
        }
    }
    return rows;
}

std::vector<int> CField::generateColumns() const
{
    std::vector<int> columns;
    for(int i = 1; i < m_columnNumber - 1; i++)
    {
        int random = rand() % 100;
        if (random < m_vertRatio * 100)
        {
            columns.push_back(i);
            i++;
        }
    }
    return columns;
}

void CField::generateField()
{
    for(int row = 0; row < NSConfig::kRowNumber; row++)
    {
        std::vector<int> r;
        for(int column = 0; column < NSConfig::kColumnNumber; column++)
        {
            r.push_back(NSConfig::kWall);
        }
        m_field.push_back(r);
    }
    for(const int row : generateRows())
    {
        for(int column = 0; column < NSConfig::kColumnNumber; column++)
        {
            m_field[row][column] = NSConfig::kHorisontalRoad;
        }
    }

    for(const int column : generateColumns())
    {
        for(int row = 0; row < m_rowNumber; row++)
        {
            if (m_field[row][column] == NSConfig::kWall)
            {
                m_field[row][column] = NSConfig::kVerticalRoad;
            }
            else
            {
                m_field[row][column] = NSConfig::kCrossRoad;
            }
        }
    }
}


bool CField::verifyBlockType(const int row, const int column, const int type) const
{
    if (row < 0 || row >= NSConfig::kRowNumber)
        return false;
    if (column < 0 || column >= NSConfig::kColumnNumber)
        return false;
    return m_field[row][column] == type;
}
