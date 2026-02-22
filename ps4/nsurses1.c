#include <ncurses.h>

int main()
{

    initscr();

    addstr("Hello World!\n");
    refresh();

    getch(); // scanf for char to hold the ncurses session just to see smths
    endwin();

    return 0;
}