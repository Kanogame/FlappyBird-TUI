#include "game.hpp"

#include <iostream>

namespace flappyBird {
    Game::Game(GameInfo gameInfo) {
        for (int i = 0; i < gameInfo.WIDTH; i++) {
            for (int j = 0; j < gameInfo.HEIGHT; j++) {
                if (i % 6 == 0) {
                    std::cout << "#";
                } else if (j % 6 == 0) {
                    std::cout << "#";
                } else {
                    std::cout << " ";
                }
            }
        }
    }
}