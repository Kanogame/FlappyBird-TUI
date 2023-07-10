#include "drawer.hpp"

#include <iostream>

namespace flappyBird {

    void Drawer::DrawBird(int BirdPosition) {
        DrawRectangle(Point{10, BirdPosition}, 10, 4);
    }

    void Drawer::DrawRectangle(Point start, int width, int height) {
        for (int i = 0; i < DrawerWindow.clientHeight; i++) {
            for (int j = 0; j < DrawerWindow.clientWidth; j++) {
                if ((i >= start.y && i < height + start.y) && (j >= start.x && j < width + start.x)) {
                    std::cout << "#";
                } else {
                    std::cout << " ";
                }
            }
        }
    }
}
