#include <stdio.h>
#include <string.h>
#include "ds.h"
#include "input.h"
#include "main.h"

int ret_tg_operations(struct lexem* a, char *temp);                         //  write to list tg operations
int numbers_search(int * i, char * str_input, char * c, struct lexem* a);   //  serching numbers. detect error with two points
void ret_math_operations(struct lexem* a, char c);                          //  write to list math operations
void numbers(struct lexem* a, char * c);                                    //  numbers from array to double
int tg_search(int * i, char * str_input, char * c, struct lexem* a);       //  searching tg operations


// typedef struct node {
//     struct data *data;
//     struct node *next;
// }TEST_LIST;


//char* input(char *str);

int main() {
    struct node *a = NULL;  
    if (get_lexems_from_input(&a) == -1)
        printf("ERROR");

    while (a->next != NULL) {
    
        printf("%u\n", a->value.lex_type);
        //printf("%lf\n", a->value.num);
        //printf("%u\n", a->value.operation);
        a = a->next;
    }
}

// Создать связный список
//Передать себе
//Вывести
int get_lexems_from_input(struct node** head_list) {
    struct node* last_list = *head_list;
    
    // Указатели!!!!!!!!!!
    int ret = 0;
    char c;
    char temp[50];
    char str_input[4096];
    int i = 0;
    if (fgets(str_input, 4096, stdin) == NULL)
        ret = -1;

    while (str_input[i] != '\0') {
        struct lexem a;
        c = str_input[i];

        if (c == '*' || c == '/' || c == '+' || c == 'x' ||
            c == '-' || c == '(' || c == ')' || c == '^') {
            ret_math_operations(&a, c);  // void
            printf("%c\n", c); // PRINT
        }
        if ((c <= '9' && c >= '0') || c == '.') {  // NUMBERS  
            if (numbers_search(&i, str_input, &c, &a) == -1) {  // INT RETURN
                ret = -1;
                break;
            }
                
        } // &i &c str_input, a
        if ( c == 'c' || c == 't' || c == 's' || c == 'l') { // OPERATIONS
            if( tg_search(&i, str_input, &c, &a) == -1)
                ret = -1;
        }
        i = i+1;
        if (!*head_list) {
            *head_list = list_add_back(NULL, a);
            last_list = *head_list;
        } else { 
            last_list = list_add_back(last_list, a);
        }
    }
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
    else {
        flag = 1;
    }    

    if (flag == 0) a->lex_type = OPER;
    else {
    a->lex_type = ERR; /////// ВЕРНУТЬ -1
    printf("%s", temp);
    ret = -1;
    } 
    return ret;
}

void ret_math_operations(struct lexem* a, char c) {
    if (c == 'x') a->lex_type = VAR;
    else {
        if (c == '/') a->operation =  DIV;
        else if (c == '*') a->operation = MUL;
        else if (c == '+') a->operation = SUM;
        else if (c == '-') a->operation = SUB;
        else if (c == '(') a->operation = BRO;
        else if (c == ')') a->operation = BRC;
        else if (c == '^') a->operation = POW;
        a->lex_type = OPER;
    }
}

void numbers(struct lexem* a, char * c) {
    double n;
    sscanf(c, "%lf", &n);
    //printf("!!!");
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
    printf("%s\n", temp);
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
    while (*c != '\0' &&  ((*c <= '9' && *c >= '0') || *c == '.')) { // !!!! FGETS END WITH "\N" ????
        if (*c == 46) flag = 1;
        temp[j] = *c;
        j++; (*i)++; 
        *c = str_input[(*i)];
            if (*c == 46 && flag == 1) {
                ret = -1; // BREAK!!!!
                break;
            }
    }
    temp[j] = '\0';
    printf("%s\n", temp);
    numbers(a, temp);
    *i = (*i) - 1;
    return ret;
}

//struct node * add_node_back(struct node*, struct lexem);
