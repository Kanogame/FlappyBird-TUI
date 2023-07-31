#include "game.hpp"
#include <thread>
#include<cstdlib>
#include <time.h>
#include <string.h>


namespace FlappyBird {
    Game::Game() {
        initscr();
        refresh();
        noecho();
        window = newwin(LINES, COLS - 1, 0, 0);
        PipesX = (int)(COLS / 2) / (pipeXDelay + 10) * (pipeXDelay + 10);
        StartPipes = PipesX;
        cbreak();
        wrefresh(window);
        GameState gameState = GameState::Menu;
        Gameloop(&gameState);
        endwin();
    }

    void Game::Gameloop(GameState *GameState) {
        switch (*GameState)
            {
            case GameState::Menu:{
                MenuState menuState;
                DrawMenu(&menuState);}
                break;
            case GameState::Game:
                nodelay(stdscr, TRUE);
                SetPipes();
                while (1) {
                    BirdJump();
                    BirdY += BirdVelocity;
                    BirdVelocity += 1;
                    PipesX -= 1;
                    int collidePositions =  (PipesX -StartPipes - 5) / (pipeXDelay + 10) - (PipesX -StartPipes + 5) / (pipeXDelay + 10);
                    int score = (-(PipesX -StartPipes - 5) / (pipeXDelay + 10)) - StartPipes / (pipeXDelay + 10);
                    RepaintReqaried(score + 1);
                    if (CollideCheck(collidePositions, score)) {
                        wclear(window);
                        return;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                break;
        }
    }

    void Game::DrawMenu(MenuState *menuState, GameState *gameState) {
        int menuWidth = 40;
        int menuHeight = 11;
        int menuY = LINES / 4 * 3 - menuHeight / 2;
        int menuX = AlignText(COLS, menuWidth);
        while (true) {
            wclear(window);
            DrawGameWindow(window);
            auto menuWindow = newwin(menuHeight, menuWidth, menuY, menuX);
            box(menuWindow, 0, 0);
            wrefresh(menuWindow);
            DrawButton(menuWidth - 4, menuY + 2, menuX + 2, "start", menuState->Start);
            DrawButton(menuWidth - 4, menuY + 6, menuX + 2, "start1", menuState->Exit);
            switch (getch())
            {
            case 'w': case 's':
                SwapState(&menuState->Start, &menuState->Exit);
                break;
            
            case 'd':
                if (menuState->Start == ButtonState::Active) {
                    GameState
                } else {
                    return;
                }
                break;
            };
        }
    }

    void Game::SwapState(ButtonState *state1, ButtonState *state2) {
        auto state = *state1;
        *state1 = *state2;
        *state2 = state;
    }

    void Game::DrawButton(int width, int y, int x, char *text, ButtonState buttonState) {
        auto buttonWindow = newwin(3, width, y, x); 
        switch (buttonState) {
        case ButtonState::Static:
            box(buttonWindow, 0, 0);
            break;
        
        case ButtonState::Active:
            box(buttonWindow, 103, 104);
            break;
        }
        mvwprintw(buttonWindow, 1, AlignText(width, strlen(text)), text);
        wrefresh(buttonWindow);
    }

    int Game::AlignText(int width, int textLen) {
        return width / 2 - textLen / 2;
    }

    void Game::SetPipes() {
        std::srand(time(NULL));
        for (int i = 0; i < pipeSize; i++) {
            int randPipe = std::rand()%(LINES - 9);
            pipes[i].pipeTop = randPipe + 2;
            pipes[i].pipeBottom = pipes[i].pipeTop + pipeYDelay;
        }
    }

    bool Game::CollideCheck(int collidePositions, int score) {
        if (BirdY >= LINES -1 || BirdY < 0) {
            return true;
        }
        if (collidePositions == -1 && score >= 0) {
            if (BirdY < pipes[score].pipeTop || BirdY > pipes[score].pipeBottom) {
                return true;
            }
        }
        return false;
    }

    void Game::RepaintReqaried(int score) {
        DrawGameWindow(window);
        DrawBird(BirdY);
        wrefresh(window);
        DrawPipes(pipes);
        DrawScore(score);
    }

    void Game::DrawGameWindow(WINDOW *gameWindow) {
        werase(window);
        box(window, 0, 0);
    }

    void Game::DrawScore(int score) {
        int Gamescore = score < 0 ? 0 : score;
        auto ScoreWindow = newwin(3, 11, 0, COLS / 2 - 5);
        box(ScoreWindow, 0, 0);
        int centerCol = ScoreWindow->_maxx / 2;
        int scoreLenght = sizeof(score) / sizeof(int);
        int ajCol = centerCol - scoreLenght;
        mvwprintw(ScoreWindow, 1, ajCol, "%d", score);
        wrefresh(ScoreWindow);
    }

    void Game::BirdJump() {
        if (getch() == 'w') {
            BirdVelocity = -3;
        } else {
            return;
        }
    }

    void Game::DrawPipes(Pipes pipes[]) {
        for (int i = 0; i < pipeSize; i++) {
            if (PipesX + ((pipeXDelay + 10) * i) > COLS) {
                continue;
            }
            pipes[i].pipeBottomWindow = newwin(LINES - 1, 10, pipes[i].pipeBottom, PipesX + ((pipeXDelay + 10) * i));
            pipes[i].pipeTopWindow = newwin(pipes[i].pipeTop, 10, 0, PipesX + ((pipeXDelay + 10) * i));
            box(pipes[i].pipeBottomWindow, 0,0);
            box(pipes[i].pipeTopWindow, 0,0);
            wrefresh(pipes[i].pipeBottomWindow);
            wrefresh(pipes[i].pipeTopWindow);
        }
    }

    void Game::DrawBird(int BirdPosition) {
        mvwprintw(window, BirdPosition, BirdX, "bird");
    }
}
