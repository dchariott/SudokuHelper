//
// Created by Dylan Chariott on 11/2/19.
//

#include "Square.hpp"
#include "Cluster.hpp"

//---------------------------------------------------------------------------------------
void Square::mark(const char value){
    state.mark(value);
    shutOffLoop(value);
}

//---------------------------------------------------------------------------------------
void Square::shutOffLoop(const char value) const{
    for (Cluster* cl : clues){
        cl->shutOffLoop(value);
    }
}