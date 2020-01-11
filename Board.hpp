//
// Created by Dylan Chariott on 9/16/19.
//

#pragma once
#include "Square.hpp"
#include "Cluster.hpp"
#include "CanView.hpp"
#include "Stack.hpp"
enum ClusterType{Row, Column, Box, Diagonal, HBox, VBox};

class Board : public CanView {
private:
    ifstream& gameInfo;
    void getPuzzle();
    void makeClusters();
    void createRow(int j);
    void createColumn(int k);
protected:
    int size;
    Square* bd;
    vector<Cluster*> clusters;
    const char* typeCodes[6] = {"Row", "Column", "Box", "Diagonal", "Horizontal Box", "Vertical Box"};
    virtual void makeBoxClusters() = 0;
public:
    Board(int size, ifstream& gameInfo, int clusterNum = 27);
    ~Board() override;
    Square& sub(const int j, const int k) const{
        return bd[(j - 1) * size + (k - 1)];
    }
    int index(const int j, const int k) const{
        return (j - 1) * size + (k - 1);
    }
    Square& operator[] (int index){
        return bd[index];
    }
    ostream& print(ostream& out) const;
    void mark(int row, int column, char value);
    char getMarkChar(const int row, const int col) const override{
        return bd[index(row, col)].getValue();
    }
    string getPossibilityString(const int row, const int col) const override{
        return bd[index(row, col)].getPossibilityString();
    }
    void turnOffPossibility(int row, int column, char value);
    void restoreState(const Frame* frame);
    void initialShutOffLoop();
};

inline ostream& operator<< (ostream& out, const Board& bd){
    return bd.print(out);
}

