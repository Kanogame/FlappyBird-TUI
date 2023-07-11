#include "game.hpp"
#include <thread>


namespace FlappyBird {
    Game::Game() {
        initscr();
        refresh();
        noecho();

        window = newwin(LINES - 1, COLS - 1, 0, 0);
        wrefresh(window);
        Gameloop();
        getch();
        endwin();
    }

    void Game::Gameloop() {
        while (true) {
            BirdJump();
            RepaintReqaried();
            BirdY += BirdVelocity;
            BirdVelocity += 1;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void Game::RepaintReqaried() {
        wclear(window);
        box(window, 0, 0);
        DrawBird(BirdY);
        wrefresh(window);
        //DrawPipes();
    }

    void Game::BirdJump() {
        int ch;

        switch (ch = getch())
        {
            case 'w':
                break;
            default:
                break;
        }
    }

    void Game::DrawBird(int BirdPosition) {
        mvwprintw(window, BirdPosition, 4, "bird");
    }
}