#include "game.hpp"

#include <iostream> 
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    flappyBird::GameInfo gameinfo;
    gameinfo.HEIGHT = w.ws_col;
    gameinfo.WIDTH = w.ws_row;

    flappyBird::Game game{gameinfo};

    int test;
    std::cin >> test;
    return 0;
}