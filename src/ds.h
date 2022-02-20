#ifndef SRC_DS_H_
#define SRC_DS_H_

#include "main.h"
#include <stdlib.h>

struct node {
    struct lexem value;
    struct node *next;
};

struct stack {
    size_t size;
    struct node *data;
};

struct node* list_add_back(struct node* root, struct lexem value);

struct stack *stack_init();
void stack_destroy(struct stack **s);
void list_destroy(struct node *s);
int push(struct stack *s, struct lexem value);
int pop(struct stack *s, struct lexem *value);
int peek(struct stack *s, struct lexem *value);

#endif  // SRC_DS_H_
