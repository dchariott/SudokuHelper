#include "Game.hpp"

int main(int argc, char* argv[]) {
    banner();
    static const string fileName = (argc > 1)? argv[1] : "puzt.txt";
    Game game(fileName);
    game.run();
    bye();
    return 0;
}