#Dependecy Generation (in directory with makefile): c++ -MM *.cpp >> Makefile

CXX = g++

CXXFLAGS = -std=c++14 -g -Wall -O1

OBJ = Board.o Canvas.o Cluster.o DiagonalBoard.o Frame.o Game.o GridChar.o main.o MixedChar.o SixyBoard.o Square.o \
	  State.o tools.o TraditionalBoard.o Viewer.o

TARGETS = Sudoku_Helper

.PHONY: all clean

all: $(TARGETS)

Sudoku_Helper: $(OBJ)
		$(CXX) -o $@ $(CXXFLAGS) $(OBJ)

clean:
		rm -f $(OBJ) $(TARGETS)

#Dependencies:-----------------------------------------------------------
Board.o: Board.cpp Board.hpp Square.hpp State.hpp tools.hpp \
  GamePlayException.hpp Cluster.hpp FileFormatException.hpp CanView.hpp \
  Stack.hpp Frame.hpp
Canvas.o: Canvas.cpp Canvas.hpp MixedChar.hpp tools.hpp GridChar.hpp
Cluster.o: Cluster.cpp Cluster.hpp Square.hpp State.hpp tools.hpp \
  GamePlayException.hpp FileFormatException.hpp
DiagonalBoard.o: DiagonalBoard.cpp DiagonalBoard.hpp TraditionalBoard.hpp \
  Board.hpp Square.hpp State.hpp tools.hpp GamePlayException.hpp \
  Cluster.hpp FileFormatException.hpp CanView.hpp Stack.hpp Frame.hpp
Frame.o: Frame.cpp Frame.hpp State.hpp tools.hpp GamePlayException.hpp \
  FileFormatException.hpp
Game.o: Game.cpp Game.hpp tools.hpp DiagonalBoard.hpp \
  TraditionalBoard.hpp Board.hpp Square.hpp State.hpp \
  GamePlayException.hpp Cluster.hpp FileFormatException.hpp CanView.hpp \
  Stack.hpp Frame.hpp SixyBoard.hpp Viewer.hpp
GridChar.o: GridChar.cpp tools.hpp GridChar.hpp
MixedChar.o: MixedChar.cpp tools.hpp MixedChar.hpp
SixyBoard.o: SixyBoard.cpp SixyBoard.hpp Board.hpp Square.hpp State.hpp \
  tools.hpp GamePlayException.hpp Cluster.hpp FileFormatException.hpp \
  CanView.hpp Stack.hpp Frame.hpp
Square.o: Square.cpp Square.hpp State.hpp tools.hpp GamePlayException.hpp \
  Cluster.hpp FileFormatException.hpp
State.o: State.cpp State.hpp tools.hpp GamePlayException.hpp
TraditionalBoard.o: TraditionalBoard.cpp TraditionalBoard.hpp Board.hpp \
  Square.hpp State.hpp tools.hpp GamePlayException.hpp Cluster.hpp \
  FileFormatException.hpp CanView.hpp Stack.hpp Frame.hpp
Viewer.o: Viewer.cpp Viewer.hpp CanView.hpp Canvas.hpp MixedChar.hpp \
  tools.hpp GridChar.hpp
main.o: main.cpp Game.hpp tools.hpp DiagonalBoard.hpp \
  TraditionalBoard.hpp Board.hpp Square.hpp State.hpp \
  GamePlayException.hpp Cluster.hpp FileFormatException.hpp CanView.hpp \
  Stack.hpp Frame.hpp SixyBoard.hpp Viewer.hpp
tools.o: tools.cpp tools.hpp
