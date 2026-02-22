#include "hangman.h"
#include <time.h>
#include <stdlib.h>
#include "morse.h"



int main() {
    //char alphaba[] = "abcdefghijklmnopqrstuvwxyz";

    // char available_letters[50] = "abcdefghijklmnopqrstuvwxyz"; Розмір 50 із запасом
    srand(time(NULL));
    char word[]="";

     get_word(word);
     hangman(word);
    char output[500];
    text_to_morse("text", output);
    morse_to_text("-.- .. .-. -.-- .-..", output);

    is_morse_code_valid("-.- .. .-. -.-- .-..");





    return 0;
}