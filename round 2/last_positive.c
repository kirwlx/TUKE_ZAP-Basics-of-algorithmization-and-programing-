#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int last_positive(const int size, const int array[]);

int main() {
    const int array1[] = {0,1,0,2};
    const int array2[] = {-1,0,-6,-2};
    printf("%d %d\n", last_positive(4, array1), last_positive(4, array2)) ;

    return 0;
}

int last_positive(const int size, const int array[]) {
    if (array == NULL) {
        return -1;
    }
    for (int i = size-1; i>=0; i--) {
        if (array[i]>0) {
            return array[i];
        }
    }
    return -1;
}