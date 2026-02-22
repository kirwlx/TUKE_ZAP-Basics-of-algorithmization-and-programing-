// attron() & attroff() stands for attribute 
// attrset() overwrites all the attributes we have in the window

/* 
A_NORMAL        Normal display (no highlight)    
A_STANDOUT      Best highlighting mode of the terminal.    
A_UNDERLINE     Underlining    
A_REVERSE       Reverse video    
A_BLINK         Blinking    
A_DIM           Half bright    
A_BOLD          Extra bright or bold    
A_PROTECT       Protected mode    
A_INVIS         Invisible or blank mode    
A_ALTCHARSET    Alternate character set    
A_CHARTEXT      Bit-mask to extract a character
*/

#include <ncurses.h>

int main(){
    char * sentence[] = {"How", "is", "everybody", "doing", NULL};
    
    initscr();

    int i = 0;
    while(sentence[i]){
        if (i == 2){
            attron(A_UNDERLINE);
        }
        printw("%s ", sentence[i]);
        if(i == 2){
            attroff(A_UNDERLINE);
        }
        i++;
    }

    getch();

    endwin();
    return 0;
}