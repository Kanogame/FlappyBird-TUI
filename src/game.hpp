#include <ncurses.h>

namespace FlappyBird {
    struct Pipes {
        int pipeTop;
        int pipeBottom;
        WINDOW* pipeTopWindow;
        WINDOW* pipeBottomWindow;
    };

    class Game {
        public:
            Game();
        private:
            WINDOW* window;
            Pipes pipes[3];
            int PipesX = 10;
            int BirdY = 3;
            int BirdVelocity = 1;
            void Gameloop();
            void RepaintReqaried();
            void SetPipes();
            void DrawBird(int BirdPosition);
            void DrawPipes(Pipes pipes[]);
            void BirdJump();
            bool CollideCheck();
    };
}