//
// Created by Dylan Chariott on 10/15/19.
//

#ifndef CPP__FILEFORMATEXCEPTION_HPP
#define CPP__FILEFORMATEXCEPTION_HPP
#include <utility>

#include "tools.hpp"

//================================
class FileFormatException : public exception{
public:
    FileFormatException() = default;
    ~FileFormatException() override = default;
    virtual void print() const = 0;
};

//================================
class IllegalTypeCodeException : public FileFormatException{
private:
    const char typeCode;
public:
    explicit IllegalTypeCodeException(const char typeCode): typeCode(typeCode) {}
    void print() const override{
        cerr << "The type codes stand for the variants of sudoku as follows: "
                "traditional, diagonal, and sixty." << endl
             << "The legal type code values are: t, d, and s. ";
        if (typeCode == ' '){
            cerr << "The type code was missing from the file. You must supply a legal type code.";
        }
        else{
            cerr << "Your supplied type code was: " << typeCode << ". You must supply a legal type code.";
        }
        exit(0);
    }
};

//==============================
class IllegalCharacterException : public FileFormatException{
private:
    const int row;
    const int column;
    const char value;
public:
    IllegalCharacterException(const int row, const int column, const char value): row(row), column(column), value(value)
    {}
    void print() const override{
        cerr << "An illegal character was encountered in the file at Square["
             << row << ", " << column << "]: "
             << value << ". The legal characters are: - and the digits from 1-9.";
        exit(0);
    }
};

//==============================
class FileTooLongException : public FileFormatException{
private:
    const int size;
public:
    explicit FileTooLongException(const int size): size(size) {}
    void print() const override{
        cerr << "The file that was supplied is too long. It should only allocate "
             << size << " squares.";
        exit(0);
    }
};

//=============================
class FileTooShortException: public FileFormatException{
private:
    const int size;
public:
    explicit FileTooShortException(const int size): size(size) {}
    void print() const override{
        cerr << "The file that was supplied is too short. It must allocate "
             << size << " squares.";
        exit(0);
    }
};

//==============================
class DuplicateClusterValueException: public FileFormatException{
private:
    const string clusterType;
    const char value;
    const int number;
public:
    DuplicateClusterValueException(string clusterType, const char value, const int number):
        clusterType(std::move(clusterType)), value(value), number(number) {}
    void print() const override{
        cerr << "There was a duplicate value found in " << clusterType << " " << number << ": " << value << ".";
        exit(0);
    }
};
#endif //CPP__FILEFORMATEXCEPTION_HPP
