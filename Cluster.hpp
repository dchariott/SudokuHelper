//
// Created by Dylan Chariott on 9/30/19.
//

#pragma once
#include "Square.hpp"
#include "FileFormatException.hpp"

class Cluster {
private:
    const char* type;
    Square** squares;
    const int clusterSize;
    const int number;
public:
    ~Cluster(){
        delete [] squares;
    }
    Cluster(const char* type, Square**& squares, int clusterSize, int number);
    void shutOffLoop(char value) const;
    ostream& print(ostream& out) const;
    void checkForDuplicateValues() const;
};

inline ostream& operator<< (ostream& out, const Cluster& cl){
    return cl.print(out);
}


