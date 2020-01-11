//
// Created by Dylan Chariott on 9/16/19.
//

#include "Board.hpp"

//---------------------------------------------------
Board::Board(const int size, ifstream& gameInfo, const int clusterSize): size(size), gameInfo(gameInfo){
    clusters.reserve(clusterSize);
    cerr << "The board is being constructed." << endl;
    bd = new Square[size * size];
    getPuzzle();
    makeClusters();
    initialShutOffLoop();
}

//---------------------------------------------------
Board::~Board(){
    cerr << "The board is being deleted." << endl;
    delete [] bd;
}

//---------------------------------------------------
void Board::initialShutOffLoop(){
    for (int l = 0; l < (size * size); ++l){
        if (!isdigit(bd[l].getValue())) continue;
        bd[l].shutOffLoop(bd[l].getValue());
    }
}

//---------------------------------------------------
ostream& Board::print(ostream& out) const{
    for (Cluster* cl : clusters){
        cl->print(out);
    }
    return out << endl;
}

//----------------------------------------------------
void Board::getPuzzle(){
    const int numberOfSquares = size * size;
    short j = 1, k = 1;
    const string legalValues = (size == 6)? "123456-":"123456789-";
    char value = ' ';

    while (!gameInfo.eof()){
        gameInfo >> value;
        if (gameInfo.eof()) throw FileTooShortException(numberOfSquares);
        if (legalValues.find_first_of(value) != string::npos){
            bd[index(j, k)] = Square(value, j ,k, size);
            if (k == size){
                if (j == size){
                    gameInfo >> value;
                    if (!gameInfo.eof()){
                        throw FileTooLongException(numberOfSquares);
                    }
                }
                else{
                    ++j;
                    k = 1;
                }
            }
            else{
                ++k;
            }
        }
        else{
            throw IllegalCharacterException(j, k, value);
        }
    }
}

//--------------------------------------------------
void Board::makeClusters(){
    for (int j = 1; j <= size; ++j){
        createRow(j);
    }
    for (int k = 1; k <= size; ++k){
        createColumn(k);
    }
}

//---------------------------------------------------
void Board::createRow(int j){
    Square** squares = new Square*[size];
    int n = 0;
    for (int k = 1; k <= size; ++k){
        squares[n++] = &sub(j, k);
    }
    Cluster* cluster = new Cluster(typeCodes[ClusterType::Row], squares, size, j);
    clusters.push_back(cluster);
}

//---------------------------------------------------
void Board::createColumn(int k){
    Square** squares = new Square*[size];
    int n = 0;
    for (int j = 1; j <= size; ++j){
        squares[n++] = &sub(j, k);
    }
    Cluster* cluster = new Cluster(typeCodes[ClusterType::Column], squares, size, k);
    clusters.push_back(cluster);
}

//-----------------------------------------------------
void Board::mark(const int row, const int column, const char value){
    if (!(1 <= row && row <= size) || !(1 <= column && column <= size)){
        throw IllegalPositionException(row, column, size);
    }
    sub(row, column).mark(value);
}

//----------------------------------------------------
void Board::restoreState(const Frame* frame){
    for (int n = 0; n < frame->size(); n++){
        bd[n].setState((*frame)[n]);
    }
    //this is needed to catch any duplicate values added by a modification to the save file
    for (Cluster* cluster : clusters){
        cluster->checkForDuplicateValues();
    }
}

//-----------------------------------------------------
void Board::turnOffPossibility(const int row, const int column, const char value){
    if (!(1 <= row && row <= size) || !(1 <= column && column <= size)){
        throw IllegalPositionException(row, column, size);
    }
    State savedState = sub(row, column).getState();
    sub(row, column).shutOffLoop(value);
    sub(row, column).setState(savedState);
}
