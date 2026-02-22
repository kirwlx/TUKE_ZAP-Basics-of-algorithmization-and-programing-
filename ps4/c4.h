#ifndef C4_H
#define C4_H

// The main entry point for the game
void play_connect_four();

// Core logic functions
void initialize_board(int rows, int cols, char board[rows][cols]);
void print_board(int rows, int cols, const char board[rows][cols]); 
int is_valid_move(int rows, int cols, const char board[rows][cols], int col);

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece);
int is_board_full(int rows, int cols, const char board[rows][cols]);

#endif