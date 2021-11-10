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
#include <cmath>
#include <set>
#include <stack>

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

bool CGraph::isValidPosition(const int row, const int column)
{
    return (row >= 0) && (row < NSConfig::kRowNumber) && (column >= 0) && (column < NSConfig::kColumnNumber);
}

bool CGraph::isBlocked(const CField& field, const int row, const int column)
{
    return field.verifyBlockType(row, column, NSConfig::kWall);
}

bool CGraph::isDestination(const int row, const int column, const std::pair<int, int> goal)
{
    return (row == goal.first && column == goal.second);
}

double CGraph::calculateHCost(const int row, const int column, const std::pair<int, int> goal)
{
    return (double)sqrt((row - goal.first) * (row - goal.first) +
                        (column - goal.second) * (column - goal.second));
}

std::vector<std::pair<int, int> > CGraph::aStarSearch(const int startRow, const int startColumn, const int finishRow, const int finishColumn, const CField& field)
{
    if (isValidPosition(startRow, startColumn) == false)
    {
        std::cout << "Failed validation of start position" << std::endl;
        return{};
    }
    
    if (isValidPosition(finishRow, finishColumn) == false)
    {
        std::cout << "Failed validation of finish position" << std::endl;
        return {};
    }
    
    if (isBlocked(field, startRow, startColumn) == true || isBlocked(field, finishRow, finishColumn))
    {
        std::cout << "Start or finish position is wall" << std::endl;
        return {};
    }
    
    if (isDestination(startRow, startColumn, std::make_pair(finishRow, finishColumn)))
    {
        std::cout << "We already on finish position" << std::endl;
        return {};
    }
    
    std::vector<std::vector<bool> > closedList;
    for (size_t r = 0; r < NSConfig::kRowNumber; r++)
    {
        closedList.push_back({});
        for (size_t c = 0; c < NSConfig::kColumnNumber; c++)
        {
            closedList[r].push_back(false);
        }
    }
    
    std::vector<std::vector<cell> > cellDetails;
    size_t r, c;
    for (r = 0; r < NSConfig::kRowNumber; r++)
    {
        cellDetails.push_back({});
        for (c = 0; c < NSConfig::kColumnNumber; c++)
        {
            cellDetails[r].push_back({});
            cellDetails[r][c].f = __FLT_MAX__;
            cellDetails[r][c].h = __FLT_MAX__;
            cellDetails[r][c].g = __FLT_MAX__;
            cellDetails[r][c].parent_row = -1;
            cellDetails[r][c].parent_column = -1;
        }
    }
    // for starting node
    r = startRow;
    c = startColumn;
    cellDetails[r][c].f = 0.0;
    cellDetails[r][c].g = 0.0;
    cellDetails[r][c].h = 0.0;
    cellDetails[r][c].parent_row = r;
    cellDetails[r][c].parent_column = c;
    
    std::set<posWithValue> openList;
    openList.insert(std::make_pair(0.0, std::make_pair(r, c)));
    bool goalFound = false;
    int nr, nc;
    double ng, nh, nf;
    while (openList.empty() == false)
    {
        posWithValue p = *openList.begin();
        openList.erase(openList.begin());
        r = p.second.first;
        c = p.second.second;
        closedList[r][c] = true;
        
        
        
        // process neibours
        // up
        
        for(const auto& neibour: kNeibours)
        {
            int nr = r + std::get<0>(neibour);
            int nc = c + std::get<1>(neibour);
            normalizePosition(nr, nc);
            if (isValidPosition(nr, nc) == true)
            {
                if (isDestination(nr, nc, std::make_pair(finishRow, finishColumn)) == true)
                {
                    cellDetails[nr][nc].parent_row = r;
                    cellDetails[nr][nc].parent_column = c;
                    goalFound = true;
                    // put here path tracing
                    return tracePath(cellDetails, finishRow, finishColumn);
                }
                else if (closedList[nr][nc] == false && (isBlocked(field, nr, nc) == false))
                {
                    ng = cellDetails[r][c].g + 1.0;
                    nh = calculateHCost(nr, nc, std::make_pair(finishRow, finishColumn));
                    nf = ng + nh;
                    if (cellDetails[nr][nc].f == __FLT_MAX__ || cellDetails[nr][nc].f > nf)
                    {
                        openList.insert(std::make_pair(nf, std::make_pair(nr, nc)));
                        cellDetails[nr][nc].parent_row = r;
                        cellDetails[nr][nc].parent_column = c;
                        cellDetails[nr][nc].f = nf;
                        cellDetails[nr][nc].g = ng;
                        cellDetails[nr][nc].h = nh;
                    }
                }
            }
        }
    }
    return {};
}


void CGraph::normalizePosition(int& row, int& column)
{
    if (row < 0)
    {
        row = NSConfig::kRowNumber - 1;
    }
    else if (row >= NSConfig::kRowNumber)
    {
        row = 0;
    }
    if (column < 0)
    {
        column = NSConfig::kColumnNumber - 1;
    }
    else if (column >= NSConfig::kColumnNumber)
    {
        column = 0;
    }
}


std::vector<std::pair<int, int> > CGraph::tracePath(std::vector<std::vector<cell> >& cellDetails, const int finishRow, const int finishColumn)
{
    std::vector<std::pair<int, int> > path;
    int row = finishRow;
    int column = finishColumn;
    
    std::stack<std::pair<int, int> > pathStack;
    while (!(cellDetails[row][column].parent_column == column && cellDetails[row][column].parent_row == row))
    {
        pathStack.push(std::make_pair(row, column));
        int tempRow = cellDetails[row][column].parent_row;
        int tempColumn = cellDetails[row][column].parent_column;
        row = tempRow;
        column = tempColumn;
    }
    
    pathStack.push(std::make_pair(row, column));
    
    while (pathStack.empty() == false)
    {
        path.push_back(pathStack.top());
        pathStack.pop();
    }
    return path;
}
