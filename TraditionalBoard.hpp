//
// Created by Dylan Chariott on 11/22/19.
//

#pragma once
#include "Board.hpp"

class TraditionalBoard : public Board {
private:
    void createBox(int j, int k, int boxNumber);
    void makeBoxClusters() override;
public:
    TraditionalBoard(int size, ifstream& gameInfo, int clusterNum = 27);
};



