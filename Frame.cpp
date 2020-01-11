//
// Created by Dylan Chariott on 11/19/19.
//
#include "Frame.hpp"
#include "FileFormatException.hpp"

void Frame::serialize(ofstream & saveFile) const{
    int j = 0;
    for (const State& st : states){
        st.serialize(saveFile);
        if (++j > 8){
            saveFile << endl;
            j = 0;
        }
    }
}

void Frame::realize(ifstream& saveFile){
    int numberOfStates = 0;
    string legalValues = "123456789-";
    char value;
    while (!saveFile.eof()){
        saveFile >> value;
        if (saveFile.eof()) throw FileTooShortException(boardSize);
        if (legalValues.find_first_of(value) != string::npos){
            State st (value, sqrt(boardSize)); //boardSize = the total number of states not 6 or 9
            states.push_back(st);
            if (++numberOfStates == boardSize){
                saveFile >> value;
                if (!saveFile.eof()){
                    throw FileTooLongException(boardSize);
                }
            }
        }
        else{
            throw IllegalCharacterException(0, 0, value);
        }
    }
}
