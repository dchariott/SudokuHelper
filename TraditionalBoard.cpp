//
// Created by Dylan Chariott on 11/22/19.
//

#include "TraditionalBoard.hpp"

//----------------------------------------------------
TraditionalBoard::TraditionalBoard(const int size, ifstream& gameInfo, const int clusterNum):
                                   Board(size, gameInfo, clusterNum){
    TraditionalBoard::makeBoxClusters();
    initialShutOffLoop();
}


//----------------------------------------------------
void TraditionalBoard::makeBoxClusters(){
    int boxNumber = 1;
    for (int j = 1; j <= 7; j += 3){
        for (int k = 1; k <= 7; k += 3){
            createBox(j, k, boxNumber++);
        }
    }
}

//----------------------------------------------------
void TraditionalBoard::createBox(int j, int k, const int boxNumber){
    Square** squares = new Square*[9];
    int n = 0;
    for (int x = j; x < (j + 3); x++){
        for (int y = k; y < (k + 3); y++){
            squares[n++] = &sub(x, y);
        }
    }
    Cluster* cluster = new Cluster(typeCodes[ClusterType::Box], squares, size, boxNumber);
    clusters.push_back(cluster);
}
