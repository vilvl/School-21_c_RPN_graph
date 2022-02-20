#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#define FIELD_X 80
#define FIELD_Y 25

#define X_0 0.0
// 2 * M_PI
#define X_MAX 6.28318530717958647692528676655900576

#define Y_0 -1.0
#define Y_max 1.0

#define EMPTY_POINT '.'
#define FUNC_POINT '*'


enum lex_types {
    NUM,
    VAR,
    OPER,
    ERR,
};

enum operations {
    SUM = 0,
    SUB,  // binary minus
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
    BRC,
    MINUS  // undefined minus
};

struct lexem {
    enum lex_types lex_type;
    union {
        double num;
        enum operations operation;
    };
};

struct mb_dbl {
    int valid;
    double num;
};

#endif  // SRC_MAIN_H_