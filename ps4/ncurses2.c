#include <ncurses.h>

int main()
{

    char text[] = "My name is John and I'm doing well\n";
    char *p = text;

    initscr();

    while (*p) {
        addch(*(p));
        refresh();
        p++;
        napms(200); //delay
    }

    getch();
    endwin();

    return 0;
}