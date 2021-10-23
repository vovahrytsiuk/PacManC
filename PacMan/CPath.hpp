//
//  CPath.hpp
//  PacMan
//
//  Created by Volodymyr on 18.10.2021.
//  Copyright © 2021 Volodymyr Hrytsiuk. All rights reserved.
//

#ifndef CPath_hpp
#define CPath_hpp

#include <stdio.h>
#include <vector>
#include <utility>

class CPath
{
public:
    void addVertexToPath(const std::pair<int, int> vertex);
    std::vector<std::pair<int, int> > get_m_Path() const;
private:
    std::vector<std::pair<int, int>> m_Path;
    
};

#endif /* CPath_hpp */
