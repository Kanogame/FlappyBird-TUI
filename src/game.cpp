#include "game.hpp"

#include <iostream>

namespace flappyBird {
    Game::Game(GameInfo gameInfo) {
        for (int i = 0; i < gameInfo.HEIGHT; i++) {
            for (int j = 0; j < gameInfo.WIDTH; j++) {
                std::cout << "#";
            }
        }
    }
}