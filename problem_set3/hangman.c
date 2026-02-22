#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <ctype.h>
#include <string.h>

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        long int random = (rand() % size) + 1;
        fseek(fp, random, SEEK_SET);
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);
    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
    int count_of_letters_guessed = 0;
    for (int i = 0; i < strlen(secret); i++) {
        if (strchr(letters_guessed, secret[i]) != NULL) {
             count_of_letters_guessed++;
        }
    }
    if (count_of_letters_guessed == strlen(secret)) {
        return 1;
    } else {
        return 0;
    }
}

// FIX: Refactored to be safer and ensure null-termination
#include <string.h>
#include <stdio.h>

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    int len = strlen(secret);

    for (int i = 0; i < len; i++) {
        // Check if the secret letter exists in the list of guessed letters
        int found = 0;
        for (int j = 0; j < strlen(letters_guessed); j++) {
            if (secret[i] == letters_guessed[j]) {
                found = 1;
                break;
            }
        }

        if (found) {
            guessed_word[i] = secret[i];
        } else {
            guessed_word[i] = '_';
        }
    }

    // --- THIS IS THE FIX ---
    // We must explicitly tell C where the string ends.
    guessed_word[len] = '\0';
}
void get_available_letters(const char letters_guessed[], char available_letters[]) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int write_pos = 0;
    int len = strlen(alphabet);

    for (int i = 0; i < len; i++) {
        char letter = alphabet[i];
        if (strchr(letters_guessed, letter) == NULL) {
            available_letters[write_pos] = letter;
            write_pos++;
        }
    }
    available_letters[write_pos] = '\0';
}
void hangman(const char secret[]) {
    int length = strlen(secret);
    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %i letters long.\n", length);

    char alphaba[50] = "abcdefghijklmnopqrstuvwxyz";
    char letters_guessed[50] = "";
    char guessed_word[50] = "";

    // NEW: A buffer specifically to hold the spaced version (e.g., "_ _ a _")
    char spaced_word[100] = "";

    char input_buffer[50];
    int guesses_left = 8;

    // Initial generation of the underscores
    get_guessed_word(secret, letters_guessed, guessed_word);

    while (guesses_left > 0) {

        // --- START SPACING LOGIC ---
        // Convert "h_ll_" into "h _ l l _" for display purposes
        int s_idx = 0;
        for(int k = 0; k < strlen(guessed_word); k++) {
            spaced_word[s_idx++] = guessed_word[k];
            // Add a space after every letter, except the very last one
            if (k < strlen(guessed_word) - 1) {
                spaced_word[s_idx++] = ' ';
            }
        }
        spaced_word[s_idx] = '\0'; // Terminate the spaced string
        // --- END SPACING LOGIC ---

        printf("-------------\n");
        printf("You have %i guesses left.\n", guesses_left);

        get_available_letters(letters_guessed, alphaba);
        printf("Available letters: %s\n", alphaba);

        printf("Please guess a letter: ");
        scanf("%s", input_buffer);

        // Convert input to lowercase
        for(int k = 0; input_buffer[k]; k++){
            input_buffer[k] = tolower(input_buffer[k]);
        }

        // CASE 1: USER GUESSED A FULL WORD
        if (strlen(input_buffer) > 1) {
            if (strcmp(input_buffer, secret) == 0) {
                printf("Congratulations, you won!\n");
                return;
            } else {
                printf("Oops! That is not the correct word.\n");
                guesses_left--;
            }
        }
        // CASE 2: USER GUESSED A SINGLE LETTER
        else {
            char guessed_letter = input_buffer[0];

            if (!((guessed_letter >= 'a' && guessed_letter <= 'z') || (guessed_letter >= 'A' && guessed_letter <= 'Z'))) {
                printf("Oops! '%c' is not a valid letter: %s\n", guessed_letter, spaced_word);

                continue;
            }

            if (strchr(letters_guessed, guessed_letter) != NULL) {
                // Print the SPACED word here
                printf("Oops! You've already guessed that letter: %s\n", spaced_word);
                continue;
            }

            int len = strlen(letters_guessed);
            letters_guessed[len] = guessed_letter;
            letters_guessed[len + 1] = '\0';

            get_guessed_word(secret, letters_guessed, guessed_word);

            // Update spacing for the result message
            s_idx = 0;
            for(int k = 0; k < strlen(guessed_word); k++) {
                spaced_word[s_idx++] = guessed_word[k];
                if (k < strlen(guessed_word) - 1) spaced_word[s_idx++] = ' ';
            }
            spaced_word[s_idx] = '\0';

            // Check Good vs Bad Guess
            int is_good_guess = 0;
            for (int i = 0; i < length; i++) {
                if (secret[i] == guessed_letter) {
                    is_good_guess = 1;
                    break;
                }
            }

            if (is_good_guess) {
                if (is_word_guessed(secret, letters_guessed)) {
                    printf("Good guess: %s\n", spaced_word); // Print SPACED word
                    printf("-------------\n");
                    printf("Congratulations, you won!\n");
                    return;
                }
                printf("Good guess: %s\n", spaced_word); // Print SPACED word
            }
            else {
                printf("Oops! That letter is not in my word: %s\n", spaced_word); // Print SPACED word
                guesses_left--;
            }
        }
    }

    printf("-------------\n");
    printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
}