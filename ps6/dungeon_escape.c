#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

#define MAX_H 30
#define MAX_W 100
#define VISIBILITY_RADIUS 9.0 
#define MAX_MONSTERS 10
#define FREEZE_DURATION 50 
#define MONSTER_SPEED 3 

#define C_WALL '1'
#define C_EXIT '2'
#define C_DOOR '3'
#define C_PORTAL_IN '4'
#define C_PORTAL_OUT '5'
#define C_SAFE '7'
#define C_BREAKABLE '8'
#define C_KEY '!'
#define C_WEAPON '@'
#define C_AMMO 'p'
#define C_MONSTER '~'
#define C_PLAYER 'o'

enum {
    PAIR_WALL = 1,      
    PAIR_FLOOR,         
    PAIR_PLAYER,        
    PAIR_MONSTER,       
    PAIR_GOLD,          
    PAIR_ITEM,          
    PAIR_DOOR,          
    PAIR_UI,            
    PAIR_SAFE_ZONE,     
    PAIR_PORTAL,        
    PAIR_BREAKABLE,
    PAIR_FROZEN,
    PAIR_MINIMAP_WALL,
    PAIR_MINIMAP_PLAYER,
    PAIR_MINIMAP_FLOOR,
    PAIR_VICTORY,
    PAIR_GAMEOVER,
    PAIR_DANGER_WALL,   
    PAIR_DANGER_FLOOR,
    PAIR_DANGER_UI
};

typedef struct {
    char tiles[MAX_H][MAX_W]; 
    int h, w;                 
} Map;

typedef struct {
    int x, y;          
    int active;        
    int frozen_timer;  
} Monster;

typedef struct {
    int x, y;
    int hp;
    int ammo;
    int has_weapon;
    int keys;
    int artifacts;
    int current_map_idx;
    int saved_x_map3, saved_y_map3;
} Player;

Map levels[4];
Monster monsters[MAX_MONSTERS];
int monster_count = 0;
Player p;
int game_over = 0;
int win = 0;
char message[100] = "Collect 3 Artifacts -> Exit";
int frame_counter = 0;

int start_y = 0;
int start_x = 0;

const char* map_files[] = {"map1", "map2", "map3", "map3next"};

void load_maps() {
    for (int m = 0; m < 4; m++) {
        FILE *f = fopen(map_files[m], "r");
        if (!f) { endwin(); printf("Error: Can't find file %s\n", map_files[m]); exit(1); }
        levels[m].h = 0; levels[m].w = 0;
        char buf[256];
        while(fgets(buf, sizeof(buf), f) && levels[m].h < MAX_H) {
            int len = strlen(buf);

            if (len > 0 && buf[len-1] == '\n') 
                buf[--len] = '\0';

            if (len > levels[m].w) 
                levels[m].w = len;

            strcpy(levels[m].tiles[levels[m].h], buf);
            levels[m].h++;
        }
        fclose(f);
    }
}

void init_level_objects(int map_idx) {
    monster_count = 0;
    Map *m = &levels[map_idx];

    for(int y=0; y < m->h; y++) {
        for(int x=0; x<m->w; x++) {
            char c = m->tiles[y][x];
            if (c == C_PLAYER) {
                p.x = x; p.y = y;
                m->tiles[y][x] = ' '; 
            } else if (c == C_MONSTER) {
                if (monster_count < MAX_MONSTERS) {
                    monsters[monster_count].x = x;
                    monsters[monster_count].y = y;
                    monsters[monster_count].active = 1;
                    monsters[monster_count].frozen_timer = 0;
                    monster_count++;
                }
                m->tiles[y][x] = ' ';
            }
        }
    }
}

int can_see(int r0, int c0, int r1, int c1) {
    int dr = abs(r1 - r0), dc = abs(c1 - c0);
    int sr = r0 < r1 ? 1 : -1, sc = c0 < c1 ? 1 : -1;
    int err = (dr > dc ? dr : -dc) / 2, e2;
    while (1) {
        if (r0 == r1 && c0 == c1) return 1;
        char t = levels[p.current_map_idx].tiles[r0][c0];
        if (t == C_WALL || t == C_DOOR || t == C_EXIT || t == C_BREAKABLE) return 0;
        e2 = err;
        if (e2 > -dr) { err -= dc; r0 += sr; }
        if (e2 < dc) { err += dr; c0 += sc; }
    }
    return 0;
}

