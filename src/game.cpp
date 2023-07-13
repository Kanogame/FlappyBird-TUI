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
            RepaintReqaried();
            if (CollideCheck()) {
                wclear(window);
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
        }
    }

    void Game::SetPipes() {
        for (int i = 0; i < sizeof(pipes) / sizeof(Pipes); i++) {
            int randPipe = std::rand()%(LINES - 6);
            pipes[i].pipeTop = randPipe;
            pipes[i].pipeBottom = randPipe + 6;
        }
    }

    bool Game::CollideCheck() {
        if (BirdY >= LINES -1 || BirdY < 0) {
            return true;
        }

        return false;
    }

    void Game::RepaintReqaried() {
        wclear(window);
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
        for (int i = 0; i < sizeof(pipes) / sizeof(Pipes); i++) {
            pipes[i].pipeTopWindow = newwin(0, pipes[i].pipeTop, 0, PipesX);
            box(pipes[i].pipeTopWindow, 0,0);
            wrefresh(pipes[i].pipeTopWindow);
        }
        
    }

    void Game::DrawBird(int BirdPosition) {
        mvwprintw(window, BirdPosition, 4, "bird");
    }
}