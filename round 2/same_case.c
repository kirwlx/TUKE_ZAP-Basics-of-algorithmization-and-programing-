#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int same_case(const char a, const char b);

int main() {
    printf("%d %d %d\n", same_case('a','f'), same_case('L','g'), same_case('#', 'P'));
    return 0;
}

int same_case(const char a, const char b) {
    if (isalpha(a) == 0 || isalpha(b) == 0) {
        return -1;
    }

    if (isupper(a) == isupper(b)) {
        return 1;
    }else {
        return 0;
    }
}