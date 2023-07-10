#include "Game/game.hpp"

#include <iostream> 
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    flappyBird::GameInfo gameinfo;
    gameinfo.HEIGHT = w.ws_row;
    gameinfo.WIDTH = w.ws_col;
    gameinfo.BirdPosition = 10;

    flappyBird::Game game{gameinfo};

    int test;
    std::cin >> test;
    return 0;
}