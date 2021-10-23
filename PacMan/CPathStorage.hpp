//
//  CPathStorage.hpp
//  PacMan
//
//  Created by Volodymyr on 20.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CPathStorage_hpp
#define CPathStorage_hpp

#include <stdio.h>
#include "CGraph.hpp"
#include <map>


class CPathStorage
{
public:
    CPathStorage(CGraph& graph);
    std::vector<std::pair<int, int> > getBFSPath(std::pair<int, int> startNode, std::pair<int, int> finishNode);
private:
    // row, column
    std::vector<std::pair<int, int> > m_Nodes;
    std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, std::vector<std::pair<int, int> > > m_BFSPaths;
    std::pair<std::pair<int, int>, std::pair<int, int> > getNodesKey(std::pair<int, int> startNode, std::pair<int, int> finishNode);
    
};

#endif /* CPathStorage_hpp */
