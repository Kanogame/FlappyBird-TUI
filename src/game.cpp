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
            case GameState::Menu:
                DrawMenu(GameState);
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

    void Game::DrawMenu(GameState *GameState) {
        DrawGameWindow(window);
        DrawButton(11, LINES / 2, COLS / 2, "start", ButtonState::Static);
    }

    void Game::DrawButton(int width, int x, int y, char *text, ButtonState buttonState) {
        auto buttonWindow = newwin(3, width, x, y); 
        switch (buttonState) {
        case ButtonState::Static:
            box(buttonWindow, 0, 0);
            mvwprintw(buttonWindow, 1, AlignText(width, strlen(text)), text);
            wrefresh(buttonWindow);
            break;
        
        default:
            break;
        }
        getch();
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