int is_in_danger() {
    for (int i=0; i<monster_count; i++) {
        if (!monsters[i].active) continue;
        if (monsters[i].frozen_timer > 0) continue; 

        float dist = sqrt(pow(monsters[i].x - p.x, 2) + pow(monsters[i].y - p.y, 2));
        if (dist <= 10.0 && can_see(monsters[i].y, monsters[i].x, p.y, p.x)) {
            return 1;
        }
    }
    return 0; 
}

void update_monsters() {
    Map *m = &levels[p.current_map_idx];
    int player_is_safe = (m->tiles[p.y][p.x] == C_SAFE);

    for (int i=0; i<monster_count; i++) {
        if (!monsters[i].active) continue;
        if (monsters[i].frozen_timer > 0) {
            monsters[i].frozen_timer--;
            continue; 
        }

        int can_see_player = can_see(monsters[i].y, monsters[i].x, p.y, p.x);
        float dist = sqrt(pow(monsters[i].x - p.x, 2) + pow(monsters[i].y - p.y, 2));
        int dx = 0, dy = 0;

        if (dist <= 10.0 && can_see_player) {
            if (player_is_safe) {
                if (p.x > monsters[i].x) dx = -1; else if (p.x < monsters[i].x) dx = 1;
                if (p.y > monsters[i].y) dy = -1; else if (p.y < monsters[i].y) dy = 1;
            } else {
                if (p.x > monsters[i].x) dx = 1; else if (p.x < monsters[i].x) dx = -1;
                if (p.y > monsters[i].y) dy = 1; else if (p.y < monsters[i].y) dy = -1;
            }
        } else {
            int r = rand() % 4;
            if (r == 0) dx = 1; else if (r == 1) dx = -1; else if (r == 2) dy = 1; else dy = -1;
        }

        int nx = monsters[i].x + dx;
        int ny = monsters[i].y + dy;
        char t = m->tiles[ny][nx];

        int blocked = (t == C_WALL || t == C_DOOR || t == C_EXIT || t == C_SAFE || 
                       t == C_PORTAL_IN || t == C_PORTAL_OUT || t == C_BREAKABLE);
        for(int j=0; j<monster_count; j++) 
            if(i!=j && monsters[j].x == nx && monsters[j].y == ny) blocked = 1;

        if (!blocked) {
            monsters[i].x = nx;
            monsters[i].y = ny;
        }
        
        if (monsters[i].x == p.x && monsters[i].y == p.y) {
            game_over = 1; 
            strcpy(message, "KILLED BY MONSTER!");
        }
    }
}

void shoot(int dx, int dy) {
    if (!p.has_weapon) { strcpy(message, "No Weapon!"); return; }
    if (p.ammo <= 0) { strcpy(message, "No Ammo!"); return; }
    p.ammo--;
    strcpy(message, "BANG!");
    
    int bx = p.x, by = p.y;
    Map *m = &levels[p.current_map_idx];
    while(1) {
        bx += dx; by += dy;
        char t = m->tiles[by][bx];
        if (t == C_WALL || t == C_EXIT || t == C_DOOR) break;
        if (t == C_BREAKABLE) { m->tiles[by][bx] = ' '; strcpy(message, "Wall Destroyed!"); break; }
        
        int hit = 0;
        for(int i=0; i<monster_count; i++) {
            if (monsters[i].x == bx && monsters[i].y == by && monsters[i].active) {
                monsters[i].frozen_timer = FREEZE_DURATION;
                strcpy(message, "Enemy Frozen!");
                hit = 1;
                break;
            }
        }
        if (hit) break;
        if (abs(bx - p.x) > 20 || abs(by - p.y) > 20) break;
    }
}

