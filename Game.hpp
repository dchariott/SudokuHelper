//
// Created by Dylan Chariott on 9/16/19.
//

#pragma once
#include "tools.hpp"
#include "DiagonalBoard.hpp"
#include "SixyBoard.hpp"
#include "Viewer.hpp"

class Game {
private:
    const char* menu[7] = {"Mark", "Undo", "Redo", "Save game", "Load game", "Turn off possibility for neighbors",
                           "Quit and discard game"};
    const char* legalChoices = "MmUuRrSsLlTtQq";
    Board* board;
    int size;
    char type;
    Stack undo;
    Stack redo;
    void pushCurrentFrame();
    static tuple<int, int, char> getUserInput();
    void undoLastMove();
    void redoLastMove();
    void load(ifstream& saveFile);
public:
    explicit Game(const string& fileName);
    ~Game(){
        delete board;
    }
    void run();
    ostream& print(ostream& out) const{
        return board->print(out);
    }
};

inline ostream& operator<< (ostream& out, const Game& gm){
    return gm.print(out);
}

