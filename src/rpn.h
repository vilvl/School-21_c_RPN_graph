#ifndef SRC_RPN_H_
#define SRC_RPN_H_

#include "main.h"

struct mb_dbl process_lexems(struct list* lexems, struct stack* RPN, struct stack* tmp);
void calculate_with_RPN(struct stack* RPN, double x);

#endif  // SRC_RPN_H_