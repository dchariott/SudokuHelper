//
// Created by Dylan Chariott on 10/26/19.
//

#include "DiagonalBoard.hpp"

//------------------------------------
DiagonalBoard::DiagonalBoard(const int size, ifstream& gameInfo): TraditionalBoard(size, gameInfo, 29){
    int m = 0;

    Square** diagonalCluster1 = new Square*[9];
    for (int j = 1, k = 1; (j <= 9) && (k <= 9); j++, k++){
        diagonalCluster1[m++] = &bd[index(j, k)];
    }
    Cluster* diag1 = new Cluster("Diagonal", diagonalCluster1, size, 1);
    clusters.push_back(diag1);

    m = 0;
    Square** diagonalCluster2 = new Square*[9];
    for (int j = 1, k = 9; (j <= 9) && (k >= 1); j++, k--){
        diagonalCluster2[m++] = &bd[index(j, k)];
    }
    Cluster* diag2 = new Cluster(typeCodes[ClusterType::Diagonal], diagonalCluster2, size, 2);
    clusters.push_back(diag2);

    initialShutOffLoop();
}