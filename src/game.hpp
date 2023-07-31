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
        Gameover,
        Exit,
    };

    enum class ButtonState {
        Static,
        Active
    };

    struct MenuState {
        ButtonState Start = ButtonState::Active;
        ButtonState Exit = ButtonState::Static;
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
            int PipesX;
            int BirdY;
            int BirdX = 5;
            int BirdVelocity = 1;
            int StartPipes;
            void InitializeGame();
            void GameTick();
            void DrawMenu(MenuState *menuState, GameState *gameState);
            void Gameloop(GameState *GameState);
            void RepaintReqaried(int score);
            void DrawGameWindow(WINDOW *window);
            void SwapState(ButtonState *state1, ButtonState *state2);
            void DrawButton(int width, int y, int x, char *text, ButtonState buttonState);
            int AlignText(int width, int textLen);
            void SetPipes();
            void ResetPipes(Pipes Oldpipes[]);
            void DrawBird(int BirdPosition);
            void DrawPipes(Pipes pipes[]);
            void DrawScore(int score);
            void BirdJump();
            bool CollideCheck(int collidePositions, int score);
    };
}