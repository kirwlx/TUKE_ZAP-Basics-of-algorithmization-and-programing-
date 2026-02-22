#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void change_whites(char string[]);

int main() {
    char str[] = "Hello World!";
    change_whites(str);
    printf("%s\n", str);
    return 0;
}

void change_whites(char string[]) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ' ' || string[i] == '\n') {
            string[i] = '.';
        }else {
            continue;
        }
    }
}