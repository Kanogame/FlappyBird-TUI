#include "game.hpp"
#include <thread>


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
        auto pipe = newwin(0, 10, LINES - 9, PipesX);
        box(pipe, 0,0);
        wrefresh(pipe);
    }

    void Game::DrawBird(int BirdPosition) {
        mvwprintw(window, BirdPosition, 4, "bird");
    }
}