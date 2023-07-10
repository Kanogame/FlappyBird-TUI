#include "game.hpp"
#include "../Drawer/drawer.hpp"

#include <iostream>
#include <thread>

namespace flappyBird {
    Game::Game(GameInfo GameInfo) {
        gameInfo = GameInfo;
        GameLoop();
    }

    void Game::GameLoop() {
        while (true) {
            runTick();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Game::runTick() {
        gameInfo.BirdPosition *= gameInfo.BirdVelocity;
        gameInfo.BirdVelocity *= 1.1;
    }
}