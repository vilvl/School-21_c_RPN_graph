#include <stdio.h>
#include <string.h>
#include "ds.h"
#include "input.h"
#include "main.h"

int ret_tg_operations(struct lexem* a, char *temp);
int numbers_search(int * i, char * str_input, char * c, struct lexem* a);
void ret_math_operations(struct lexem* a, char c);
void numbers(struct lexem* a, char * c);
int tg_search(int * i, char * str_input, char * c, struct lexem* a);

int get_lexems_from_input(struct node** head_list) {
    struct node* last_list = *head_list;
    int ret = 0;
    char c;
    char str_input[1024];
    int i = 0;
    if (fgets(str_input, 1024, stdin) == NULL)
        ret = -1;

    while (str_input[i] != '\0' && str_input[i] != '\n' && ret != -1) {
        struct lexem a;
        c = str_input[i];
        if (str_input[i] == ' ') {
            i++;
            continue;
        } else if (c == '*' || c == '/' || c == '+' || c == 'x' ||
            c == '-' || c == '(' || c == ')' || c == '^') {
            ret_math_operations(&a, c);
        } else if ((c <= '9' && c >= '0') || c == '.') {
            if (numbers_search(&i, str_input, &c, &a) == -1) {
                ret = -1;
                break;
            }
        } else if (c == 'c' || c == 't' || c == 's' || c == 'l') {
            if (tg_search(&i, str_input, &c, &a) == -1) {
                ret = -1;
                break;
            }
        } else {
            ret = -1;
            break;
        }
        i += 1;
        last_list = list_add_back(last_list, a);
        if (!*head_list)
            *head_list = last_list;
    }
    // printf("%c\n", str_input[i]);
    return ret;
}

int ret_tg_operations(struct lexem* a, char *temp) {
    int ret = 0;
    int flag = 0;
    if      (strcmp("sin", temp) == 0) a->operation = SIN;
    else if (strcmp("cos", temp) == 0) a->operation = COS;
    else if (strcmp("tan", temp) == 0) a->operation = TAN;
    else if (strcmp("ln", temp) == 0) a->operation = LN;
    else if (strcmp("ctg", temp) == 0) a->operation = CTG;
    else if (strcmp("sqrt", temp) == 0) a->operation = SQRT;
    else
        flag = 1;

    if (flag == 0) {
        a->lex_type = OPER;
    } else {
        a->lex_type = ERR;
        ret = -1;
    }
    return ret;
}

void ret_math_operations(struct lexem* a, char c) {
    if (c == 'x') {
        a->lex_type = VAR;
    } else {
        if (c == '/') a->operation =  DIV;
        else if (c == '*') a->operation = MUL;
        else if (c == '+') a->operation = SUM;
        else if (c == '-') a->operation = MINUS;
        else if (c == '(') a->operation = BRO;
        else if (c == ')') a->operation = BRC;
        else if (c == '^') a->operation = POW;
        a->lex_type = OPER;
    }
}

void numbers(struct lexem* a, char * c) {
    double n;
    sscanf(c, "%lf", &n);
    // printf("!!!");
    a->lex_type = NUM;
    a->num = n;
}

int tg_search(int * i, char * str_input, char * c, struct lexem* a) {
    int ret = 0;
    char temp[50];
    (*i)++;
    int j = 0;
    temp[j] = *c;
    j = j+1;
    *c = str_input[(*i)];
    while (*c != '\0' && (*c >= 'a' && *c < 'z') && j < 4) {
        temp[j] = *c;
        j++; (*i)++;
        *c = str_input[(*i)];
    }
    temp[j] = '\0';
    if (ret_tg_operations(a, temp) == -1)
        ret = -1;
    // printf("%s\n", temp);
    *i = *i - 1;
    return ret;
}

int numbers_search(int * i, char * str_input, char * c, struct lexem* a) {
    int flag = 0;
    int ret = 0;
    (*i)++;
    int j = 0;
    char temp[50];
    temp[j] = *c;
    j = j+1;
    *c = str_input[(*i)];
    while (*c != '\0' &&  ((*c <= '9' && *c >= '0') || *c == '.')) {
        if (*c == 46) flag = 1;
        temp[j] = *c;
        j++; (*i)++;
        *c = str_input[(*i)];
            if (*c == 46 && flag == 1) {
                ret = -1;
                break;
            }
    }
    temp[j] = '\0';
    // printf("%s\n", temp);
    numbers(a, temp);
    *i = (*i) - 1;
    return ret;
}
