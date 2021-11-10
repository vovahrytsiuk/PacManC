//
//  CBrain.hpp
//  PacMan
//
//  Created by Volodymyr on 26.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CBrain_hpp
#define CBrain_hpp

#include <stdio.h>
#include "CGraphInterFace.hpp"
#include <vector>
#include "CField.hpp"
#include "CFoodBoard.hpp"

class CBrain : public CGraphInterface
{
    struct Node
    {
        int m_Column;
        int m_Row;
        int m_ParentRow;
        int m_ParentColumn;
        double m_GCost;
        double m_HCost;
        double m_FCost;
        
        bool operator < (const Node& rhs)
        {
            return this->m_FCost < rhs.m_FCost;
        }
    };
    
    
    std::vector<std::pair<int, int> > m_PathMemory;
    
    CFoodBoard m_FoodBoard;
public:
    CBrain(const CField& field);
    
    std::pair<int, int> makeStep(const std::pair<int, int>& pacManCoordinates);
    
    void findNewPath(const std::pair<int, int>& goalCoordinates, const std::pair<int, int>& pacManCoordinates);
};

#endif /* CBrain_hpp */
