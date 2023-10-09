#pragma once
#include "allhead.h"

#define maxn 1005
char str[maxn];
char file_name[maxn]="\\terminal";
char *input;
bool flag_B=0,flag_H=0;

//#define D
//删除"//"的话实现输出时会输出后缀表达式

#ifdef D
flag_tr=1;
#endif

int main(int argc,char *argv[]) {
    int op=0;
    while((op=getopt(argc,argv,"d"))!=-1){
        if(op=='d'){
            flag_tr=1;
        }
    }

    using_history();
    rl_initialize();

    f1 = fopen("/dev/tty", "w");

    while (1) {
        input = readline("interaction>");
        if (strcmp(input, "\\exit") == 0) {
            printf("\033[34mgoodbye\n");
            return 0;
        } else if (strstr(input, "\\clear")) {
            printf("\033[F\033[K");
        } else if (strcmp(input, "\\help") == 0) {
            help();
        } else if (strstr(input, "-t")) {
            for (int i = 0; i < strlen(input); i++) {
                if (input[i] == ' ')continue;
                else if (input[i] == '-') {
                    if (input[i + 1] == 't' && input[i + 2] == ' ' && input[i + 3] != '\0') {
                        strncpy(file_name, input + i + 3, strlen(input) - i - 3);
                        file_name[strlen(input) - i - 2] = '\0';
                        file_make(file_name,&f1);
                        break;
                    } else {
                        wrong();
                        break;
                    }
                } else {
                    wrong();
                    break;
                }
            }
        }
        else if (strcmp(input,"H")==0){
            flag_H=1;
            flag_B=0;
        }
        else if (strcmp(input,"B")==0){
            flag_B=1;
            flag_H=0;
        }
        else if (strcmp(input,"D")==0) {
            flag_B = 0;
            flag_H = 0;
        }
        else if(flag_H==1){
            Hsolve(file_name,input);
        }
        else if(flag_B==1){
            Bsolve(file_name,input);
        }
        else {
            Dsolve(file_name,input);
        }
        free(input);
    }
    return 0;
}


