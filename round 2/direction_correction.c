#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int direction_correction(const int degree);
int main() {
    printf("%d %d %d\n", direction_correction(-90), direction_correction(540), direction_correction(180));

    return 0;
}

int direction_correction(const int degree) {
    if ((degree % 90 == 0) && (degree >=0)) {
        if (degree > 360) {
            return degree - 360;
        }else {
            return degree;
        }
    }else {
        return -1;
    }
}