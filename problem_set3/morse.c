#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "morse.h"

// A single list containing A-Z (0-25) AND 0-9 (26-35)
const char *TABLE[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", // A-J
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",   // K-T
    "..-", "...-", ".--", "-..-", "-.--", "--..",                          // U-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." // 0-9
};

int is_morse_code_valid(const char morse[]) {
    char temp[1000];
    if (strlen(morse) >= 1000) return 0;
    strcpy(temp, morse);

    char *chunk = strtok(temp, " \n\t\r");
    while (chunk != NULL) {
        int valid = 0;

        if (strcmp(chunk, "/") == 0) {
            valid = 1;
        } else {
            // Simple loop checking the combined table
            for (int i = 0; i < 36; i++) {
                if (strcmp(TABLE[i], chunk) == 0) {
                    valid = 1;
                    break;
                }
            }
        }

        if (!valid) return 0;
        chunk = strtok(NULL, " \n\t\r");
    }
    return 1;
}

void text_to_morse(const char text[], char output[]) {
    output[0] = '\0';

    for (int i = 0; i < strlen(text); i++) {
        char c = toupper(text[i]);

        if (c == ' ') {
            printf("/ ");
            strcat(output, "/ ");
        }
        else if (c >= 'A' && c <= 'Z') {
            int index = c - 'A';
            printf("%s ", TABLE[index]);
            strcat(output, TABLE[index]);
            strcat(output, " ");
        }
        else if (c >= '0' && c <= '9') {
            int index = (c - '0') + 26;
            printf("%s ", TABLE[index]);
            strcat(output, TABLE[index]);
            strcat(output, " ");
        }
    }

    int len = strlen(output);
    if (len > 0 && output[len - 1] == ' ') {
        output[len - 1] = '\0';
    }

    printf("\n");
}

void morse_to_text(const char morse[], char output[]) {
    if (!is_morse_code_valid(morse)) {
        printf("Error: Invalid Morse Code input.\n");
        output[0] = '\0';
        return;
    }

    char temp[1000];
    strcpy(temp, morse);
    output[0] = '\0';

    char *chunk = strtok(temp, " \n\t\r");
    while (chunk != NULL) {
        if (strcmp(chunk, "/") == 0) {
            printf(" ");
            strcat(output, " ");
        } else {
            // Check the single table
            for (int i = 0; i < 36; i++) {
                if (strcmp(TABLE[i], chunk) == 0) {
                    char found_char;

                    // If index is 0-25, it's a letter. If 26-35, it's a number.
                    if (i < 26)
                        found_char = 'A' + i;
                    else
                        found_char = '0' + (i - 26);

                    printf("%c", found_char);

                    // Append to output
                    int len = strlen(output);
                    output[len] = found_char;
                    output[len + 1] = '\0';
                    break;
                }
            }
        }
        chunk = strtok(NULL, " \n\t\r");
    }
    printf("\n");
}