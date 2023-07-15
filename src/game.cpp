#include "game.hpp"
#include <thread>
#include<cstdlib>


namespace FlappyBird {
    Game::Game() {
        initscr();
        refresh();
        noecho();
        window = newwin(LINES, COLS - 1, 0, 0);
        PipesX = COLS / 2;
        cbreak();
        nodelay(stdscr, TRUE);
        wrefresh(window);
        Gameloop();
        endwin();
    }

    void Game::Gameloop() {
        SetPipes();
        while (true) {
            BirdJump();
            BirdY += BirdVelocity;
            BirdVelocity += 1;
            PipesX -= 1;
            RepaintReqaried();
            if (CollideCheck()) {
                wclear(window);
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Game::SetPipes() {
        std::srand(123);
        for (int i = 0; i < pipeSize; i++) {
            int randPipe = std::rand()%(LINES - 6);
            pipes[i].pipeTop = randPipe;
            pipes[i].pipeBottom = randPipe + pipeYDelay;
        }
    }

    bool Game::CollideCheck() {
        int collidePosition = (PipesX - COLS / 2 - 10) / (pipeXDelay + 10) -  (PipesX - COLS / 2) / (pipeXDelay + 10);
        int pipeNumber = -(PipesX - COLS / 2 - 10) / (pipeXDelay + 10) - 2;
        if (BirdY >= LINES -1 || BirdY < 0) {
            return true;
        }
        if (collidePosition == -1 && pipeNumber >= 0) {
            if (BirdY < pipes[pipeNumber].pipeTop || BirdY > pipes[pipeNumber].pipeBottom) {
                return true;
            }
        }
        return false;
    }

    void Game::RepaintReqaried() {
        werase(window);
        box(window, 0, 0);
        DrawBird(BirdY);
        wrefresh(window);
        DrawPipes(pipes);
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
            if ((PipesX + ((pipeXDelay + 10) * i)) > COLS) {
                pipes[i].pipeBottomWindow = newwin(LINES - 1, 10, pipes[i].pipeBottom, PipesX + ((pipeXDelay + 10) * i));
                pipes[i].pipeTopWindow = newwin(pipes[i].pipeTop, 10, 0, PipesX + ((pipeXDelay + 10) * i));
                box(pipes[i].pipeBottomWindow, 0,0);
                box(pipes[i].pipeTopWindow, 0,0);
            } else {
                return;
            }
        }

        for (int i = 0; i < pipeSize; i++) {
            if (pipes[i].pipeBottomWindow != NULL && pipes[i].pipeTopWindow != NULL) {
                wrefresh(pipes[i].pipeBottomWindow);
                wrefresh(pipes[i].pipeTopWindow);
            }
        }
    }

    void Game::DrawBird(int BirdPosition) {
        mvwprintw(window, BirdPosition, BirdX, "bird");
    }
}