void interact() {
    Map *m = &levels[p.current_map_idx];
    char t = m->tiles[p.y][p.x];
    if (strchr("$%&", t)) {
        p.artifacts++; m->tiles[p.y][p.x] = ' '; snprintf(message, 100, "Artifact %d/3", p.artifacts);
        if (p.artifacts >= 3) {
            strcat(message, " -> EXIT IS OPEN!");
        }
    } else if (t == C_KEY) {
        p.keys++; m->tiles[p.y][p.x] = ' '; strcpy(message, "Key Found.");
    } else if (t == C_WEAPON) {
        p.has_weapon = 1; p.ammo = 3; m->tiles[p.y][p.x] = ' '; strcpy(message, "Weapon Equipped!");
    } else if (t == C_AMMO) {
        if(p.has_weapon) { p.ammo = 3; m->tiles[p.y][p.x] = ' '; strcpy(message, "Reloaded."); }
    }
    int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    for(int i=0; i<4; i++) {
        int ny = p.y + dirs[i][1], nx = p.x + dirs[i][0];
        if (nx>=0 && nx<m->w && ny>=0 && ny<m->h && m->tiles[ny][nx] == C_DOOR) {
            if (p.keys > 0) { m->tiles[ny][nx] = ' '; strcpy(message, "Door Opened."); }
            else strcpy(message, "Locked (Need Key).");
        }
    }
}

void check_portals() {
    Map *m = &levels[p.current_map_idx];
    char t = m->tiles[p.y][p.x];
    if (t == C_PORTAL_IN) {
        p.saved_x_map3 = p.x; p.saved_y_map3 = p.y;
        p.current_map_idx = 3; init_level_objects(3);
        for(int y=0; y<levels[3].h; y++) for(int x=0; x<levels[3].w; x++)
            if(levels[3].tiles[y][x] == C_PORTAL_OUT) { p.x = x - 1; p.y = y; }
    }
    if (t == C_PORTAL_OUT) {
        p.current_map_idx = 2; p.x = p.saved_x_map3 + 1; p.y = p.saved_y_map3;
        init_level_objects(2);
    }
}

void draw_interface(int danger_mode) {
    int color = danger_mode ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_UI);
    
    int sidebar_x = start_x + (levels[p.current_map_idx].w * 2) + 2; 
    
    int header_x = start_x;
    
    attron(color);
    mvprintw(start_y - 6, header_x, "DUNGEON ESCAPE");
    mvprintw(start_y - 4, header_x, "HP:%d%% | Ammo:%d | Keys:%d | Arts:%d/3 | Wpn:%s", 
             p.hp, p.ammo, p.keys, p.artifacts, p.has_weapon ? "YES" : "NO");
    
    if (danger_mode) mvprintw(start_y - 2, header_x, "MSG: !!! RUN! MONSTER SEES YOU !!!");
    else mvprintw(start_y - 2, header_x, "MSG: %s", message);
    attroff(color);

    attron(color);
    mvprintw(start_y, sidebar_x, "CONTROLS:");
    mvprintw(start_y + 1, sidebar_x, "[ARROWS] Move");
    mvprintw(start_y + 2, sidebar_x, "[SPACE]  Shoot");
    mvprintw(start_y + 3, sidebar_x, "[E]      Action");
    mvprintw(start_y + 4, sidebar_x, "[Q]      Quit");

    int minimap_y = start_y + 7;
    int view_w = 20;    
    int view_h = 10;     
    Map *m = &levels[p.current_map_idx];

    mvprintw(minimap_y - 1, sidebar_x, "MINIMAP");
    
    for(int y=-1; y<=view_h; y++) {
        mvaddch(minimap_y + y, sidebar_x - 1, '|');
        mvaddch(minimap_y + y, sidebar_x + view_w, '|');
    }
    for(int x=0; x<view_w; x++) {
        mvaddch(minimap_y - 1, sidebar_x + x, '-');
        mvaddch(minimap_y + view_h, sidebar_x + x, '-');
    }
    attroff(color);

    int start_col = p.x - (view_w / 2);
    int start_row = p.y - (view_h / 2);
    if (start_col < 0) start_col = 0;
    if (start_row < 0) start_row = 0;
    if (start_col + view_w > m->w) start_col = m->w - view_w;
    if (start_row + view_h > m->h) start_row = m->h - view_h;
    if (start_col < 0) start_col = 0;
    if (start_row < 0) start_row = 0;

    for (int y = 0; y < view_h; y++) {
        for (int x = 0; x < view_w; x++) {
            int map_y = start_row + y;
            int map_x = start_col + x;
            int screen_y = minimap_y + y;
            int screen_x = sidebar_x + x;
            
            if (map_y >= m->h || map_x >= m->w) continue;

            if (map_x == p.x && map_y == p.y) {
                attron(COLOR_PAIR(PAIR_MINIMAP_PLAYER) | A_BOLD);
                mvaddch(screen_y, screen_x, '@');
                attroff(COLOR_PAIR(PAIR_MINIMAP_PLAYER) | A_BOLD);
            } 
            else if (m->tiles[map_y][map_x] == C_WALL || m->tiles[map_y][map_x] == C_EXIT) {
                int wall_color = danger_mode ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_MINIMAP_WALL);
                attron(wall_color);
                mvaddch(screen_y, screen_x, '#');
                attroff(wall_color);
            }
            else {
                attron(COLOR_PAIR(PAIR_MINIMAP_FLOOR));
                mvaddch(screen_y, screen_x, ' ');
                attroff(COLOR_PAIR(PAIR_MINIMAP_FLOOR));
            }
        }
    }
}

