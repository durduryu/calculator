#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"stack.h"



void stack_init(stack *p) {
    p->size = 0;
    p->top = NULL;
    return;
}

void stack_pop(stack *p) {
    if (p->size == 0)return;
    data *m = p->top;
    p->top = m->next;
    free(m);
    p->size--;
    return;
}

char stack_top(stack *p) {
    return p->top->num;
}

void stack_clear(stack *p) {
    data *q = p->top;
    while (q != NULL) {
        data *m = q;
        q = q->next;
        free(m);
    }
    p->size=0;
    return;
}

void stack_print(stack *p) {
    data *q = p->top;
    while (q != NULL) {
        printf("%c ", q->num);
        q = q->next;
    }
    return;
}

void stack_push(stack *p, char d) {
    data *q = (data *) malloc(sizeof(data));
    q->num = d;
    q->next = p->top;
    p->top = q;
    p->size++;
    return;
}

bool is_empty(stack *p) {
    return p->size == 0 ? 1 : 0;
}



