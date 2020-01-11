//
// Created by Dylan Chariott on 11/6/19.
//

#pragma once
#include "State.hpp"

class Frame {
private:
    vector<State> states;
    int boardSize;
public:
    Frame(vector<State>& states, const int boardSize): states(states), boardSize(boardSize){}
    ~Frame() = default;
    State operator[](const int index) const{
        return states[index];
    }
    int size() const{
        return boardSize;
    }
    void serialize(ofstream& saveFile) const;
    void realize(ifstream& saveFile);
};



