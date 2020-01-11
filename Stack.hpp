//
// Created by Dylan Chariott on 11/6/19.
//

#pragma once
#include <vector>
#include "Frame.hpp"

class Stack : private vector<Frame*>{
public:
    ~Stack(){
        zap();
    }
    void pop(){
        pop_back();
    }
    Frame* top() const{
        return back();
    }
    void push(Frame* frame){
        push_back(frame);
    }
    int size() const {
        return vector::size();
    }
    bool isEmpty() const{
        return empty();
    }
    void zap(){
        while (!empty()){
            delete back();
            pop_back();
        }
    }
};