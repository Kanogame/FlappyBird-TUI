#include <ncurses.h>

namespace FlappyBird {
    class Game {
        public:
            Game();
        private:
            WINDOW* window;
            int BirdY = 3;
            int BirdVelocity = 1;
            void Gameloop();
            void RepaintReqaried();
            void DrawBird(int BirdPosition);
            void BirdJump();
            bool CollideCheck();
    };
}