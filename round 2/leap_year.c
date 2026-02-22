#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int leap_year(const int year);

int main() {
    printf("%d %d %d\n", leap_year(4000), leap_year(3000), leap_year (3004));
    return 0;
}

int leap_year(const int year) {
    if ((year % 100 == 0) && ((year/100) % 4 != 0)) {
        return 0;
    }else if (year % 4 == 0) {
        return 1;
    }else if ((year % 100 == 0) && ((year/100) % 4 == 0) ) {
        return 1;
    }
    return 0;
}