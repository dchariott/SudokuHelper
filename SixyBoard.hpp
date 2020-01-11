//
// Created by Dylan Chariott on 11/22/19.
//

#pragma once
#include "Board.hpp"

class SixyBoard : public Board{
private:
    void createHBox(int j, int k, int hBoxNumber);
    void createVBox(int j, int k, int vBoxNumber);
    void makeBoxClusters() override;
public:
    SixyBoard(int size, ifstream& gameInfo);
};