void calculate_center() {
    int map_w_pixels = levels[p.current_map_idx].w * 2;
    int map_h_pixels = levels[p.current_map_idx].h;
    
    int total_width = map_w_pixels + 25; 
    
    start_y = (LINES - map_h_pixels) / 2;
    start_x = (COLS - total_width) / 2;
    
    if (start_y < 8) start_y = 8; 
    if (start_x < 1) start_x = 1;
}

void show_victory_screen() {
    clear();
    int cy = LINES / 2;
    int cx = (COLS - 40) / 2;
    attron(COLOR_PAIR(PAIR_VICTORY) | A_BOLD);
    mvprintw(cy-3, cx, "***************************************");
    mvprintw(cy-2, cx, " ");
    mvprintw(cy-1, cx, "* CONGRATULATIONS! YOU WON!     *");
    mvprintw(cy,   cx, "* *");
    mvprintw(cy+1, cx, "* You have escaped the Dungeon.   *");
    mvprintw(cy+2, cx, "* *");
    mvprintw(cy+3, cx, "***************************************");
    attroff(COLOR_PAIR(PAIR_VICTORY) | A_BOLD);
    attron(COLOR_PAIR(PAIR_UI));
    mvprintw(cy+5, cx+5, "Press any key to exit...");
    attroff(COLOR_PAIR(PAIR_UI));
    refresh();
    timeout(-1);
    getch();
}

void show_gameover_screen() {
    clear();
    int cy = LINES / 2;
    int cx = (COLS - 30) / 2;
    attron(COLOR_PAIR(PAIR_GAMEOVER) | A_BOLD);
    mvprintw(cy-2, cx, "=========================");
    mvprintw(cy-1, cx, "|       GAME OVER       |");
    mvprintw(cy,   cx, "=========================");
    attroff(COLOR_PAIR(PAIR_GAMEOVER) | A_BOLD);
    mvprintw(cy+2, cx-5, "Reason: %s", message);
    mvprintw(cy+4, cx, "Press any key to exit...");
    refresh();
    timeout(-1);
    getch();
}

