#include "../Game/game.hpp"

namespace flappyBird {
    class Drawer {
        public:
            Drawer(GameInfo gameinfo);
            void DrawRectangle(Point start, int width, int height);
    };
}