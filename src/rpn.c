#include "rpn.h"
#include "main.h"
#include "ds.h"
#include "math.h"

void RPN_add_back(struct node** RPN, struct node** RPN_last, struct lexem value);
void define_minus(struct node* prev, struct node* lexems);

void process_oper(struct node** RPN, struct node** RPN_last, struct stack* tmp, struct lexem value);
int process_BRC(struct node** RPN, struct node** RPN_last, struct stack* tmp);
int get_operation_priority(enum operations oper);
void apply_operation(struct stack* tmp, enum operations oper);
double apply_unary_operation(enum operations oper, double a);
double apply_binary_operation(enum operations oper, double a, double b);










int process_lexems(struct node* lexems, struct node* RPN, struct stack* tmp) {

    struct node* RPN_last = RPN;
    struct node* prev = NULL;
    struct lexem curr;

    while (lexems) {
        if (lexems->value.lex_type == OPER) {
            if (lexems->value.operation == MINUS) {
                define_minus(prev, lexems);
            }
            if (lexems->value.operation == BRO) {
                push(tmp, lexems->value);
            } else if (lexems->value.operation == BRC) {
                process_BRC(&RPN, &RPN_last, tmp);
            } else if (get_operation_priority(curr.operation) == 3) {
                push(tmp, lexems->value);
            } else {
                process_oper(&RPN, &RPN_last, tmp, lexems->value);
                push(tmp, lexems->value);
            }
        } else {
            RPN_add_back(&RPN, &RPN_last, lexems->value);
        }
        prev = lexems;
        lexems = lexems->next;
    }
    while (tmp->size) {
        pop(tmp, &curr);
        RPN_add_back(&RPN, &RPN_last, curr);
    }
    return 0;
}

void process_oper(struct node** RPN, struct node** RPN_last, struct stack* tmp, struct lexem value) {
    struct lexem curr;
    while (peek(tmp, &curr) && (curr.operation != BRO) &&
            (value.operation = POW &&
                (get_operation_priority(curr.operation)
                > get_operation_priority(value.operation))
            || (value.operation != POW &&
                (get_operation_priority(curr.operation)
                >= get_operation_priority(value.operation))))) {
        pop(tmp, &curr);
        RPN_add_back(RPN, RPN_last, curr);
    }
}

int process_BRC(struct node** RPN, struct node** RPN_last, struct stack* tmp) {
    struct lexem curr;
    while (pop(tmp, &curr) && curr.operation != BRO) {
        RPN_add_back(RPN, RPN_last, curr);
    }
    if (curr.operation != BRO)
        return -1;
    if (peek(tmp, &curr) && get_operation_priority(curr.operation) == 3) {
        pop(tmp, &curr);
        RPN_add_back(RPN, RPN_last, curr);
    }
    return 0;
}

void define_minus(struct node* prev, struct node* lexems) {
    if (!prev || (prev->value.lex_type == OPER
                 && (prev->value.operation == BRO
                    || get_operation_priority(prev->value.operation) < 3)))
        lexems->value.operation = NEG;
    else
        lexems->value.operation = SUB;
}

void RPN_add_back(struct node** RPN, struct node** RPN_last, struct lexem value) {
    *RPN_last = list_add_back(*RPN_last, value);
    if (*RPN)
        *RPN = *RPN_last;
}

int get_operation_priority(enum operations oper) {
    int ret = 0;

    switch (oper) {
        case SUM:
        case SUB:
            ret = 0; break;
        case MUL:
        case DIV:
            ret = 1; break;
        case POW:
            ret = 2; break;
        case SIN:
        case COS:
        case TAN:
        case CTG:
        case NEG:
        case LN:
        case SQRT:
            ret = 3; break;
        case BRO:
        case BRC:
            ret = 4; break;
        case MINUS:
            ret = -1; break;
    }
    return ret;
}

struct mb_dbl calculate_with_RPN(struct node* RPN, struct stack* tmp, double x) {

    struct lexem curr;
    while (RPN) {
        curr = RPN->value;
        if (curr.lex_type == VAR) {
            push( tmp, (struct lexem) {.lex_type = NUM, .num = x} );
        } else if (curr.lex_type == NUM) {
            push( tmp, curr );
        } else {  // RPN->value.lex_type = OPER
            apply_operation(tmp, curr.operation);
        }
        RPN=RPN->next;
    }
    pop(tmp, &curr);
    return (struct mb_dbl) {.valid = 0, .num = curr.num};
}

void apply_operation(struct stack* tmp, enum operations oper) {
    struct lexem curr;
    double a, b;
    if (get_operation_priority(oper) == 3) {
        pop(tmp, &curr);
        a = curr.num;
        curr.num = apply_unary_operation(oper, a);
        push(tmp, curr);
    } else if (get_operation_priority(oper) < 3) {
        pop(tmp, &curr);
        b = curr.num;
        pop(tmp, &curr);
        a = curr.num;
        curr.num = apply_binary_operation(oper, a, b);
        push(tmp, curr);
    }

}

double apply_unary_operation(enum operations oper, double a) {
    switch (oper) {
        case SIN: return sin(a);
        case COS: return cos(a);
        case TAN: return tan(a);
        case CTG: return 1.0/tan(a);
        case LN: return log(a);
        case SQRT: return sqrt(a);
        case NEG: return -a;
        default: return NAN;
    }
}

double apply_binary_operation(enum operations oper, double a, double b) {
    switch (oper) {
        case SUM: return a + b;
        case SUB: return a - b;
        case MUL: return a * b;
        case DIV: return a / b;
        case POW: return pow(a, b);
        default: return NAN;
    }
}