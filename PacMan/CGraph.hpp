//
//  CGraph.hpp
//  PacMan
//
//  Created by Volodymyr on 18.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CGraph_hpp
#define CGraph_hpp

#include <stdio.h>
#include "CField.hpp"
#include "CPath.hpp"
#include <map>

class CGraph
{
public:
    CGraph(const CField& field);
    
    std::vector<std::pair<int, int> > dfsSearch(const int startRow, const int startColumn, const int finishRow, const int finishColumn);
    
    std::vector<std::pair<int, int> > bfsSearch(const int startRow, const int startColumn, const int finishRow, const int finishColumn);
    
    std::vector<std::pair<int, int> > ucsSearch(const int startRow, const int startColumn, const int finishRow, const int finishColumn);
    
    std::vector<std::pair<int, int> > getNodes() const;
private:
    std::vector<std::pair<int, int> > m_Nodes;
    
    std::map<int, std::vector<int> > m_Graph;
    
    std::map<std::pair<int, int>, int> m_Cost;
    
    int getVertex(const int row, const int column);
    
    int m_RowNumber;
    
    int m_ColumnNumber;
    
    void dfs(std::vector<bool>& visited, std::vector<int>& previousVertexes, int currentVertex, const int finishVertex);
    
    void validateCoordinates(int& row, int& column);
    
    std::pair<int, int> getCoordinates(const int vertex);
    
    std::vector<std::pair<int, int> > getPath(const std::vector<int>& previousVertexes, const int startVertex, const int finishVertex);
};

#endif /* CGraph_hpp */
