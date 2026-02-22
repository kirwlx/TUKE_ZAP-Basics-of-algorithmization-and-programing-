#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int guess_eval(const int guess, const int my_number);

int main() {
    printf("%i %i %i\n", guess_eval(34, 22), guess_eval(22, 34), guess_eval(45, 45));

    return 0;
}

int guess_eval(const int guess, const int my_number) {
    if (guess == my_number) {
        return 1;
    }else if (guess < my_number) {
        return 2;
    }else if (guess > my_number) {
        return 0;
    }
}