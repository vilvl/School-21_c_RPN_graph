
#include <stdio.h>
#include "main.h"
#include "graph.h"

void verify_array(struct mb_dbl ey[]);

void draw_by_array(struct mb_dbl ey[]) {
    verify_array(ey);

    double step = (Y_MAX - Y_0) / (FIELD_Y - 1);

    for (int row = 0; row < FIELD_Y; ++row) {
        double y_curr = Y_0 + step*row;
        for (int column = 0; column < FIELD_X; ++column) {
            if (ey[column].valid && ey[column].num < y_curr + step/2) {
                printf(FUNC_POINT);
                ey[column].valid = 0;
            } else {
                printf(EMPTY_POINT);
            }
        }
        if (row < FIELD_Y - 1)
            printf("\n");
    }
}

void verify_array(struct mb_dbl ey[]) {
    for (int i = 0; i < FIELD_X; ++i)
        if (ey[i].valid && (ey[i].num < Y_0 || ey[i].num > Y_MAX))
            ey[i].valid = 0;
}
