
#include <iostream> 
#include <ncurses.h>

int main() {
    initscr();
    refresh();

    WINDOW *board = newwin(LINES - 1, COLS - 1, 0, 0);
    mvwprintw(board, 2, 2, "%d:%d", LINES, COLS);
    box(board, 0, 0);
    wrefresh(board);
    getch();
    endwin();
    return 0;
}