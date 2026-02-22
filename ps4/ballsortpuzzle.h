#ifndef BALLSORTPUZZLE_H
#define BALLSORTPUZZLE_H

#include <stdbool.h>

void generator(const int rows, const int columns, char field[rows][columns]);
// down_possible isn't used externally in the main loop anymore (replaced by animated version), 
// but we keep it or replace it depending on your main implementation.
// However, looking at your .c file, you created 'down_possible_animated'. 
// If main.c calls ball_sort_puzzle(), we don't strictly need to expose the internal helper functions 
// unless main.c calls them directly. 
// Assuming ball_sort_puzzle() is the entry point called by main.c:

void ball_sort_puzzle();

// If you need these exposed for testing:
void down_possible_animated(const int rows, const int columns, char field[rows][columns], int x, int y);
bool check(const int rows, const int columns, char field[rows][columns]);

// UPDATED SIGNATURE:
void game_field(const int rows, const int columns, char field[rows][columns], int highlight_col);

#endif