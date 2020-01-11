cmake_minimum_required(VERSION 3.13)
project(Sudoku_Helper)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sudoku_Helper main.cpp tools.cpp tools.hpp State.cpp State.hpp Board.cpp Board.hpp
               Game.cpp Game.hpp Cluster.cpp Cluster.hpp GamePlayException.hpp FileFormatException.hpp
               DiagonalBoard.cpp DiagonalBoard.hpp CanView.hpp Viewer.cpp Viewer.hpp GridChar.cpp GridChar.hpp
               MixedChar.cpp MixedChar.hpp Canvas.cpp Canvas.hpp Square.cpp Square.hpp Frame.hpp Stack.hpp Frame.cpp TraditionalBoard.cpp TraditionalBoard.hpp SixyBoard.cpp SixyBoard.hpp)