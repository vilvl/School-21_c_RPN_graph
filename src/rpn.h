#ifndef SRC_RPN_H_
#define SRC_RPN_H_

#include "main.h"
#include "ds.h"

int process_lexems(struct node* lexems, struct node** RPN, struct stack* tmp);
struct mb_dbl calculate_with_RPN(struct node* RPN, struct stack* tmp, double x);

#endif  // SRC_RPN_H_