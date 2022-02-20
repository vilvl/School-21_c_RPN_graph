#include <stdio.h>



int main() {


    for(int y = 0; y <= 25; y++) { // Отрисовка столбцов
        char c = '#';
        for(int x = 0; x  <= 80; x++) { // Отрисовка строк x
            printf("%c", c); //Отрисовка пустоты поля
        }
        printf("\n");
    }
    return 0;
}