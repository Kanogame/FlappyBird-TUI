#include <ncurses.h>

#define pipeSize 100
#define pipeXDelay 20
#define pipeYDelay 10
#define BirdX 5

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
            int PipesX;
            int BirdY;
            int BirdVelocity;
            int StartPipes;
            void InitializeGame(int *birdY, int *birdVelocity, int *pipesX, int *startPipes);
            void GameTick(int *birdY, int *birdVelocity, int *pipesX, int *collidePositions, int *score);
            void DrawMenu(MenuState *menuState, GameState *gameState, char *TopButton, char *BottomButton, const char *Title[], int titleLen);
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
            void DrawTitle(WINDOW *window, int x, int y, const char *title[], int titleLen);
            bool CollideCheck(int collidePositions, int score);
            int menuLen = 8;
            const char *menuTitle[8] = {
                " ______  _                               _      _           _ ",
                "|  ____|| |                             | |    (_)         | |",
                "| |__   | |  __ _  _ __   _ __   _   _  | |__   _  _ __  __| |",
                "|  __|  | | / _` || '_ \\ | '_ \\ | | | | | '_ \\ | || '__|/ _` |",
                "| |     | || (_| || |_) || |_) || |_| | | |_) || || |  | (_| |",
                "|_|     |_| \\__,_|| .__/ | .__/  \\__, | |_.__/ |_||_|   \\__,_|",
                "                  | |    | |      __/ |                       ",
                "                  |_|    |_|     |___/                        ",
            };

            int gameOverLen = 6;
            const char *gameOverTitle[6] = {
                " _____                                                   ",
                "/ ____|                                                  ",
                "| |  __   __ _  _ __ ___    ___    ___ __   __ ___  _ __ ",
                "| | |_ | / _` || '_ ` _ \\  / _ \\  / _ \\\\ \\ / // _ \\| '__|",
                "| |__| || (_| || | | | | ||  __/ | (_) |\\ V /|  __/| |   ",
                " \\_____| \\__,_||_| |_| |_| \\___|  \\___/  \\_/  \\___||_|   ",
            };
    };
}