#include"work.h"
#include<stdio.h>

void stack_work(char ch,FILE* f2,stack *s) {
    if (ch == '(')stack_push(s, ch);
    else if (ch == ')') {
        while (stack_top(s) != '(') {
            fprintf(f2, "%c ", stack_top(s));
            stack_pop(s);
        }
        stack_pop(s);//弹出‘(’
    } else if (ch == '-' || ch == '+') {
        while (!is_empty(s) && (stack_top(s)=='*'||stack_top(s)=='/'||stack_top(s)=='-'||stack_top(s)=='+')) {
            fprintf(f2, "%c ", stack_top(s));
            stack_pop(s);
        }
        stack_push(s,ch);
    }
    else if (ch=='a'||ch=='b'||ch=='<'||ch=='>'){
        while(!is_empty(s)&&stack_top(s)!='('&&stack_top(s)!='|'&&stack_top(s)!='&'&&stack_top(s)!='!'&&stack_top(s)!='='){
            fprintf(f2,"%c ",stack_top(s));
            stack_pop(s);
        }
        stack_push(s,ch);
    }
    else if(ch=='='||ch=='!'){
        while(!is_empty(s)&&stack_top(s)!='('&&stack_top(s)!='|'&&stack_top(s)!='^'&&stack_top(s)!='&'){
            fprintf(f2,"%c ",stack_top(s));
            stack_pop(s);
        }
        stack_push(s,ch);
    }
    else if(ch=='|'){
        while(!is_empty(s)&&(stack_top(s)!='(')){
            fprintf(f2,"%c ",stack_top(s));
            stack_pop(s);
        }
        stack_push(s,ch);
    }
    else if(ch=='^'){
        while(!is_empty(s)&&stack_top(s)!='('&&stack_top(s)!='|'){
            fprintf(f2,"%c ",stack_top(s));
            stack_pop(s);
        }
        stack_push(s,ch);
    }
    else if(ch=='&'){
        while(!is_empty(s)&&stack_top(s)!='('&&stack_top(s)!='|'&&stack_top(s)!='^'){
            fprintf(f2,"%c ",stack_top(s));
            stack_pop(s);
        }
        stack_push(s,ch);
    }
    else if (ch == '/' || ch == '*') {
        while (!is_empty(s) && (stack_top(s) == '*' || stack_top(s) == '/')) {//只有当前面是*或者是\时才会弹出
            fprintf(f2, "%c ", stack_top(s));
            stack_pop(s);
        }
        stack_push(s,ch);
    }
    return;
}