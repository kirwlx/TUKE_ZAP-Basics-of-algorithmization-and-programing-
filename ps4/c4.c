#define _DEFAULT_SOURCE // Fix for usleep

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> //for usleep
#include <ncurses.h>
#include "c4.h"

#define ANIM_DELAY 50000 // Microseconds for drop animation

void initialize_board(int rows, int cols, char board[rows][cols])
{
    for (int j = 0; j < cols; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            board[i][j] = '.';
        }
    }
}

//header visual
void draw_c4_header()
{
    if (has_colors()) {
        attron(A_BOLD | COLOR_PAIR(4)); // Cyan
    }
    const char* title = "=== C O N N E C T   F O U R ===";
    mvprintw(2, (COLS - strlen(title)) / 2, "%s", title);
    if (has_colors()) {
        attroff(A_BOLD | COLOR_PAIR(4));
    }
}

// visual
void print_board(int rows, int cols, const char board[rows][cols])
{
    // Calculate Centering
    int cell_width = 4; // "| O "
    int board_width = (cols * cell_width) + 1;
    int board_height = (rows * 2) + 1; // Rows + Separators
    
    int start_y = (LINES - board_height) / 2;
    int start_x = (COLS - board_width) / 2;
    
    if (start_y < 0) start_y = 0;
    if (start_x < 0) start_x = 0;

    int y = start_y;

    // Draw Top Line
    move(y, start_x);
    if (has_colors()) attron(COLOR_PAIR(3) | A_BOLD); // Blue Board
    addch(ACS_ULCORNER);
    for (int i = 0; i < cols; i++) {
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        if (i < cols - 1) addch(ACS_TTEE);
    }
    addch(ACS_URCORNER);
    if (has_colors()) attroff(COLOR_PAIR(3) | A_BOLD);
    y++;

    // Draw Rows
    for (int i = 0; i < rows; i++)
    {
        move(y, start_x);
        
        // Left Wall
        if (has_colors()) attron(COLOR_PAIR(3) | A_BOLD);
        addch(ACS_VLINE);
        if (has_colors()) attroff(COLOR_PAIR(3) | A_BOLD);

        for (int j = 0; j < cols; j++)
        {
            printw(" ");
            
            // Draw Piece
            char piece = board[i][j];
            if (piece == 'X') {
                if (has_colors()) attron(COLOR_PAIR(1) | A_BOLD); // Red
                addch('O'); 
                if (has_colors()) attroff(COLOR_PAIR(1) | A_BOLD);
            } else if (piece == 'O') {
                if (has_colors()) attron(COLOR_PAIR(2) | A_BOLD); // Yellow
                addch('O');
                if (has_colors()) attroff(COLOR_PAIR(2) | A_BOLD);
            } else {
                addch(' ');
            }
            
            printw(" ");

            // Separator Wall
            if (has_colors()) attron(COLOR_PAIR(3) | A_BOLD);
            addch(ACS_VLINE);
            if (has_colors()) attroff(COLOR_PAIR(3) | A_BOLD);
        }
        y++;

        // Grid
        if (i < rows - 1) {
            move(y, start_x);
            if (has_colors()) attron(COLOR_PAIR(3) | A_BOLD);
            addch(ACS_LTEE);
            for (int k = 0; k < cols; k++) {
                addch(ACS_HLINE);
                addch(ACS_HLINE);
                addch(ACS_HLINE);
                if (k < cols - 1) addch(ACS_PLUS);
            }
            addch(ACS_RTEE);
            if (has_colors()) attroff(COLOR_PAIR(3) | A_BOLD);
            y++;
        }
    }

    // Bottom Line
    move(y, start_x);
    if (has_colors()) attron(COLOR_PAIR(3) | A_BOLD);
    addch(ACS_LLCORNER);
    for (int i = 0; i < cols; i++) {
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        addch(ACS_HLINE);
        if (i < cols - 1) addch(ACS_BTEE);
    }
    addch(ACS_LRCORNER);
    if (has_colors()) attroff(COLOR_PAIR(3) | A_BOLD);
    y++;

    // Draw Numbers
    move(y, start_x);
    if (has_colors()) attron(COLOR_PAIR(5)); // Grey numbers
    for (int k = 1; k <= cols; k++) {
        printw("  %d ", k);
    }
    if (has_colors()) attroff(COLOR_PAIR(5));
}

