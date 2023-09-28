#pragma once
#include<stdbool.h>
typedef struct data{
    struct data *next;
    char num;
}data;
typedef struct stack{
    data *top;
    int size;
}stack;
void stack_init(stack *p);

void stack_pop(stack *p);

void stack_clear(stack *p);

void stack_print(stack *p);

char stack_top(stack *p);

void stack_push(stack *p,char d);

bool is_empty(stack *p);



