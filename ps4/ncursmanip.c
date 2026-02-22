// getyx(win, row, col) --> current cursor position
// move(row, col) --> move the cursor to desired position
// getmaxyx (win, row, col) --> terminal screen size

#include <ncurses.h>
#include <string.h>


int main(){
    char text[] = "Hello World!";
    int len = strlen(text);

    initscr();

    int row, col;
    getmaxyx(stdscr, row, col);
    int cursor_position = (col/2) - (len/2);
    move((row / 2)-1, cursor_position);
    printw("%s", text);

    bkgd('~');
    refresh();
    getch();

    endwin();

    return 0;
}