int main() {
    setlocale(LC_ALL, ""); 
    srand(time(NULL));
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100); 

    init_pair(PAIR_WALL, COLOR_WHITE, COLOR_WHITE); 
    
    init_pair(PAIR_FLOOR, COLOR_WHITE, COLOR_BLACK); 
    
    init_pair(PAIR_PLAYER, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PAIR_MONSTER, COLOR_RED, COLOR_BLACK);
    init_pair(PAIR_GOLD, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PAIR_ITEM, COLOR_CYAN, COLOR_BLACK);
    init_pair(PAIR_DOOR, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(PAIR_SAFE_ZONE, COLOR_GREEN, COLOR_BLACK);
    init_pair(PAIR_PORTAL, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(PAIR_BREAKABLE, COLOR_WHITE, COLOR_BLACK);
    init_pair(PAIR_FROZEN, COLOR_BLUE, COLOR_BLACK);
    init_pair(PAIR_UI, COLOR_WHITE, COLOR_BLACK);
    
    init_pair(PAIR_MINIMAP_WALL, COLOR_WHITE, COLOR_BLACK); 
    init_pair(PAIR_MINIMAP_PLAYER, COLOR_GREEN, COLOR_BLACK); 
    init_pair(PAIR_MINIMAP_FLOOR, COLOR_BLACK, COLOR_BLACK);
    
    init_pair(PAIR_VICTORY, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PAIR_GAMEOVER, COLOR_RED, COLOR_BLACK);

    init_pair(PAIR_DANGER_WALL, COLOR_RED, COLOR_RED);
    init_pair(PAIR_DANGER_FLOOR, COLOR_RED, COLOR_BLACK);
    init_pair(PAIR_DANGER_UI, COLOR_RED, COLOR_BLACK);

    load_maps();
    p.current_map_idx = 0; p.hp = 100; init_level_objects(0);

    int ch;
    while (!game_over && !win) {
        calculate_center();
        clear();
        Map *m = &levels[p.current_map_idx];

        int danger = is_in_danger();

        draw_interface(danger);

        for (int y = 0; y < m->h; y++) {
            for (int x = 0; x < m->w; x++) {
                float dist = sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
                int visible = (dist <= VISIBILITY_RADIUS) && can_see(p.y, p.x, y, x);
                
                int screen_y = start_y + y;
                int screen_x = start_x + (x * 2); 

                if (!visible) {
                    mvprintw(screen_y, screen_x, "  ");
                    continue;
                }

                char tile = m->tiles[y][x];
                
                if (tile == C_WALL) { 
                    int color = danger ? COLOR_PAIR(PAIR_DANGER_WALL) : COLOR_PAIR(PAIR_WALL);
                    attron(color); mvprintw(screen_y, screen_x, "  "); attroff(color);
                }
                else if (tile == C_SAFE) {
                    attron(COLOR_PAIR(PAIR_SAFE_ZONE)); mvprintw(screen_y, screen_x, ".."); attroff(COLOR_PAIR(PAIR_SAFE_ZONE));
                }
                else if (tile == C_DOOR) {
                    attron(COLOR_PAIR(PAIR_DOOR)); mvprintw(screen_y, screen_x, "[]"); attroff(COLOR_PAIR(PAIR_DOOR));
                }
                else if (tile == C_BREAKABLE) {
                    attron(COLOR_PAIR(PAIR_BREAKABLE) | A_DIM); mvprintw(screen_y, screen_x, "##"); attroff(COLOR_PAIR(PAIR_BREAKABLE) | A_DIM);
                }
                else if (tile == C_EXIT) {
                    attron(COLOR_PAIR(PAIR_WALL)); mvprintw(screen_y, screen_x, "EX"); attroff(COLOR_PAIR(PAIR_WALL));
                }
                else {
                    if (tile == C_KEY) { 
                        attron(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_ITEM)); 
                        mvprintw(screen_y, screen_x, "!!"); 
                        attroff(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_ITEM)); 
                    }
                    else if (strchr("$%&", tile)) { 
                        attron(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_GOLD) | A_BOLD); 
                        mvprintw(screen_y, screen_x, "$$"); 
                        attroff(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_GOLD) | A_BOLD); 
                    }
                    else if (tile == C_WEAPON) { 
                        attron(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_ITEM) | A_BOLD); 
                        mvprintw(screen_y, screen_x, "Wp"); 
                        attroff(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_ITEM) | A_BOLD); 
                    }
                    else if (tile == C_AMMO) { 
                        attron(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_ITEM)); 
                        mvprintw(screen_y, screen_x, "::"); 
                        attroff(danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_ITEM)); 
                    }
                    else if (tile == C_PORTAL_IN || tile == C_PORTAL_OUT) { 
                        attron(COLOR_PAIR(PAIR_PORTAL) | A_BLINK); mvprintw(screen_y, screen_x, "OO"); attroff(COLOR_PAIR(PAIR_PORTAL) | A_BLINK); 
                    }
                    else {
                        if (danger) {
                            attron(COLOR_PAIR(PAIR_DANGER_FLOOR)); 
                            mvprintw(screen_y, screen_x, " ."); 
                            attroff(COLOR_PAIR(PAIR_DANGER_FLOOR));
                        } else {
                            attron(COLOR_PAIR(PAIR_FLOOR) | A_DIM); 
                            mvaddch(screen_y, screen_x, ACS_CKBOARD); 
                            mvaddch(screen_y, screen_x+1, ACS_CKBOARD);
                            attroff(COLOR_PAIR(PAIR_FLOOR) | A_DIM);
                        }
                    }
                }
            }
        }

        int p_color = danger ? COLOR_PAIR(PAIR_DANGER_UI) : COLOR_PAIR(PAIR_PLAYER);
        attron(p_color | A_BOLD);
        mvprintw(start_y + p.y, start_x + (p.x * 2), "[]"); 
        attroff(p_color | A_BOLD);

        for(int i=0; i<monster_count; i++) {
            if(!monsters[i].active) continue;
            if(can_see(p.y, p.x, monsters[i].y, monsters[i].x) && 
               sqrt(pow(monsters[i].x - p.x, 2) + pow(monsters[i].y - p.y, 2)) <= VISIBILITY_RADIUS) {
                int color = (monsters[i].frozen_timer > 0) ? PAIR_FROZEN : PAIR_MONSTER;
                if(danger) color = COLOR_PAIR(PAIR_DANGER_UI);
                
                attron(color | A_BOLD);
                mvprintw(start_y + monsters[i].y, start_x + (monsters[i].x * 2), "MM");
                attroff(color | A_BOLD);
            }
        }

        ch = getch();
        frame_counter++;
        if (frame_counter >= MONSTER_SPEED) { update_monsters(); frame_counter = 0; }

        if (ch != ERR) {
            int dx = 0, dy = 0;
            if (ch == 'q') break;
            else if (ch == KEY_UP) dy = -1;
            else if (ch == KEY_DOWN) dy = 1;
            else if (ch == KEY_LEFT) dx = -1;
            else if (ch == KEY_RIGHT) dx = 1;
            else if (ch == 'e' || ch == 'E') interact();
            else if (ch == ' ') { 
                if (!p.has_weapon) { strcpy(message, "NEED WEAPON FIRST!"); }
                else if (p.ammo <= 0) { strcpy(message, "NO AMMO!"); }
                else {
                    strcpy(message, "AIMING... Press Arrow Key!");
                    draw_interface(danger);
                    timeout(-1); 
                    int dir = getch();
                    timeout(100); 
                    int sdx = 0, sdy = 0;
                    if (dir == KEY_UP) sdy = -1;
                    else if (dir == KEY_DOWN) sdy = 1;
                    else if (dir == KEY_LEFT) sdx = -1;
                    else if (dir == KEY_RIGHT) sdx = 1;
                    if (sdx || sdy) shoot(sdx, sdy);
                    else strcpy(message, "Shot Cancelled.");
                }
            }
            if (dx || dy) {
                int nx = p.x + dx, ny = p.y + dy;
                char t = m->tiles[ny][nx];

                if (t == C_EXIT) {
                    if (p.artifacts >= 3) {
                        if (p.current_map_idx < 2) {
                            p.current_map_idx++;
                            p.artifacts = 0; 
                            p.keys = 0; 
                            p.has_weapon = 0;
                            p.ammo = 0;
                            init_level_objects(p.current_map_idx);
                            strcpy(message, "LEVEL UP! Equipment Lost.");
                        } else {
                            win = 1;
                        }
                    } else {
                        strcpy(message, "Need 3 Artifacts!");
                    }
                }
                else if (t != C_WALL && t != C_DOOR && t != C_BREAKABLE) {
                    p.x = nx; p.y = ny;
                    check_portals();
                }
            }
        }
    }
    
    if (win) show_victory_screen();
    else show_gameover_screen();

    endwin();
    return 0;
}