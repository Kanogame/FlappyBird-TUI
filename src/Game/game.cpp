#include "game.hpp"

#include <iostream>
#include <thread>

namespace flappyBird {
    Game::Game(GameInfo GameInfo) {
        gameInfo = GameInfo;
        GameLoop();
    }

    void Game::GameLoop() {
        while (true) {
            RunTick();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Game::RunTick() {
        Drawer Drawer{gameInfo.ClientWindow};
        Drawer.DrawBird(gameInfo.BirdPosition);
        gameInfo.BirdPosition *= gameInfo.BirdVelocity;
        gameInfo.BirdVelocity *= 1.1;
    }
}