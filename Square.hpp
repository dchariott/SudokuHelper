//
// Created by Dylan Chariott on 11/2/19.
//

#pragma once
#include "State.hpp"
class Cluster;

class Square{
private:
    State state;
    int row;
    int column;
    int boardSize;
    vector<Cluster*> clues;
    friend class Board;
    void setState(const State& st){
        state = st;
    }
public:
    Square() = default;
    ~Square() = default;
    Square(const char value, const int row, const int column, const int boardSize):
           state(value, boardSize), row(row), column(column), boardSize(boardSize){}
    ostream& print(ostream& out) const{
        out << "Square [" << row << ", " << column << "]: ";
        return state.print(out);
    }
    void mark(char value);
    char getValue() const{
        return state.getValue();
    }
    string getPossibilityString() const{
        return state.getPossibilityString();
    }
    void addCluster(Cluster* cl){
        clues.push_back(cl);
    }
    void turnOff(const int n){
        state.turnOff(n);
    }
    void shutOffLoop(char value) const;
    State getState() const{
        return state;
    }
};

inline ostream& operator<< (ostream& out, const Square& sq){
    return sq.print(out);
}



