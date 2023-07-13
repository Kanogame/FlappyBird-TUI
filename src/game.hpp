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
            Pipes pipes[10];
            int pipeSize = 10;
            int pipeXDelay = 10;
            int pipeYDelay = 10;
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