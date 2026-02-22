#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void string_to_upper(char string[]);

int main() {



    return 0;
}

void string_to_upper(char string[]) {
    if (string == NULL) {
        return;
    }
    for (int i = 0; i < strlen(string); i++) {
        if (islower(string[i]) == 1) {
            string[i] = toupper(string[i]);
        }
    }

}