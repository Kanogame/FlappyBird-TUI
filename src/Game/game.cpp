#include "game.hpp"
#include "../Drawer/drawer.hpp"

#include <iostream>

namespace flappyBird {
    Game::Game(GameInfo GameInfo) {
        gameInfo = GameInfo;
        //int height = 4;
        //int width = 10;
        //int startx = (gameinfo.WIDTH - width) / 2;
        //int starty = (gameinfo.HEIGHT - height) / 2;
        //Point start{startx,starty};
        //DrawSquare(start, width, height);
        GameLoop(gameInfo);
    }

    void Game::GameLoop() {
        while (true) {
            DrawNewFrame(gameInfo);
        } 
    }

    void DrawNewFrame(GameInfo gameInfo) {
        Drawer drawer{gameInfo};

    }
}