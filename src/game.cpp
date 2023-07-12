#include "game.hpp"
#include <thread>


namespace FlappyBird {
    Game::Game() {
        initscr();
        refresh();
        noecho();
        window = newwin(LINES - 1, COLS - 1, 0, 0);
        cbreak();
        nodelay(stdscr, TRUE);
        wrefresh(window);
        Gameloop();
        endwin();
    }

    void Game::Gameloop() {
        while (true) {
            BirdJump();
            BirdY += BirdVelocity;
            BirdVelocity += 1;
            RepaintReqaried();
            if (CollideCheck()) {
                wclear(window);
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    bool Game::CollideCheck() {
        if (BirdY >= LINES -1) {
            return true;
        }

        return false;
    }

    void Game::RepaintReqaried() {
        wclear(window);
        box(window, 0, 0);
        DrawBird(BirdY);
        wrefresh(window);
        //DrawPipes();
    }

    void Game::BirdJump() {
        if (getch() == 'w') {
            BirdVelocity = -2;
        } else {
            return;
        }
    }

    void Game::DrawBird(int BirdPosition) {
        mvwprintw(window, BirdPosition, 4, "bird");
    }
}