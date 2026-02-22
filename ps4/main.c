#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "ballsortpuzzle.h"
#include "c4.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");
    // 1. Initialize Ncurses
    initscr();
    cbreak(); // Disable line buffering (pass input immediately)
    echo();   // ENABLE TYPING VISIBILITY (Fixes "doesn't show what I type")
    keypad(stdscr, TRUE); // Enable arrow keys if needed later

    int choice = 0;

    printw("Select Game:\n");
    printw("1. Ball Sort Puzzle\n");
    printw("2. Connect Four\n");
    printw("Choice: ");
    refresh(); // Push text to screen

    // 2. Get Input
    if (scanw("%d", &choice) != 1)
    {
        printw("Invalid input. Press any key.\n");
        refresh();
        getch();
        endwin();
        return 1;
    }

    // 3. Launch Games
    if (choice == 1)
    {
        ball_sort_puzzle();
    }
    else if (choice == 2)
    {
        play_connect_four();
    }
    else
    {
        printw("Unknown choice. Press any key.\n");
        refresh();
        flushinp();
        getch();
    }

    // 4. Cleanup
    endwin();
    return 0;
}