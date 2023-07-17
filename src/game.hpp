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
            Pipes pipes[100];
            int pipeSize = 100;
            int pipeOffset = 0;
            int pipeXDelay = 20;
            int pipeYDelay = 10;
            int PipesX = 0;
            int BirdY = 3;
            int BirdX = 5;
            int BirdVelocity = 1;
            void Gameloop();
            void RepaintReqaried();
            void SetPipes();
            void ResetPipes(Pipes Oldpipes[]);
            void DrawBird(int BirdPosition);
            void DrawPipes(Pipes pipes[]);
            void DrawScore(int score);
            void BirdJump();
            bool CollideCheck();
    };
}