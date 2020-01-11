//
// Created by Dylan Chariott on 9/30/19.
//

#include "Cluster.hpp"
//------------------------------------------------------------------------
Cluster::Cluster(const char* clusterType, Square**& squares, const int clusterSize, const int number):
                 type(clusterType), squares(squares), clusterSize(clusterSize), number(number){
    checkForDuplicateValues();
    for (int n = 0; n < clusterSize; n++){
        this->squares[n]->addCluster(this);
    }
}

//------------------------------------------------------------------------
ostream& Cluster::print(ostream& out) const{
    out << "Cluster: " << type << " " << number << endl;
    for (int n = 0; n < clusterSize; ++n){
        squares[n]->print(out);
        out << endl;
    }
    return out << endl;
}

//------------------------------------------------------------------------
void Cluster::shutOffLoop(const char value) const{
    int valueInt = value - '0';
    for (int n = 0; n < clusterSize; ++n){
        squares[n]->turnOff(valueInt);
    }
}

//------------------------------------------------------------------------
void Cluster::checkForDuplicateValues() const{
    string seenValues;
    for (int n = 0; n < clusterSize; ++n){
        const char value = squares[n]->getValue();
        if (seenValues.find_first_of(value) != string::npos){
            throw DuplicateClusterValueException(type, value, number);
        }
        if (isdigit(value)) seenValues += value;
    }
}