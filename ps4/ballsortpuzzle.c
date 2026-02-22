#define _DEFAULT_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h> //for usleep
#include <ncurses.h>
#include "ballsortpuzzle.h"

#define ANIM_DELAY 80000 




void generator(const int rows, const int columns, char field[rows][columns])
{
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < columns; j++) 
            field[i][j] = ' ';

    int empty_col1 = rand() % columns;
    int empty_col2 = rand() % columns;
    while (empty_col1 == empty_col2) empty_col2 = rand() % columns;

    const char ids[] = "ABCDEFGHI"; 
    int num_colors = columns - 2;
    if (num_colors > 9) num_colors = 9;

    char all_chars[rows * num_colors];
    int idx = 0;
    for (int s = 0; s < num_colors; s++)
        for (int r = 0; r < rows; r++)
            all_chars[idx++] = ids[s];

    for (int i = idx - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp = all_chars[i];
        all_chars[i] = all_chars[j];
        all_chars[j] = temp;
    }

    idx = 0;
    for (int j = 0; j < columns; j++)
    {
        if (j == empty_col1 || j == empty_col2) continue;
        for (int i = 0; i < rows; i++) field[i][j] = all_chars[idx++];
    }
}

int get_ball_color(char c)
{
    if (c == ' ') return 0;
    return (c - 'A') + 1; 
}


void draw_header()
{
    attron(A_BOLD | COLOR_PAIR(6)); 
    const char* title = "=== B A L L   S O R T   P U Z Z L E ===";
    mvprintw(2, (COLS - strlen(title)) / 2, "%s", title);
    attroff(A_BOLD | COLOR_PAIR(6));
}

// visual

void game_field(const int rows, const int columns, char field[rows][columns], int highlight_col)
{
    int tube_width = 5; 
    int space_between = 4; // Wider spacing looks better
    int total_width = (columns * tube_width) + ((columns - 1) * space_between);
    int total_height = rows + 1 + 2;

    int start_y = (LINES - total_height) / 2;
    int start_x = (COLS - total_width) / 2;
    
    
    if (start_y < 0) start_y = 0;
    if (start_x < 0) start_x = 0;

    int y = start_y;

    //DRAW TUBES
    for (int i = 0; i < rows; i++)
    {
        move(y, start_x);
        for (int j = 0; j < columns; j++)
        {
            
            int wall_color = (j + 1 == highlight_col) ? 7 : 6; // 7=White, 6=Cyan
            
            attron(COLOR_PAIR(wall_color) | A_BOLD);
            addch(ACS_VLINE); // │
            attroff(COLOR_PAIR(wall_color) | A_BOLD);

            printw(" ");
            
            // DRAW BALL
            char cell = field[i][j];
            if (cell != ' ')
            {
                int color = get_ball_color(cell);
                attron(COLOR_PAIR(color) | A_BOLD);
                printw("O"); 
                attroff(COLOR_PAIR(color) | A_BOLD);
            }
            else
            {
                printw(" ");
            }

            printw(" ");

            attron(COLOR_PAIR(wall_color) | A_BOLD);
            addch(ACS_VLINE); // │
            attroff(COLOR_PAIR(wall_color) | A_BOLD);
            
            printw("    "); // Spacing
        }
        y++;
    }

    //DRAW FLOORS
    move(y, start_x);
    for (int j = 0; j < columns; j++)
    {
        int wall_color = (j + 1 == highlight_col) ? 7 : 6;
        attron(COLOR_PAIR(wall_color) | A_BOLD);
        addch(ACS_LLCORNER); // └
        addch(ACS_HLINE);    // ─
        addch(ACS_HLINE);    // ─
        addch(ACS_HLINE);    // ─
        addch(ACS_LRCORNER); // ┘
        attroff(COLOR_PAIR(wall_color) | A_BOLD);
        printw("    ");
    }
    y++;

    //NUMBERS
    y++;
    move(y, start_x);
    attron(COLOR_PAIR(8)); // Greyish/Dim color for numbers
    for (int j = 1; j <= columns; j++)
    {
        printw("  %d      ", j);
    }
    attroff(COLOR_PAIR(8));
}

