//
//  CGraphInterFace.hpp
//  PacMan
//
//  Created by Volodymyr on 26.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CGraphInterFace_hpp
#define CGraphInterFace_hpp

#include <stdio.h>
#include "CField.hpp"
#include <map>

class CGraphInterface
{
    std::map<int, std::vector<int> > m_Graph;
    int m_RowNumber;
    int m_ColumnNumber;
    std::vector<std::pair<int, int> > m_Nodes;
    std::map<std::pair<int, int>, int> m_Cost;
    
    void validateCoordinates(int& row, int& column);
    int getVertex(const int row, const int column);
public:
    CGraphInterface(const CField& field);
    
};

#endif /* CGraphInterFace_hpp */
