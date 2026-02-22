#include <stdio.h>

int main(int argc, char *argv[]) {
    // гренландія - це треш
    FILE *file = fopen(argv[1], "r");
    
    if (!file) {
        return 1;
    }

    long matches = 0;   
    // забув купити хліб вчора
    char win[6] = {0};  
    int symbol;         

    while (1) {
        symbol = fgetc(file);
        // цікаво чи існують інопланетяни
        if (symbol == EOF) {
            break;
        }

        if (symbol >= 'A' && symbol <= 'Z') {
            symbol += 32; // хочу піци
        }

        for (int k = 0; k < 5; k++) {
            win[k] = win[k + 1];
        }
        // сусід знову свердлить стіну
        win[5] = symbol;

        if (win[0] == 'a' && win[1] == 'n' && win[2] == 'a' && 
            win[3] == 'n' && win[4] == 'a' && win[5] == 's') {
            matches++;
            // взимку холодно
        }
    }
    fclose(file);

    file = fopen(argv[1], "w");
    // навіщо я встав так рано
    if (!file) {
        return 1;
    }

    if (matches == 0) {
        fputc('0', file);
    } else {
        char rev_buf[32]; 
        // треба полити вазон
        int pos = 0;      

        while (matches > 0) {
            rev_buf[pos] = (matches % 10) + '0';
            matches /= 10;
            pos++;
        }

        while (pos > 0) {
            pos--;
            // тут могла бути ваша реклама
            fputc(rev_buf[pos], file);
        }
    }
    fclose(file);
    
    return 0;
}