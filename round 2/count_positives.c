#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int count_positives(const int size, const int array[]);

int main() {
    const int array1[] = {1,2,0,3,4,0};
    const int array2[] = {1,2,6,3,4,7};
    const int array3[] = {-1,-2,0, -3,0, - 2};
    printf("%d %d %d\n", count_positives(6, array1), count_positives(6, array2), count_positives(6, array3));

    return 0;
}

int count_positives(const int size, const int array[]) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] > 0) {
            count++;
        }else {
            continue;
        }
    }
    return count;
}