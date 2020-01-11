//
// Created by Dylan Chariott on 11/22/19.
//

#include "SixyBoard.hpp"

//----------------------------------------------------
SixyBoard::SixyBoard(const int size, ifstream& gameInfo): Board(size, gameInfo, 24){
    SixyBoard::makeBoxClusters();
    initialShutOffLoop();
}

//----------------------------------------------------
void SixyBoard::makeBoxClusters(){
    int hBoxNumber = 1, vBoxNumber = 1;
    for (int j = 1; j < size; j += 2){
        for (int k = 1; k < size; k += 3){
            createHBox(j, k, hBoxNumber++);
        }
    }
    for (int j = 1; j < size; j += 3){
        for (int k = 1; k < size; k += 2){
            createVBox(j, k, vBoxNumber++);
        }
    }
}

//----------------------------------------------------
void SixyBoard::createHBox(int j, int k, const int hBoxNumber){
    Square** squares = new Square*[6];
    int n = 0;
    for (int x = j; x < (j + 2); x++){
        for (int y = k; y < (k + 3); y++){
            squares[n++] = &sub(x, y);
        }
    }
    Cluster* cluster = new Cluster(typeCodes[ClusterType::HBox], squares, size, hBoxNumber);
    clusters.push_back(cluster);
}

//----------------------------------------------------
void SixyBoard::createVBox(int j, int k, const int vBoxNumber){
    Square** squares = new Square*[6];
    int n = 0;
    for (int x = j; x < (j + 3); x++){
        for (int y = k; y < (k + 2); y++){
            squares[n++] = &sub(x, y);
        }
    }
    Cluster* cluster = new Cluster(typeCodes[ClusterType::VBox], squares, size, vBoxNumber);
    clusters.push_back(cluster);
}