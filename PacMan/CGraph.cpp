//
//  CGraph.cpp
//  PacMan
//
//  Created by Volodymyr on 18.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#include "CGraph.hpp"
#include "Config.hpp"
#include <list>
#include <queue>
#include <iostream>

namespace {
    std::vector<std::pair<int, int> > kNeibours
    {   //r //c
        {-1, 0},
        {0, -1},
        {0, 1},
        {1, 0}
    };
}

CGraph::CGraph(const CField& field)
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

void CGraph::validateCoordinates(int& row, int& column)
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

std::vector<std::pair<int, int> > CGraph::dfsSearch(const int startRow, const int startColumn, const int finishRow, const int finishColumn)
{
    std::vector<int> previousVertexes(m_RowNumber * m_ColumnNumber, 0);
    std::vector<bool> visited(m_RowNumber * m_ColumnNumber, false);
    dfs(visited, previousVertexes, getVertex(startRow, startColumn), getVertex(finishRow, finishColumn));
    return getPath(previousVertexes, getVertex(startRow, startColumn), getVertex(finishRow, finishColumn));
    
}

void CGraph::dfs(std::vector<bool>& visited, std::vector<int>& previousVertexes, int currentVertes, const int finishVertex)
{
    visited[currentVertes] = true;
    if (currentVertes == finishVertex)
    {
        return;
    }
    std::vector<int>::iterator i;
    for(i = m_Graph[currentVertes].begin(); i != m_Graph[currentVertes].end(); ++i)
    {
        if(visited[*i] == false)
        {
            previousVertexes[*i] = currentVertes;
            dfs(visited, previousVertexes, *i, finishVertex);
        }
    }
}

std::pair<int, int> CGraph::getCoordinates(const int vertex)
{
    const int row = int(vertex / m_ColumnNumber);
    const int column = vertex % m_ColumnNumber;
    return {row, column};
}

std::vector<std::pair<int, int> > CGraph::bfsSearch(const int startRow, const int startColumn, const int finishRow, const int finishColumn)
{
    int currentVertex = getVertex(startRow, startColumn);
    const int finishVertex = getVertex(finishRow, finishColumn);
    std::vector<bool> visited(m_RowNumber * m_ColumnNumber, false);
    std::vector<int> previousVertex(m_RowNumber * m_ColumnNumber, 0);
    
    visited[currentVertex] = true;
    std::list<int> queue;
    queue.push_back(currentVertex);
    while(!queue.empty())
    {
        currentVertex = queue.front();
        queue.pop_front();
        if (currentVertex == finishVertex)
        {
            return getPath(previousVertex, getVertex(startRow, startColumn), getVertex(finishRow, finishColumn));
        }
        
        for(const auto& vertex : m_Graph[currentVertex])
        {
            if (visited[vertex] == false)
            {
                visited[vertex] = true;
                previousVertex[vertex] = currentVertex;
                queue.push_back(vertex);
            }
        }
    }
    return getPath(previousVertex, getVertex(startRow, startColumn), getVertex(finishRow, finishColumn));
}

std::vector<std::pair<int, int> > CGraph::ucsSearch(const int startRow, const int startColumn, const int finishRow, const int finishColumn)
{
    const int startVertex = getVertex(startRow, startColumn);
    const int finishVertex = getVertex(finishRow, finishColumn);
    
    std::priority_queue<std::pair<int, int> > queue;
    std::vector<int> previousVertexes(m_RowNumber * m_ColumnNumber, 0);
    
    queue.push({0, startVertex});
    
    std::vector<bool> visited(m_RowNumber * m_ColumnNumber, false);
    std::vector<int> previous(m_RowNumber * m_ColumnNumber);
    
    while (!queue.empty()) {
        std::pair<int, int> p = queue.top();
        queue.pop();
        
        if (p.second == finishVertex)
            return getPath(previousVertexes, startVertex, finishVertex);
        
        if (visited[p.second] == false)
        {
            visited[p.second] = true;
            
            for(int i = 0; i < m_Graph[p.second].size(); ++i)
            {
                if (visited[m_Graph[p.second][i]] == true)
                    continue;
                previousVertexes[m_Graph[p.second][i]] = p.second;
                queue.push(std::make_pair((p.first + m_Cost[std::make_pair(p.second, m_Graph[p.second][i])] * -1), m_Graph[p.second][i]));
            }
        }
    }
    return getPath(previous, startVertex, finishVertex);
    
}

std::vector<std::pair<int, int> > CGraph::getPath(const std::vector<int>& previousVertexes, const int startVertex, const int finishVertex)
{
    std::vector<std::pair<int, int> > path;
    path.push_back(getCoordinates(finishVertex));
    int currentVertex = finishVertex;
    do
    {
        std::cout << currentVertex << " : ";
        currentVertex = previousVertexes[currentVertex];
        path.push_back(getCoordinates(currentVertex));
    }
    while (currentVertex != startVertex);
    return path;
}

int CGraph::getVertex(const int row, const int column)
{
    int vertex = row * m_ColumnNumber + column;
    if (std::find(m_Nodes.begin(), m_Nodes.end(), std::make_pair(row, column)) == m_Nodes.end())
    {
        vertex++;
    }
    return vertex;
}


std::vector<std::pair<int, int> > CGraph::getNodes() const
{
    return m_Nodes;
}
