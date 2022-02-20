#include <stdio.h>
#include <math.h>
#include "main.h"
#include "graph.h"

int convert(double old);
double* create_array(double*ar);
void draw_by_array(struct mb_dbl ar_draw[80]);



int main() {
    draw_by_array(mb_dbl, ar_draw[80]);
return 0;
}

void draw_by_array(struct mb_dbl ar_draw[80]) {
    //double ar[80];
    //create_array(ar);


    int y_goal = 0;
    int x_goal ;

    for (int row = 0; row < 25; ++row) {
        for (int column = 0; column < 80; ++column) {
            if (ar_draw[column].valid == 1) {
                x_goal = convert(ar_draw[column].num);
                if (x_goal == row) {
                printf("*");
            }
            }
            else { 
                printf(".");
            }
        y_goal = y_goal +1;
        }
        
        printf("\n");

    }

}
   

int convert(double old) {
    double old_range = 2;
    double new_range = 25;
    double converted =  (((old - (-1.0) ) * 25.0 / 2.0) + 0);
    //return ceil(converted);
    return converted;
}


double* create_array(double * ar) {
    double step = 3.14 * 2 / 80;
    double x = 0;
    double y;
    int i = 0;
    while(i < 80) {
        y = sin(x);
        x = x + step;
        i++;
        ar[i] = y;
}

 for (int j = 0; j < 80; j++) {
  //  printf("%.1d\n", convert(ar[j]));
 }
   return ar;
}