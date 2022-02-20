#include <inttypes.h>
#include <stdio.h>

#include "main.h"
#include "ds.h"

#include "input.h"
#include "rpn.h"

void close_with_messege(int code, char* messege, struct node* lexems, struct node* RPN, struct stack* tmp);
void fill_array(struct mb_dbl ey[], struct node* RPN);

int main() {

    struct node* lexems = NULL;
    struct node* RPN = NULL;
    struct stack* tmp = init_stack();

    // struct lexem lex;

    if (0 == get_lexems_from_input(&lexems))
        close_with_messege(1, "wrong input", lexems, RPN, tmp);
    if (0 == process_lexems(lexems, RPN, tmp))
        close_with_messege(1, "logic error", lexems, RPN, tmp);

    struct mb_dbl ey[FIELD_X];
    fill_array(ey, RPN);

    draw_by_array(ey);

    close_with_messege(0, "", lexems, RPN, tmp);
}

void fill_array(struct mb_dbl ey[], struct node* RPN) {
    double step = (X_MAX - X_0) / (FIELD_X - 1);
    for (int i = 0; i < FIELD_X; ++i) {
        ey[i] = calculate_with_RPN(RPN, X_0 + step * i);
    }
}

void close_with_messege(int code, char* messege, struct node* lexems, struct node* RPN, struct stack* tmp) {
    if (lexems)
        destroy_list(lexems);
    if (RPN)
        destroy_list(RPN);
    if (tmp)
        destroy_stack(tmp);
    if (*messege != '\0')
        printf("%s\n", messege);
    // exit(code);
}