#include <iostream> 
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    std::cout << w.ws_col << ":" << w.ws_row << "\n";
    return 0;
}