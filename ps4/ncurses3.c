#include <ncurses.h>

//getch() getstr(str) (safer --- getnstr(str, size))


int main(){
    int size = 32;
    char fname[size];
    char lname[size];

    initscr();

    addstr("Your first name: ");
    refresh();
    getnstr(fname, size - 1);

    addstr("Your last name: ");
    refresh();
    getnstr(lname, size - 1); 

    printw("Pleased to meet you %s %s\n", fname, lname);
    getch();

    endwin();

    return 0;
}