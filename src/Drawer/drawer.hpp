#include "../types.hpp"

namespace flappyBird {
    class Drawer {
        public:
            Drawer(Window &Window);
            void DrawRectangle(Point start, int width, int height);
        private: 
            Window &DrawerWindow;
    };
}