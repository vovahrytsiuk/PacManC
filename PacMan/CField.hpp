//
//  CField.hpp
//  PacMan
//
//  Created by Volodymyr on 17.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CField_hpp
#define CField_hpp

#include <stdio.h>
#include <utility>
#include <vector>

class CField
{
public:
    CField(int column_number, int row_number, double horisontal_ratio = 0.8, double vertical_ratio = 0.7);

    int get_m_columnNumber() const;
    int get_m_rowNumber() const;
    std::pair<int, int> getRandomPosition() const;
    bool verifyBlockType(const int row, const int column, const int type) const;

private:
    int m_columnNumber;
    int m_rowNumber;
    double m_horRatio;
    double m_vertRatio;
    std::vector<std::vector<int> > m_field;

    std::vector<int> generateRows() const;
    std::vector<int> generateColumns() const;
    void generateField();
};

#endif /* CField_hpp */
