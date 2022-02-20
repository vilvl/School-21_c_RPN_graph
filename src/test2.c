#include <stdio.h>
#include <string.h>
//#include <libc.h>


// RETURN 0 - OK 
// RETURN 1 - OK
enum operations {
    SUM = 0,
    SUB,
    MUL,
    DIV,
    NEG,  // unary minus
    POW,
    SIN,
    COS,
    TAN,
    CTG,
    LN,
    SQRT,
    BRO,
    BRC
};
enum lex_types {
    NUM,
    VAR, // x
    OPER, // 
    ERR,
};


//; // Записываю один если ок, нолик когда ввод закончен.
// Записать в структуру лексемы 


struct lexem {
    enum lex_types lex_type;
    union{
        double num;
        enum operations operation;
    };
};

int get_lexem(struct lexem* a);                                             //  parcing string
int ret_tg_operations(struct lexem* a, char *temp);                         //  write to list tg operations
int numbers_search(int * i, char * str_input, char * c, struct lexem* a);   //  serching numbers. detect error with two points
void ret_math_operations(struct lexem* a, char c);                          //  write to list math operations
void numbers(struct lexem* a, char * c);                                    //  numbers from array to double
int tg_search(int * i, char * str_input, char * c, struct lexem* a);       //  searching tg operations


// struct node {
//     struct data *data;
//     struct node *next;
// };


//char* input(char *str);

int main() {
    struct lexem a;  
    if ( get_lexem(&a) == -1) 
        printf("Error DETECTED");
    return 0;
}

int get_lexem(struct lexem* a) {
    int ret = 0;
    char c;
    char temp[50];
    char str_input[4096];
    int i = 0;
    if (fgets(str_input, 4096, stdin) == NULL)
        ret = -1;

    while (str_input[i] != '\0') {
        c = str_input[i];

        if (c == '*' || c == '/' || c == '+' || c == 'x' ||
            c == '-' || c == '(' || c == ')' || c == '^') {
            ret_math_operations(a, c);  // void
            printf("%c\n", c); // PRINT
        }
        if ((c <= '9' && c >= '0') || c == '.') {  // NUMBERS  
            if (numbers_search(&i, str_input, &c, a) == -1) {  // INT RETURN
                ret = -1;
                break;
            }
                
        } // &i &c str_input, a
        if ( c == 'c' || c == 't' || c == 's' || c == 'l') { // OPERATIONS
            if( tg_search(&i, str_input, &c, a) == -1)
                ret = -1;
        }
        i = i+1;
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
