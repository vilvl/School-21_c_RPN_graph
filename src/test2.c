#include <stdio.h>
#include <string.h>
//#include <libc.h>

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

int get_lexem(struct lexem* a);
void ret_tg_operations(struct lexem* a, char *temp);
void ret_math_operations(struct lexem* a, char c);
void numbers(struct lexem* a, char * c);

// struct node {
//     struct data *data;
//     struct node *next;
// };


//char* input(char *str);

int main() {
    struct lexem a;
   
    get_lexem(&a);
    //printf("", a_struct.lex_type);
    //printf("", lexem.num)
    //printf("", a_struct.operations);
    
    return 0;
}

int get_lexem(struct lexem* a) {  /// 
    int ret = 1;
    char c;
    char temp[50];
    char str_input[4096];
    int i = 0;
    fgets(str_input, 4096, stdin); // NULL
    while (str_input[i] != '\0') {
        c = str_input[i];
       
        // Условия считвания операндов
        if (c == '*' || c == '/' || c == '+' || c == 'x' ||
            c == '-' || c == '(' || c == ')' || c == '^') {
            ret_math_operations(a, c);
            printf("%c\n", c);
        }


        if ((c <= 57 && c >= 48) || c == 46) { // NUMBERS   

            int flag = 0;

            i++;
            int j = 0;
            temp[j] = c;
            j = j+1;
            c = str_input[i];
            if (c == 46 && flag == 1) {
                printf("ERROR");
                ret = 0;
                break;
                };
            
            while (c != '\n' &&  ((c <= 57 && c >= 48) || c == 46)) { // !!!! FGETS END WITH "\N" ????
                if (c == 46) flag = 1;

                temp[j] = c;
                j++; i++; 
                c = str_input[i];

                if (c == 46 && flag == 1){
                ret = 0; // BREAK!!!!
                return 0; // !!! УБРАТЬ ИЛИ В ОТДЕЛЬНУЮ ФУНКЦИЮ
                }
            }
            temp[j] = '\0';
            numbers(a, temp);
        }
        if ( c == 'c' || c == 't' || c == 's' || c == 'l') { // OPERATIONS
            i++;
            int j = 0;
            temp[j] = c;
            j = j+1;
            c = str_input[i];
            while (c != '\0' && (c >= 'a' && c < 'z') && j < 4) {
                temp[j] = c;
                j = j + 1;
                i = i + 1;  
                c = str_input[i];
            }
            temp[j] = '\0'; 
            ret_tg_operations(a, temp);
        }
        i = i+1;
    }
    return ret;
}

void ret_tg_operations(struct lexem* a, char *temp) {
    int flag = 0;
    if      (strcmp("sin", temp) == 0) a->operation = SIN;
    else if (strcmp("cos", temp) == 0) a->operation = COS;
    else if (strcmp("tan", temp) == 0) a->operation = TAN;
    else if (strcmp("ln", temp) == 0) a->operation = LN;
    else if (strcmp("ctg", temp) == 0) a->operation = CTG;
    else if (strcmp("sqrt", temp) == 0) a->operation = SQRT;
    else    flag = 1;
    if (flag == 0) a->lex_type = OPER;
    else a->lex_type = ERR; /////// ВЕРНУТЬ НОЛЬ
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
    a->num = num;
}


//struct node * add_node_back(struct node*, struct lexem);