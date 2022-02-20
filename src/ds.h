#ifndef SRC_DS_H_
#define SRC_DS_H_

#include "main.h"

struct node {
    struct lexem value;
    struct node *next;
};

struct stack {
    size_t size;
    struct node *data;
};

struct stack *stack_init();
void stack_destroy(struct stack **s);
int push(struct stack *s, struct lexem value);
int pop(struct stack *s, struct lexem *value);

struct node* list_add_back(struct node* root, struct lexem value);

#endif  // SRC_DS_H_
