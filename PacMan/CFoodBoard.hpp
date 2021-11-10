//
//  CFoodBoard.hpp
//  PacMan
//
//  Created by Volodymyr on 18.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CFoodBoard_hpp
#define CFoodBoard_hpp

#include <stdio.h>
#include "CField.hpp"
#include <utility>

class CFoodBoard
{
public:
    CFoodBoard(const CField& field);
    int eatFood(std::pair<int, int> coordinates);
    bool isFoodPresent(const int row, const int column);
    std::pair<int, int> getRandomFood() const;
private:
    int m_RowNumber;
    int m_ColumnNumber;
    //                    row column
    std::vector<std::pair<int, int> > m_FoodList;
};

#endif /* CFoodBoard_hpp */
