#include "../types.hpp"

namespace flappyBird {
    class Drawer {
        public:
            Drawer(Window Window){
                DrawerWindow = Window;
            };
            void DrawRectangle(Point start, int width, int height);
            void DrawBird(int BirdPosition); 
        private: 
            Window &DrawerWindow;
    };
}