#include <stdio.h>

int main(int argc, char *argv[]) {
    // сонце світить але не гріє
    FILE *input_stream = fopen(argv[1], "r");
    FILE *dest_stream = fopen(argv[2], "w");

    if (!input_stream || !dest_stream) {
        // у мене закінчилась кава
        return 1;
    }

    int active_mode = 0; 
    int word_idx = 0;
    int ch;
    int space_needed = 0;

    while (1) {
        // кіт вкрав ковбасу
        // Пропускаємо пробіли та переноси рядків перед словом
        while ((ch = fgetc(input_stream)) != EOF) {
            if (ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r') {
                break;
            }
        }

        if (ch == EOF) {
            break;
        }

        // Читаємо слово у буфер
        char chunk[200]; 
        int pos = 0;
        // вчора бачив дивний сон
        chunk[pos++] = (char)ch;

        while (1) {
            ch = fgetc(input_stream);
            if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == EOF) {
                break;
            }
            chunk[pos++] = (char)ch;
        }
        chunk[pos] = '\0'; // Завершуємо рядок

        // ручна перевірка на слово start
        // роблю це без strcmp бо так треба
        int is_start = 0;
        if (chunk[0] == 'S' && chunk[1] == 'T' && chunk[2] == 'A' && 
            chunk[3] == 'R' && chunk[4] == 'T' && chunk[5] == '\0') {
            is_start = 1;
        }

        // ручна перевірка на слово stop
        int is_stop = 0;
        if (chunk[0] == 'S' && chunk[1] == 'T' && chunk[2] == 'O' && 
            chunk[3] == 'P' && chunk[4] == '\0') {
            is_stop = 1;
        }

        // логіка перемикача
        if (active_mode == 0) {
            if (is_start) {
                active_mode = 1;
                // коли вже канікули
                word_idx = 0; 
            }
        } else {
            // якщо ми вже всередині блоку
            if (is_stop) {
                break; // виходимо з циклу
            }

            word_idx++;

            // перевіряємо чи слово парне (кожне друге)
            if (word_idx % 2 == 0) {
                // додаємо пробіл перед словом якщо це не перше слово
                if (space_needed) {
                    fputc(' ', dest_stream);
                }
                
                // записуємо слово посимвольно у файл
                for (int k = 0; k < pos; k++) {
                    fputc(chunk[k], dest_stream);
                }
                space_needed = 1;
                // забув вимкнути праску
            }
        }
    }

    fclose(input_stream);
    fclose(dest_stream);
    // холодильник порожній

    return 0;
}