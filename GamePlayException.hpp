//
// Created by Dylan Chariott on 10/15/19.
//

#ifndef CPP__GAMEPLAYEXCEPTION_HPP
#define CPP__GAMEPLAYEXCEPTION_HPP
#include "tools.hpp"

//============================
class GamePlayException : public exception{
public:
    GamePlayException() = default;
    ~GamePlayException() override = default;
    virtual void print() const = 0;
};

//============================
class IllegalValueException : public GamePlayException{
private:
    const char value;
public:
    explicit IllegalValueException(const char value): value(value){}
    void print() const override{
        cerr << value << " is not a legal value for a square. The legal values are"
        << " the digits from 1-9. Please try again." << endl;
    }
};

//============================
class ImpossibleValueException : public GamePlayException{ //the value is legal but not in the possibility list
private:
    const char value;
public:
    explicit ImpossibleValueException(const char value): value(value){}
    void print() const override{
        cerr << value << " is not a possible value for this square. Try a different value." << endl;
    }
};

//============================
class IllegalPositionException : public GamePlayException{
private:
    const int row;
    const int column;
    const int size;
public:
    IllegalPositionException(const int row, const int column, const int size):
                            row(row), column(column), size(size) {}
    void print() const override{
        cerr << "[" << row << ", " << column << "] is not a valid position "
        << "on the board. Row and Column values can only go from 1-" << size << "respectively. "
        << "Please try again." << endl;
    }
};

#endif //CPP__GAMEPLAYEXCEPTION_HPP
