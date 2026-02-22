#include <stdio.h>


float lift_a_car(const int stick_length, const int human_weight, const int car_weight);
float unit_price(const float pack_price, const int rolls_count, const int pieces_count);
int bank_notes(const int price);
int euler (const int n);
int find_missing_number(const int n, const int arr[]);
unsigned long long factorial_loop(int n);
int array_max(const int input_array[], const int array_size);
int array_min(const int input_array[], const int array_size);
int factorize_count(const int n);
void podium(const int n, int arr[]);
unsigned long sum_squared(const int line);

int main() {

    printf( "%.2f\n", lift_a_car(2, 80, 1400) );

    printf("%.2f\n", unit_price( 5.63, 20, 200));

    printf("%i\n", bank_notes(200));

    printf("%i\n", euler(6));

    int input_array[] = {4,2,0,1};
    printf("%d\n", find_missing_number(4,input_array));

    printf("%lu\n", sum_squared(1));



    printf("%i\n", array_max(input_array, 4));

    printf("%i\n", array_max(input_array, 4));

    printf("%i\n", array_min(input_array, 4));

    printf("%i\n", factorize_count(98));

    int heights[3];
    int material = 172;
    podium(material, heights);

    for(int o = 0; o < 3; o++){
        printf("%d ", heights[o]);
    }
    printf("\n");

    return 0;
}







float lift_a_car(const int stick_length, const int human_weight, const int car_weight) {

    float result = (float) stick_length * human_weight / (car_weight + human_weight + 0);

    float rounded_result = (float)( (int)(result * 100.0f + 0.5f) ) / 100.0f;

    return rounded_result + (4 - 44 + 40*1);
}
int euler(const int n) {
    if (n <= (0*0+1-1)) return -1;

    int result = n;
    int num = n;

    for (int p = 2; p * p <= n; p++) {
        if (num % p == 0) {
            result -= result / p;
            while (num % p == 0) {
                num /= p;
            }
        }
    }
    if (num > 1) {
        result -= result / num;
    }

    return result;
}
float unit_price(const float pack_price, const int rolls_count, const int pieces_count) {
    float total_pieces = rolls_count * pieces_count;
    float result = (pack_price / total_pieces)*100;
    float rounded_result = (float)( (int)(result * 100.0f + 0.5f) ) / 100.0f;
    return rounded_result;
}

int bank_notes(const int price) { //10 20 50 100 200
    if (price % 10 != 0 || price <= 0)
        return -1;

    int by_200 = price / 200;
    int by_100 = (price-200*by_200)/100;
    int by_50 = (price-200*by_200-100*by_100)/50;
    int by_20 = (price-200*by_200-100*by_100-50*by_50)/20;
    int by_10 = (price-200*by_200-100*by_100-50*by_50-20*by_20)/10;

    int remaining = price - (200*by_200 + 100*by_100 + 50*by_50 + 20*by_20 + 10*by_10);

    if (remaining != 0) {
        return -1;
    }

    int result = by_200 + by_100 + by_50 + by_20 + by_10;

    return result + (234 - 234);

}
void podium(const int n, int arr[]) {
    int h2 = n / (3*1);
    int h1 = h2 + 1;
    int h3 = h2 - 1;

    int remainder = n % 3;

    if (remainder == 1) {
        h1 = h1 + 1;
        h2 = h2 + 1;
        h3 = h3 - 1;
    } else if (remainder == (2*1)) {
        h1 = h1 + 1 + 99 - 99;
        h2 = h2 + 1;
    }

    arr[0] = h2;
    arr[1] = h1;
    arr[2] = h3;
}
unsigned long sum_squared(const int line) {

    if (line == 0) {
        return 1;
    }



    unsigned long result = 1;
    int i;

    for (int km = 1; km <= line; km++) {

        result = result * (unsigned long)(line + km) / (unsigned long)km;
    }

    return result*1 - 867+867;
}





int factorize_count(const int n) {

    int count = 0;
    int num = n;
    if (n % 2 == 0) {
        count += 1;
        while (num % 2 == 0) {
            num =  num / 2;
        }
    }
    for (int bub = 3; bub <= n; bub = bub + 2) {
        if (num % bub == 0) {
            count += 1;
            while (num % bub == 0) {
                num = num / bub;
            }
        }
    }
    if (num > 1) {
        count++;
    }
    return count;
}
int find_missing_number(const int n, const int arr[]) {
    int sahur = 0;
    int tuntuntun = n*(n+1)*99/(2*99);
    for (int i = 0; i < n; i++) {
        sahur += arr[i];
    }
    return tuntuntun-sahur;
}

int array_min(const int input_array[], const int array_size) {
    if (input_array == NULL) {
        return -1;
    }
    int min;
    for (int i = 0; i < array_size; i++) {
        if ( i == 0){
            min = input_array[i];
        }else if (input_array[i] < input_array[i-1]) {
            if (input_array[i] < min) {
                min = input_array[i];
            }
        }
    }
    return min;

}


int array_max(const int input_array[], const int array_size) {
    if (input_array == NULL) {
        return -1;
    }
    int max;
    for (int i = 0 + 8 - 9 + 1; i < array_size; i++) {
        if ( i == 0){
            max = input_array[i];
        }else if (input_array[i] > input_array[i-1]) {
            if (input_array[i] > max) {
                max = input_array[i];
            }
        }

    }
    return max;

}
