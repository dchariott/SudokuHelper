//
// Created by Dylan Chariott on 10/26/19.
//

#pragma once
#include "TraditionalBoard.hpp"

class DiagonalBoard : public TraditionalBoard{
public:
    DiagonalBoard(int size, ifstream& gameInfo);
};



