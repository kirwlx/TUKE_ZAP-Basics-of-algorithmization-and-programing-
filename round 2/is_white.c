#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int is_white(const char c);

int main() {

    printf("%i %i\n", is_white('a'), is_white(' '));
    return 0;
}

int is_white(const char c) {
    if (c == ' ' || c == '\t' || c == '\n') {
        return 1;
    }else {
        return 0;
    }
}

