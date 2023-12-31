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
        cbreak();
        wrefresh(window);
        GameState gameState = GameState::Menu;
        while (gameState != GameState::Exit) {
            Gameloop(&gameState);
        }
        endwin();
    }

    void Game::DrawGameWindow(WINDOW *gameWindow) {
        werase(window);
        box(window, 0, 0);
    }

    void Game::Gameloop(GameState *GameState) {
        switch (*GameState)
            {
            case GameState::Menu:{
                MenuState menuState;
                DrawMenu(&menuState, GameState, "start", "exit", menuTitle, menuLen, true);}
                break;
            case GameState::Game:
                nodelay(stdscr, TRUE);
                SetPipes();
                InitializeGame(&BirdY, &BirdVelocity, &PipesX, &StartPipes);
                while (1) {
                    int score;
                    int collidePositions;
                    BirdJump();
                    GameTick(&BirdY, &BirdVelocity, &PipesX, &collidePositions, &score);
                    RepaintReqaried(score + 1);
                    if (CollideCheck(collidePositions, score)) {
                        wclear(window);
                        *GameState = GameState::Gameover;
                        return;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                break;
            case GameState::Gameover:{
                nodelay(stdscr, FALSE);
                MenuState menuState;
                DrawMenu(&menuState, GameState, "try again", "exit", gameOverTitle, gameOverLen, false);}
                break;
        }
    }

    void Game::InitializeGame(int *birdY, int *birdVelocity, int *pipesX, int *startPipes) {
        *birdY = LINES / 2;
        *pipesX = (int)(COLS / 2) / (pipeXDelay + 10) * (pipeXDelay + 10);
        *startPipes = *pipesX;
        *birdVelocity = 1;
    }

    void Game::GameTick(int *birdY, int *birdVelocity, int *pipesX, int *collidePositions, int *score) {
        *birdY += BirdVelocity;
        *birdVelocity += 1;
        *pipesX -= 1;
        *collidePositions =  (*pipesX -StartPipes - 5) / (pipeXDelay + 10) - (*pipesX -StartPipes + 5) / (pipeXDelay + 10);
        *score = (-(*pipesX -StartPipes - 5) / (pipeXDelay + 10)) - StartPipes / (pipeXDelay + 10);
    }

    void Game::RepaintReqaried(int score) {
        DrawGameWindow(window);
        DrawBird(BirdY);
        wrefresh(window);
        DrawPipes(pipes);
        DrawScore(score);
    }

    void Game::BirdJump() {
        if (getch() == 'w') {
            BirdVelocity = -3;
        } else {
            return;
        }
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

    void Game::DrawScore(int score) {
        int scoreWidth = 11;
        int scoreHeight = 3;
        Gamescore = score < 0 ? 0 : score;
        auto ScoreWindow = newwin(scoreHeight, scoreWidth, 0, COLS / 2 - 5);
        box(ScoreWindow, 0, 0);
        mvwprintw(ScoreWindow, 1, AlignText(scoreWidth, sizeof(Gamescore) / sizeof(int)), "%d", Gamescore);
        wrefresh(ScoreWindow);
    }
    
    void Game::DrawMenu(MenuState *menuState, GameState *gameState, char *TopButton, char *BottomButton, const char *Title[], int titleLen, bool isMenu) {
        int menuWidth = 40;
        int menuHeight = 11;
        int menuY = LINES / 4 * 3 - menuHeight / 2;
        int menuX = AlignText(COLS, menuWidth);
        while (true) {
            wclear(window);
            DrawGameWindow(window);
            auto menuWindow = newwin(menuHeight, menuWidth, menuY, menuX);
            box(menuWindow, 0, 0);
            if (!isMenu) {
                mvwprintw(window, LINES / 2, AlignText(COLS, sizeof(Gamescore) / sizeof(int) + 12), "Your score: %d", Gamescore);
            }
            DrawTitle(window, 3, AlignText(COLS, strlen(Title[0])), Title, titleLen);
            wrefresh(menuWindow);
            DrawButton(menuWidth - 4, menuY + 2, menuX + 2, TopButton, menuState->Start);
            DrawButton(menuWidth - 4, menuY + 6, menuX + 2, BottomButton, menuState->Exit);
            switch (getch())
            {
            case 'w': case 's':
                SwapState(&menuState->Start, &menuState->Exit);
                break;
            
            case 'd':
                if (menuState->Start == ButtonState::Active) {
                    *gameState = GameState::Game;
                } else {
                    *gameState = GameState::Exit;
                }
                return;
                break;
            };
        }
    }

    void Game::DrawTitle(WINDOW *window, int x, int y, const char *title[], int titleLen) {
        for (int i = 0; i < titleLen; i++) {
            mvwprintw(window, x + i, y, title[i]);
        }
        wrefresh(window);
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
            box(buttonWindow, 0, '=');
            break;
        }
        mvwprintw(buttonWindow, 1, AlignText(width, strlen(text)), text);
        wrefresh(buttonWindow);
    }

    int Game::AlignText(int width, int textLen) {
        return width / 2 - textLen / 2;
    }
}
