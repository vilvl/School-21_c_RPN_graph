#ifndef SRC_RPN_H_
#define SRC_RPN_H_

#include "main.h"

int process_lexems(struct node* lexems, struct stack* RPN, struct stack* tmp);
struct mb_dbl calculate_with_RPN(struct stack* RPN, double x);

#endif  // SRC_RPN_H_