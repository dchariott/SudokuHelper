//
// Created by Dylan Chariott on 9/16/19.
//

#include "Game.hpp"

//-------------------------------------------------------------
Game::Game(const string& fileName){
    const string legalType = "tds";
    ifstream gameInfo(fileName);
    if (!gameInfo.is_open()){
        cerr << "The puzzle file was not found. The program will terminate." << endl;
        exit(0);
    }
    char typeCode = ' ';
    gameInfo >> typeCode;
    if (legalType.find_first_of(typeCode) == string::npos) throw IllegalTypeCodeException(typeCode);
    size = (typeCode == 's')? 6 : 9;
    type = typeCode;

    try{
        if (type == 't'){
            board = new TraditionalBoard(size, gameInfo);
        }
        else if (type == 'd'){
            board = new DiagonalBoard(size, gameInfo);
        }
        else{
            board = new SixyBoard(size, gameInfo);
        }
    }catch (FileFormatException& fe){
        fe.print();
    }

    gameInfo.close();
    pushCurrentFrame();
}

//-------------------------------------------------------------
void Game::run(){
    char choice, value;
    string fileName;
    ofstream boardData("board-output.txt");
    ofstream saveFile;
    ifstream loadFile;
    tuple<int, int, char> userInput;
    int row = 0, column = 0;
    Viewer boardView(size, size, *board);
    boardData << "Initial Board State: " << endl << *board;
    for(;;){
        boardView.show(cout);
        choice = _tolower(menu_c("Sudoku", 6, menu, legalChoices));
        switch(choice){
            case 'm':
                try{
                    userInput = getUserInput();
                    row = get<0>(userInput);
                    column = get<1>(userInput);
                    value = get<2>(userInput);
                    board->mark(row, column, value);
                    boardData << "Marking Square[" << row << ", " << column << "] with "
                              << value << "." << endl;
                    boardData << *board;
                    pushCurrentFrame();
                }catch (GamePlayException& ge){
                    ge.print();
                }
                break;
            case 'u':
                undoLastMove();
                boardData << "Attempting to undo the last move." << endl;
                boardData << *board;
                break;
            case 'r':
                redoLastMove();
                boardData << "Attempting to redo the last move." << endl;
                boardData << *board;
                break;
            case 's':
                cout << "Enter the name of the save file: " << endl;
                cin >> fileName;
                saveFile.open(fileName);
                undo.top()->serialize(saveFile);
                saveFile.close();
                break;
            case 'l':
                cout << "Enter the name of the save file: " << endl;
                cin >> fileName;
                loadFile.open(fileName);
                if(!loadFile.is_open()){
                    cerr << "The save file was not found." << endl;
                    break;
                }
                try{
                    load(loadFile);
                    loadFile.close();
                }catch(FileFormatException& fe){
                    cerr << "The save file has been corrupted. The program will terminate." << endl;
                    fe.print();
                }
                break;
            case 't':
                userInput = getUserInput();
                row = get<0>(userInput);
                column = get<1>(userInput);
                value = get<2>(userInput);
                board->turnOffPossibility(row, column, value);
                boardData << "Turning off " << value << " for neighbors of Square["
                          << row << ", " << column << "]." << endl;
                boardData << *board;
                pushCurrentFrame();
                break;
            case 'q':
                cout << "Thank you for playing Sudoku. The game is now ending." << endl;
                return;
        }
    }
}

//----------------------------------------------------
void Game::undoLastMove(){
    if (undo.size() < 2){
        cerr << "There aren't any moves to undo." << endl;
        return;
    }
    redo.push(undo.top());
    undo.pop();
    board->restoreState(undo.top());
}

//----------------------------------------------------
void Game::redoLastMove(){
    if (redo.isEmpty()){
        cerr << "There aren't any moves to redo." << endl;
        return;
    }
    undo.push(redo.top());
    board->restoreState(redo.top());
    redo.pop();
}

//-------------------------------------------------------
void Game::load(ifstream& saveFile){
    const int numberOfSquares = size * size;
    redo.zap();
    undo.zap();
    vector<State> states;
    states.reserve(numberOfSquares);
    Frame* loadFrame = new Frame(states, numberOfSquares);
    loadFrame->realize(saveFile);
    undo.push(loadFrame);
    board->restoreState(loadFrame);
    board->initialShutOffLoop();
}

//-----------------------------------------------------
void Game::pushCurrentFrame(){
    const int numberOfSquares = size * size;
    vector<State> currentState;
    currentState.reserve(numberOfSquares);
    for (int n = 0; n < numberOfSquares; ++n){
        currentState.push_back((*board)[n].getState());
    }
    Frame* currentFrame = new Frame(currentState, numberOfSquares);
    undo.push(currentFrame);
    redo.zap();
}

//-----------------------------------------------------
tuple<int, int, char> Game::getUserInput(){
    int row = 0, column = 0;
    char value = ' ';
    cout << "Enter the row number (1 - 9): ";
    cin >> row;
    if (cin.fail()){
        cout << "You must enter a number from 1 - 9 for the row." << endl;
        cin.clear();
        cin.ignore();
        return make_tuple(0, 0, '0'); //this will cause the calling function to throw an IllegalPositionException
    }
    cout << "Enter the column number (1 - 9): ";
    cin >> column;
    if (cin.fail()){
        cout << "You must enter a number from 1 - 9 for the column." << endl;
        cin.clear();
        cin.ignore();
        return make_tuple(0, 0, '0');
    }
    cout << "Enter the value (1 - 9): ";
    cin >> value;
    return make_tuple(row, column, value);
}