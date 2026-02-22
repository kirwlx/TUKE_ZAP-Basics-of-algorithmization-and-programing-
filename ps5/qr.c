#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void encode_char(const char character, bool bits[8]);
char decode_byte(const bool bits[8]);
void encode_string(const char string[], bool bytes[strlen(string)+1][8]);
void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]);

int main(){


    // // bool bits1[8];
    // // encode_char('A', bits1);
    // // for(int i = 0; i < 8; i++){
    // //     printf("%d", bits1[i]);
    // // }
    // // printf("\n");



    // // bool bits2[8] = {0,1,0,0,0,0,0,1};
    // // printf("%c\n", decode_byte(bits2));

    // char* text = "Hello, how are you?";
    // const int len = strlen(text);
    // bool bytes1[len+1][8];
    // encode_string(text, bytes1);
    // for(int j = 0; j <= len; j++){
    //     printf("%c: ", text[j]);
    //     for(int i = 0; i < 8; i++){
    //         printf("%d", bytes1[j][i]);
    //     }
    //     printf("\n");
    // }
    

    return 0;
}

 void encode_char(const char character, bool bits[8]){

    int number = character;
    int hod = 128;
    for (int i = 0; i < 8; i++){
        if (number >= hod){
            bits[i] = 1;
            number = number - hod;
            hod = hod/2;
            continue;
        }else{
            bits[i] = 0;
            hod = hod/2;
            continue;
        }
    }

 }


 char decode_byte(const bool bits[8]){
    int hod = 128;
    int number = 0;
    for (int i = 0; i < 8; i++){

        if(bits[i] == 1){
            number = number + hod;
            hod = hod/2;
        }else{
            hod = hod/2;
        }

    }
    char letter = number;
    return letter;
 }

void encode_string(const char string[], bool bytes[strlen(string)+1][8]){
    for(int j = 0; j <= strlen(string); j++){
        int number = string[j];
        int hod = 128;
        for (int i = 0; i < 8; i++){
        if (number >= hod){
            bytes[j][i] = 1;
            number = number - hod;
            hod = hod/2;
            continue;
        }else{
            bytes[j][i] = 0;
            hod = hod/2;
            continue;
        }
    }
    }

}


void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]) {
    for (int k = 0; k < offset * 8; k++) {
        for (int m = 0; m < cols; m++) {
            blocks[k][m] = 0;
        }
    }

    for (int k = 0; k < rows; k++) {
        for (int m = 0; m < 8; m++) {
            int c = k % cols;
            int r = (k / cols) * 8 + m;

            if (r < offset * 8 && c < cols) {
                blocks[r][c] = bytes[k][m];
            }
        }
    }
}

void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8]) {
    for (int k = 0; k < rows; k++) {
        for (int m = 0; m < 8; m++) {
            int c = k % cols;
            int r = (k / cols) * 8 + m;

            if (r < offset * 8 && c < cols) {
                bytes[k][m] = blocks[r][c];
            } else {
                bytes[k][m] = 0;
            }
        }
    }
}