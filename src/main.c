#include <stdio.h>

#include "main.h"

#include "graph.h"
#include "ds.h"
#include "input.h"
#include "rpn.h"

void close_with_messege(int code, char* messege, struct node* lexems, struct node* RPN, struct stack* tmp);
void fill_array(struct mb_dbl ey[], struct node* RPN, struct stack* tmp);

int main() {
    struct node* lexems = NULL;
    struct node* RPN = NULL;
    struct stack* tmp = stack_init();

    // struct lexem lex;

    if (-1 == get_lexems_from_input(&lexems))
        close_with_messege(1, "wrong input", lexems, RPN, tmp);
    // printf("infix: \n");
    // output_list(lexems);
    if (-1 == process_lexems(lexems, &RPN, tmp))
        close_with_messege(1, "logic error", lexems, RPN, tmp);

    // printf("RPN: \n");
    // output_list(RPN);

    // printf("stack_size %zu\n", tmp->size);
    struct mb_dbl ey[FIELD_X];
    fill_array(ey, RPN, tmp);
    // for (int i = 0; i < FIELD_X; i++) {
    //     printf("%.2lf ", ey[i].num);
    // }

    draw_by_array(ey);

    close_with_messege(0, "", lexems, RPN, tmp);
}

void output_lexem(struct lexem value) {
    if (value.lex_type == VAR)
        printf("x\n");
    else if (value.lex_type == NUM)
        printf("%lf\n", value.num);
    else if (value.lex_type == OPER)
        printf("oper %u\n", value.operation);
}

void fill_array(struct mb_dbl ey[], struct node* RPN, struct stack* tmp) {
    double step = (X_MAX - X_0) / (FIELD_X - 1);
    for (int i = 0; i < FIELD_X; ++i) {
        ey[i] = calculate_with_RPN(RPN, tmp, X_0 + step * i);
    }
}

void close_with_messege(int code, char* messege, struct node* lexems, struct node* RPN, struct stack* tmp) {
    if (lexems)
        list_destroy(lexems);
    if (RPN)
        list_destroy(RPN);
    if (tmp)
        stack_destroy(&tmp);
    if (*messege != '\0')
        printf("%s\n", messege);
    exit(code);
}
