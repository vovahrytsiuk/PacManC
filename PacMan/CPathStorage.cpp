//
//  CPathStorage.cpp
//  PacMan
//
//  Created by Volodymyr on 20.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CPathStorage.hpp"
#include "Config.hpp"

CPathStorage::CPathStorage(CGraph& graph)
{
    m_Nodes = graph.getNodes();
    
    for (int i = 0; i < m_Nodes.size(); i++)
    {
        for(int j = 0; j < m_Nodes.size(); j++)
        {
            if (i == j)
                continue;
            int startRow = std::get<0>(m_Nodes[i]);
            int startColumn = std::get<1>(m_Nodes[i]);
            int finishRow = std::get<0>(m_Nodes[j]);
            int finishColumn = std::get<1>(m_Nodes[j]);
            m_BFSPaths[getNodesKey(m_Nodes[i], m_Nodes[j])] = graph.bfsSearch(startRow, startColumn, finishRow, finishColumn);
        }
    }
}


std::pair<std::pair<int, int>, std::pair<int, int> > CPathStorage::getNodesKey(std::pair<int, int> startNode, std::pair<int, int> finishNode)
{
    return std::make_pair(startNode, finishNode);
}


std::vector<std::pair<int, int> > CPathStorage::getBFSPath(std::pair<int, int> startNode, std::pair<int, int> finishNode)
{
    return m_BFSPaths[getNodesKey(startNode, finishNode)];
}
