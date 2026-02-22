//echo() -- keypresses are displayed in the terminal. Default
//noecho() -- keypressesare NOT displayed in the terminal 
//nodelay(win, TRUE) -- execution doesn't wait for user to provide an input function called such as getch(), getstr()
//nodelay(win, FALSE) -- default behavior
//clear() --> clears the window 



#include <ncurses.h>

int main(){
    int counter = 0;

    initscr();

    nodelay(stdscr, TRUE);
    while(getch() == ERR){ 
        counter++;
        printw("Program runs for %d seconds!\n", counter);
        refresh();
        napms(1000);
        clear();
        refresh();
    }
    nodelay(stdscr, FALSE);

    printw("You've pressed a key after %d seconds\n", counter);
    refresh();
    getch();

    endwin();
    return 0;
}
