//
// Created by Dylan Chariott on 2019-08-30.
//

#include "State.hpp"

//-------------------------------------
State::State(const char value, const int boardSize): value(value), boardSize(boardSize),
             legalValues((boardSize == 6)? "123456-" : "123456789-"){
    if (isdigit(value)){
        possibilities = 0;
    }
    else {
        this->value = '-';
        possibilities = 0x3fe;
    }
}

//--------------------------------------
void State::mark(const char newValue){
    if(legalValues.find_first_of(value) != string::npos){
        const int valueInt = newValue - '0';
        int mask = 1 << valueInt;
        if ((mask & possibilities) == 0) throw ImpossibleValueException(newValue);
        value = newValue;
        possibilities = 0;
    }
    else{
        throw IllegalValueException(newValue);
    }
}

//-----------------------------------------
void State::turnOff(const int n){
    int mask = ~(1 << n);
    possibilities &= mask;
}

//-----------------------------------------
string State::getPossibilityString() const{
    int mask = 0x1;
    int digit = 0;
    string possibilityString;
    for (int n = 1; n <= boardSize; n++){
        mask <<= 1;
        digit = mask & possibilities;
        if (digit == 0){
            possibilityString += '-';
        }
        else{
            possibilityString += to_string(n);
        }
    }
    return possibilityString;
}