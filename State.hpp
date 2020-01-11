//
// Created by Dylan Chariott on 2019-08-30.
//

#pragma once
#include "tools.hpp"
#include "GamePlayException.hpp"


class State{
private:
    int possibilities;
    int boardSize;
    string legalValues;
    char value;
public:
    State() = default;
    ~State() = default;
    State(char value, int boardSize);
    void mark(char value);
    ostream& print(ostream& out) const{
        return out << value << " Possibilities: " << getPossibilityString();
    }
    char getValue() const{
        return value;
    }
    string getPossibilityString() const;
    void turnOff(int n);
    ostream& serialize(ostream& out) const{
        return out << value;
    }
};

inline ostream& operator<< (ostream& out, const State& st){
    return st.print(out);
}
