#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int count_whites(const char string[]);

int main() {
    const char string[] = "Hello, how are you?";
    printf("%d\n", count_whites(string));
    return 0;
}

int count_whites(const char string[]) {
    int count = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == ' ' || string[i] == '\n' || string[i] == '\t') {
            count++;
        }else {
            continue;
        }
    }
    return count;
}