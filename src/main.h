#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#define FIELD_X 80
#define FIELD_Y 25

#define X_0 0.0
// 4 * M_PI
#define X_MAX 12.56637061435917295385057353311801152

#define Y_0 -1.0
#define Y_MAX 1.0

#define EMPTY_POINT "."
#define FUNC_POINT "*"

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

void output_lexem(struct lexem value);

#endif  // SRC_MAIN_H_
