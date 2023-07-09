#include "drawer.hpp"

namespace flappyBird {
    void Drawer::DrawSquare(Point start, int width, int height) {
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
