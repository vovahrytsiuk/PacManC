//
//  CGraphInterFace.cpp
//  PacMan
//
//  Created by Volodymyr on 26.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CGraphInterFace.hpp"
#include "Config.hpp"


namespace {
    std::vector<std::pair<int, int> > kNeibours
    {   //r //c
        {-1, 0},
        {0, -1},
        {0, 1},
        {1, 0}
    };
}


CGraphInterface::CGraphInterface(const CField& field)
{
    m_RowNumber = field.get_m_rowNumber();
    m_ColumnNumber = field.get_m_columnNumber();
    for (int row = 0; row < m_RowNumber; row++)
    {
        for (int column = 0; column < m_ColumnNumber; column++)
        {
            //m_Graph.push_back({});
            // for each node check neibours
            // if neibour is not wall add vertex to graph
            if (field.verifyBlockType(row, column, NSConfig::kWall))
                continue;
            m_Nodes.push_back(std::make_pair(row, column));
            for(const auto& neibour: kNeibours)
            {
                int neibourRow = row + std::get<0>(neibour);
                int neibourColumn = column + std::get<1>(neibour);
                validateCoordinates(neibourRow, neibourColumn);
                if (field.verifyBlockType(neibourRow, neibourColumn, NSConfig::kWall))
                    continue;
                m_Nodes.push_back(std::make_pair(neibourRow, neibourColumn));
                int start = getVertex(row, column);
                int finish = getVertex(neibourRow, neibourColumn);
                m_Graph[start].push_back(finish);
                m_Cost[{start, finish}] = 1;
            }
        }
    }
}


void CGraphInterface::validateCoordinates(int& row, int& column)
{
    if(row < 0)
    {
        row = m_RowNumber - 1;
    }
    if(column < 0)
    {
        column = m_ColumnNumber - 1;
    }
    if(row >= m_RowNumber)
    {
        row = 0;
    }
    if(column >= m_ColumnNumber)
    {
        column = 0;
    }
}

int CGraphInterface::getVertex(const int row, const int column)
{
    int vertex = row * m_ColumnNumber + column;
    if (std::find(m_Nodes.begin(), m_Nodes.end(), std::make_pair(row, column)) == m_Nodes.end())
    {
        vertex++;
    }
    return vertex;
}

