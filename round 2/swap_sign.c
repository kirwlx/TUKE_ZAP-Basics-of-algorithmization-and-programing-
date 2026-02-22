#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void swap_sign(const int size, int array[]);

int main() {
    int array[] = {1,2,0, -3,4,0};
        swap_sign(6, array);
    for (int i = 0; i < 6; i++) {
    printf("%d ", array[i]);
}
printf ("\n");
    return 0;
}

void swap_sign(const int size, int array[]) {
    for (int i = 0; i < size; i++) {
        int symb = array[i] - 2*array[i];
        array[i] = symb;
    }
}