//falling ball
void animate_drop(const int rows, const int columns, char field[rows][columns], int col_idx, char ball, int target_row)
{
    
    int tube_width = 5; 
    int space_between = 4;
    int total_width = (columns * tube_width) + ((columns - 1) * space_between);
    int total_height = rows + 1 + 2;
    int start_y = (LINES - total_height) / 2;
    int start_x = (COLS - total_width) / 2;


    // X = start + (col_idx * (width + space)) + 2 (padding inside tube)
    int screen_x = start_x + (col_idx * (tube_width + space_between)) + 2;
    
    // Animate falling from top of tube down to target_row
    // Start slightly above the tube
    for (int r = -1; r <= target_row; r++)
    {
        int screen_y = start_y + r;
        
        // Draw Ball
        int color = get_ball_color(ball);
        attron(COLOR_PAIR(color) | A_BOLD);
        mvprintw(screen_y, screen_x, "O");
        attroff(COLOR_PAIR(color) | A_BOLD);
        
        refresh();
        usleep(ANIM_DELAY); // Wait

        // Erase Ball
        if (r < target_row)
        {
             mvprintw(screen_y, screen_x, " ");
        }
    }
}


void down_possible_animated(const int rows, const int columns, char field[rows][columns], int x, int y)
{
    if (x < 1 || x > columns || y < 1 || y > columns || x == y) {
        beep(); // Sound alert
        return;
    }

    int from = x - 1;
    int to = y - 1;
    int source_row = -1;
    char symbol = ' ';

    // Find Source
    for (int i = 0; i < rows; i++) {
        if (field[i][from] != ' ') {
            source_row = i;
            symbol = field[i][from];
            break;
        }
    }
    if (source_row == -1) { beep(); return; }

    // Find Dest
    int dest_top_row = -1;
    for (int i = 0; i < rows; i++) {
        if (field[i][to] != ' ') {
            dest_top_row = i;
            break;
        }
    }
    if (dest_top_row == 0) { beep(); return; }

    int target_row;
    if (dest_top_row == -1) target_row = rows - 1;
    else {
        if (field[dest_top_row][to] != symbol) { beep(); return; }
        target_row = dest_top_row - 1;
    }


    
  
    field[source_row][from] = ' ';
    
   // WITHOUT the ball 
    clear();
    draw_header();
    game_field(rows, columns, field, to + 1); // Highlight destination
    refresh();

    // Play Falling Animation at destination
    animate_drop(rows, columns, field, to, symbol, target_row);

    //Place in destination permanently
    field[target_row][to] = symbol;
}

bool check(const int rows, const int columns, char field[rows][columns])
{
    for (int j = 0; j < columns; j++) {
        if (field[rows - 1][j] == ' ') {
            for (int i = 0; i < rows; i++) if (field[i][j] != ' ') return false;
            continue;
        }
        char leader = field[rows - 1][j];
        for (int i = 0; i < rows; i++) if (field[i][j] != leader) return false;
    }
    return true;
}

//VICTORY ANIMATION
void celebrate()
{
    clear();
    const char *msg = "V I C T O R Y !";
    int start_y = LINES / 2;
    int start_x = (COLS - strlen(msg)) / 2;

    for (int k = 0; k < 5; k++) {
        // Flash text colors
        attron(A_BOLD | COLOR_PAIR((k % 5) + 1));
        mvprintw(start_y, start_x, "%s", msg);
        attroff(A_BOLD | COLOR_PAIR((k % 5) + 1));
        
        // Random fireworks
        int fy = rand() % LINES;
        int fx = rand() % COLS;
        mvaddch(fy, fx, '*');
        
        refresh();
        usleep(200000);
    }
    
    mvprintw(start_y + 2, start_x - 4, "Press any key to exit.");
    flushinp();
    getch();
}

void ball_sort_puzzle()
{
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_CYAN,    COLOR_BLACK); // For Tubes
        init_pair(7, COLOR_WHITE,   COLOR_BLACK); // For Highlights
        init_pair(8, COLOR_WHITE,   COLOR_BLACK); // For Numbers
    }

    const int rows = 4;
    const int columns = 4;
    char field[rows][columns];

    srand(time(NULL));
    generator(rows, columns, field);

    int from_col = 0;
    int to_col = 0;

    while (1)
    {
    
        clear();
        draw_header();
        game_field(rows, columns, field, -1); // -1 = No highlight
        
        //heck Win
        if (check(rows, columns, field))
        {
            celebrate();
            break;
        }

        
        int prompt_y = LINES - 4;
        mvprintw(prompt_y, (COLS/2)-10, "Select From: ");
        refresh();
        if (scanw("%d", &from_col) != 1) break;

        // Redraw with HIGHLIGHT
        clear();
        draw_header();
        game_field(rows, columns, field, from_col); // Highlight selected tube
        
        
        mvprintw(prompt_y + 1, (COLS/2)-10, "Select To:   ");
        refresh();
        if (scanw("%d", &to_col) != 1) break;

        // Logic & Animation
        down_possible_animated(rows, columns, field, from_col, to_col);
    }
}