// anim
void animate_c4_drop(int rows, int cols, const char board[rows][cols], int target_col, int target_row, char piece)
{
    int cell_width = 4;
    int board_width = (cols * cell_width) + 1;
    int board_height = (rows * 2) + 1;
    
    int start_y = (LINES - board_height) / 2;
    int start_x = (COLS - board_width) / 2;
    if (start_y < 0) start_y = 0;
    if (start_x < 0) start_x = 0;

    int screen_x = start_x + 1 + (target_col * 4) + 1;

    // Animate falling
    for (int r = 0; r <= target_row; r++)
    {
        int screen_y = start_y + 1 + (r * 2); 
        int prev_y = (r == 0) ? (start_y - 1) : (start_y + 1 + ((r-1) * 2));

        if (prev_y >= start_y + 1) {
             mvaddch(prev_y, screen_x, ' ');
        }

        int color = (piece == 'X') ? 1 : 2;
        if (has_colors()) attron(COLOR_PAIR(color) | A_BOLD);
        mvaddch(screen_y, screen_x, 'O');
        if (has_colors()) attroff(COLOR_PAIR(color) | A_BOLD);

        refresh();
        usleep(ANIM_DELAY);
    }
}

int is_valid_move(int rows, int cols, const char board[rows][cols], int col)
{
    if (col >= 0 && col < cols && board[0][col] == '.')
    {
        return 1;
    }
    return 0;
}


int get_drop_row(int rows, int cols, const char board[rows][cols], int col)
{
    for (int i = rows - 1; i >= 0; i--)
    {
        if (board[i][col] == '.')
        {
            return i;
        }
    }
    return -1;
}


int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece)
{
    int r = get_drop_row(rows, cols, board, col);
    if (r != -1) board[r][col] = player_piece;
    return r;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece)
{
    int dr[] = {0, 1, -1, 1};
    int dc[] = {1, 0, 1, 1};

    for (int d = 0; d < 4; d++)
    {
        int count = 1;
        for (int k = 1; k < 4; k++)
        {
            int r = row + k * dr[d];
            int c = col + k * dc[d];
            if (r >= 0 && r < rows && c >= 0 && c < cols && board[r][c] == player_piece)
                count++;
            else
                break;
        }
        for (int k = 1; k < 4; k++)
        {
            int r = row - k * dr[d];
            int c = col - k * dc[d];
            if (r >= 0 && r < rows && c >= 0 && c < cols && board[r][c] == player_piece)
                count++;
            else
                break;
        }
        if (count >= 4) return 1;
    }
    return 0;
}

int is_board_full(int rows, int cols, const char board[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (board[i][j] == '.') return 0;
        }
    }
    return 1;
}

void celebrate_c4()
{
    const char *msg = "V I C T O R Y !";
    int start_y = LINES / 2;
    int start_x = (COLS - strlen(msg)) / 2;

    for (int k = 0; k < 6; k++) {
        attron(A_BOLD | COLOR_PAIR((k % 2) + 1)); // Flash Red/Yellow
        mvprintw(start_y, start_x, "%s", msg);
        attroff(A_BOLD | COLOR_PAIR((k % 2) + 1));
        refresh();
        usleep(200000);
    }
    mvprintw(start_y + 2, start_x - 4, "Press any key to exit.");
    flushinp();
    getch();
}

void play_connect_four()
{
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);    // Player 1 (X)
        init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Player 2 (O)
        init_pair(3, COLOR_BLUE, COLOR_BLACK);   // Board
        init_pair(4, COLOR_CYAN, COLOR_BLACK);   // Header
        init_pair(5, COLOR_WHITE, COLOR_BLACK);  // Text/Numbers
    }

    int rows = 6;
    int cols = 7;
    char board[rows][cols];

    initialize_board(rows, cols, board);

    int turn = 0;
    int game_over = 0;

    while (!game_over)
    {
        clear(); 
        draw_c4_header();
        print_board(rows, cols, board);
        refresh();

        int player_idx = (turn % 2) + 1;
        char player_piece = (player_idx == 1) ? 'X' : 'O';
        int col;

        int prompt_y = LINES - 3;
        int prompt_x = (COLS / 2) - 15;
        
        if (has_colors()) attron(A_BOLD | COLOR_PAIR(player_idx));
        mvprintw(prompt_y, prompt_x, "Player %d, select column: ", player_idx);
        if (has_colors()) attroff(A_BOLD | COLOR_PAIR(player_idx));
        
        refresh();

        if (scanw("%d", &col) != 1) {
            continue;
        }

        col--; 

        if (col >= 0 && col < cols && is_valid_move(rows, cols, board, col))
        {
            
            int row = get_drop_row(rows, cols, board, col);
            
            //  Animation
            animate_c4_drop(rows, cols, board, col, row, player_piece);
            
            
            drop_piece(rows, cols, board, col, player_piece);

            if (check_win(rows, cols, board, row, col, player_piece))
            {
                clear();
                draw_c4_header();
                print_board(rows, cols, board);
                celebrate_c4();
                game_over = 1;
            }
            else if (is_board_full(rows, cols, board))
            {
                clear();
                draw_c4_header();
                print_board(rows, cols, board);
                mvprintw(LINES/2, (COLS/2)-6, "IT'S A DRAW!");
                refresh();
                flushinp();
                getch();
                game_over = 1;
            }
            turn++;
        }
        else
        {
            mvprintw(prompt_y + 1, prompt_x, "Invalid move! Try again.");
            refresh();
            usleep(500000); 
        }
    }
}