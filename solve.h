#pragma once
#include<stdio.h>
#include "file_make.h"
#include<stdbool.h>
#include"stack.h"
#include<string.h>
#include"print.h"
#include"work.h"
#include"stdlib.h"
#include"transit.h"
#include<readline/history.h>
#include<readline/readline.h>

extern stack s;
extern FILE *f1,*f2,*f3;
extern bool flag ;//判断是否出现非‘（’的符号出现在第一个的情况
extern bool flag_ch, flag_num,flag_tr;
extern int id;
extern char str[1005];
extern long double num[1005];

void Bsolve(char *file_name,char *input);

void Hsolve(char *file_name,char *input);

void Dsolve(char *file_name,char *input);

