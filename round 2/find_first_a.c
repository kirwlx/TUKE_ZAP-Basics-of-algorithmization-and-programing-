#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int find_first_A(const char string[]);

int main() {
    printf("%d\n", find_first_A("Tomorrow afternoon"));
    return 0;
}

int find_first_A(const char string[]) {
    if (string == NULL) {
        return -1;
    }

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == 'A' || string[i] == 'a') {
            return i;
        }
    }
}