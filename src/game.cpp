#include "game.hpp"

#include <iostream>

namespace flappyBird {
    Game::Game(GameInfo GameInfo) {
        gameinfo = GameInfo;
        int height = 4;
        int width = 10;

        int startx = (gameinfo.WIDTH - width) / 2;
        int starty = (gameinfo.HEIGHT - height) / 2;
        Point start{startx,starty};
        DrawSquare(start, width, height);

    }

    void Game::DrawSquare(Point start, int width, int height) {
        for (int i = 0; i < gameinfo.HEIGHT; i++) {
            for (int j = 0; j < gameinfo.WIDTH; j++) {
                if ((i >= start.y && i < height + start.y) && (j >= start.x && j < width + start.x)) {
                    std::cout << "#";
                } else {
                    std::cout << " ";
                }
            }
        }
    }
}