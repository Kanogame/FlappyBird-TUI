#include <ncurses.h>

namespace FlappyBird {
    struct Pipes {
        int pipeTop;
        int pipeBottom;
        WINDOW* pipeTopWindow;
        WINDOW* pipeBottomWindow;
    };

    enum class GameState {
        Menu,
        Game,
        Gameover
    };

    enum class MenuButton {
        Start,
        Exit
    };

    enum class ButtonState {
        Static,
        Active,
        Pressed
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
            int StartPipes;
            void DrawMenu(GameState *GameState);
            void Gameloop(GameState *GameState);
            void RepaintReqaried(int score);
            void DrawGameWindow(WINDOW *window);
            void DrawButton(int width, int x, int y, char *text, ButtonState buttonState);
            void SetPipes();
            void ResetPipes(Pipes Oldpipes[]);
            void DrawBird(int BirdPosition);
            void DrawPipes(Pipes pipes[]);
            void DrawScore(int score);
            void BirdJump();
            bool CollideCheck(int collidePositions, int score);
    };
}