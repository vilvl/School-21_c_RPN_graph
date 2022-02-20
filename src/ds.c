#include <stdlib.h>
#include "ds.h"

/////// LIST OF INTS DECL //////////////////

struct node* list_remove_front(struct node* root);
struct node* list_add_front(struct node* root, struct lexem value);
struct node* list_init(struct lexem value);
void list_destroy(struct node* root);

//////////////// STACK ////////////////////

struct stack* stack_init() {
    struct stack* s = malloc(sizeof(struct stack));
    s->data = NULL;
    s->size = 0;
    return s;
}

void stack_destroy(struct stack **s) {
    list_destroy((*s)->data);
    free(*s);
    *s = NULL;
}

int push(struct stack *s, struct lexem value) {
    if (!s)
        return 0;
    // tmp is either located in heap or NULL
    struct node* tmp = list_add_front(s->data, value);
    if (tmp == NULL)
        return 0;
    s->data = tmp;
    s->size++;
    return 1;
}

int pop(struct stack *s, struct lexem *value) {
    if (s == NULL || s->size == 0 || s->data == NULL)
        return 0;
    *value = s->data->value;
    s->data = list_remove_front(s->data);
    s->size--;
    return 1;
}

int peek(struct stack *s, struct lexem *value) {
    if (s == NULL || s->size == 0 || s->data == NULL)
        return 0;
    *value = s->data->value;
    return 1;
}

struct node* list_remove_front(struct node* root) {
    struct node* new_root = root->next;
    root->next = NULL;
    list_destroy(root);
    return new_root;
}

struct node* list_add_front(struct node* root, struct lexem value) {
    struct node *inj = list_init(value);
    if (inj == NULL) {
        return NULL;
    }
    inj->next = root;
    return inj;
}

struct node* list_add_back(struct node* root, struct lexem value) {
    while (root && root->next)
        root = root->next;
    struct node *inj = list_init(value);
    if (inj == NULL)
        return NULL;
    if (root)
        root->next = inj;
    return inj;
}

struct node* list_init(struct lexem value) {
    struct node* new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
        return NULL;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void list_destroy(struct node* root) {
    if (root) {
        list_destroy(root->next);
        free(root);
    }
}

