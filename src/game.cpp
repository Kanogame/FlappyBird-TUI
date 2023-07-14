#include "game.hpp"
#include <thread>
#include<cstdlib>


namespace FlappyBird {
    Game::Game() {
        initscr();
        refresh();
        noecho();
        window = newwin(LINES, COLS - 1, 0, 0);
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
            PipesX - 1;
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
        if (BirdY >= LINES -1 || BirdY < 0) {
            return true;
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
            pipes[i].pipeBottomWindow = newwin(LINES - 1, 10, pipes[i].pipeBottom, PipesX + ((pipeXDelay + PipesX) * i));
            box(pipes[i].pipeBottomWindow, 0,0);
        }

        for (int i = 0; i < pipeSize; i++) {
            pipes[i].pipeTopWindow = newwin(pipes[i].pipeTop, 10, 0, PipesX + ((pipeXDelay + PipesX) * i));
            box(pipes[i].pipeTopWindow, 0,0);
        }

        for (int i = 0; i < pipeSize; i++) {
            wrefresh(pipes[i].pipeBottomWindow);
            wrefresh(pipes[i].pipeTopWindow);
        }
    }

    void Game::DrawBird(int BirdPosition) {
        mvwprintw(window, BirdPosition, 4, "bird");
    }
}