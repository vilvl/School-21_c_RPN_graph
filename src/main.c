
#include <inttypes.h>

#include "input.h"
#include "main.h"


enum lex_types {
    NUM,
    VAR,
    BIN_OPER,
    UNO_OPER,
    ERR,
};

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

struct lexem {
    enum lex_types lex_type;
    union lex{
        double num;
        enum operations operation;
    }
};

int oper_priorities[15];


int main() {

    set_priorities();

    struct stack* RPN = init_stack();
    struct stack* tmp = init_stack();

    struct lexem lex;
    while (get_lexem(&lex)) {
        if (lex.lex_type == ERR)
            close_with_messege(1, "wrong input", RPN, tmp);
        if (!process_lexem(&lex, RPN, tmp))
            close_with_messege(1, "logic error", RPN, tmp);
    }

}

void close_with_messege(int code, char* messege, struct stack* RPN, struct stack* tmp) {
    if (RPN)
        destroy_stack(RPN);
    if (tmp)
        destroy_stack(tmp);
    printf("%s\n", messege);
    exit(code);
}