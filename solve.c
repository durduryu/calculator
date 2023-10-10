#include "solve.h"
stack s;
FILE *f1,*f2,*f3;
bool flag = 0;//判断是否出现非‘（’的符号出现在第一个的情况
bool flag_ch=0, flag_num=0,flag_tr;
int id=0;
char str[1005];
long double num[1005];
unsigned long long num2[1005];

void begin_(){
    num[1]=0;
    num2[1]=num2[0]=0;
    fclose(f2);
    fclose(f3);
    f3 = fopen("transit.txt", "r");
    f2 = fopen("transit.txt","w");
    id = 0;
    flag_num = 0;
    flag_ch = 0;
    flag = 0;
    while(!is_empty(&s))stack_pop(&s);
}

void Dsolve(char* file_name,char *input){//10进制的计算
    begin_();
    int i = 0;
    while(input[i]==' ')i++;
    if(input[i]=='-'){//特判断第一个出现的符号为‘-’的情况
        flag_ch=1;
        fprintf(f2,"0 ");
        stack_push(&s,'-');
        i++;
    }
    while (i < strlen(input)) {
        if(input[i]=='-'&&i<strlen(input)&&input[i+1]<='9'&&input[i+1]>='0'&&flag_num==0){//在前面没有直接连着数字的情况下，并且在后面连着数字时，‘-’作为负数的标志
            fprintf(f2,"-");
            i++;
        }
        if (input[i] <= '9' && input[i] >= '0') {
            flag = 1;
            flag_ch = 0;
            bool flat = 0;
            if (flag_num == 1) {
                wrong();
                return;
            }
            while (i < strlen(input) && ((input[i] <= '9' && input[i] >= '0') || (input[i] == '.'))) {
                if (input[i] == '.') {
                    if (flat == 1) {
                        wrong();
                        return;
                    } else if (i == strlen(input) - 1 || input[i + 1] > '9' || input[i+1] < '0') {
                        wrong();
                        return;
                    } else {
                        flat = 1;
                    }
                }
                fprintf(f2, "%c", input[i]);
                i++;
            }
            flag_num=1;
            fprintf(f2," ");
        } else if(input[i]!=' '){
            flag_num=0;
            if(!flag&&input[i]!='('){
                wrong();
                return ;
            }
            else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
                if (flag_ch ==1){
                    wrong();
                    return;
                }
                flag_ch=1;
                stack_work(input[i],f2,&s);
            }
           else if(input[i]=='|'||input[i]=='&'||input[i]=='='){
                if(flag_ch==1||i==strlen(input)-1||input[i+1]!=input[i]){
                    wrong();
                    return ;
                }
                flag_ch=1;
                stack_work(input[i],f2,&s);
                i++;
            }
            else if(input[i]=='<'||input[i]=='>'||input[i]=='!'){
                if(flag_ch==1||i==strlen(input)-1||(input[i]=='!'&&input[i+1]!='=')){
                    wrong();
                    return ;
                }
                flag_ch=1;
                if(input[i+1]!='='){
                    stack_work(input[i],f2,&s);
                }
                else {
                    if(input[i]=='!')stack_work(input[i],f2,&s);
                    else input[i]=='<'?stack_work('a',f2,&s):stack_work('b',f2,&s);
                    i++;
                }
            }
            else if(input[i]=='('){
                num2[0]++;
                flag_ch=1;
                stack_work(input[i],f2,&s);
            }
            else if(input[i]==')'){
                if(flag_ch==1||!num2[0]){
                    wrong();
                    return ;
                }
                num2[0]--;
                stack_work(input[i],f2,&s);
            }
            else{
                wrong();
                return;
            }
            i++;
        }
        else i++;
    }



    if (flag_ch) {//如果结尾时非‘）’的符号的话
        wrong();
        return;
    }
    while (!is_empty(&s)) {
        fprintf(f2, "%c ", stack_top(&s));
        stack_pop(&s);
    }
    fprintf(f2, "\nstop");

    //如果运行到可以运行到下面的代码，说明表达式大概率不会出错
    //下面开始对后缀表达式进行计算

    add_history(input);

    fflush(f2);

    while (fscanf(f3, "%s", str)) {
        if (strcmp(str, "stop") == 0) {
            break;
        } else {
            if (strlen(str)>1||(str[0] <= '9' && str[0] >= '0')) {
                num[++id] = atof(str);
            } else {
                switch (str[0]) {
                    case '&':
                        num[id-1]=num[id]&&num[id-1];
                        break;
                    case '|':
                        num[id-1]=num[id]||num[id-1];
                        break;
                    case '<':
                        num[id-1]=num[id-1]<num[id];
                        break;
                    case '>':
                        num[id-1]=num[id-1]>num[id];
                        break;
                    case 'a':
                        num[id-1]=num[id-1]<=num[id];
                        break;
                    case 'b':
                        num[id-1]=num[id-1]>=num[id];
                        break;
                    case '=':
                        num[id-1]=(num[id-1]==num[id]);
                        break;
                    case '!':
                        num[id-1]=num[id-1]!=num[id];
                        break;
                    case '+':
                        num[id - 1] += num[id];
                        break;
                    case '-':
                        num[id - 1] -= num[id];
                        break;
                    case '/':
                        if(num[id]==0){
                            printf("\033[31mERROR:ZERO\n\033[0m");
                            return ;
                        }
                        num[id - 1] /= num[id];
                        break;
                    case '*':
                        num[id - 1] *= num[id];
                        break;
                }
                id--;
            }
        }
    }
    fprintf(f1, "result>:%.8Lf\n", num[1]);
    fflush(f1);
    return ;
}

void Bsolve(char *file_name,char *input){//2进制的计算
    begin_();
    int i = 0;
    while(input[i]==' ')i++;
    while (i < strlen(input)) {
        if (input[i] =='1' || input[i]== '0') {
            flag = 1;//最先出现的是数字
            flag_ch = 0;
            bool flat = 0;
            if (flag_num == 1) {
                wrong();
                return;
            }
            while (i < strlen(input) && (input[i] =='1' || input[i] == '0' )) {
                fprintf(f2, "%c", input[i]);
                i++;
            }
            flag_num=1;
            fprintf(f2," ");
        } else if(input[i]!=' '){
            flag_num=0;
            if(!flag&&input[i]!='('){
                wrong();
                return ;
            }
            else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'||input[i]=='&'||input[i]=='^'||input[i]=='|') {
                if (flag_ch ==1){
                    wrong();
                    return;
                }
                flag_ch=1;
                stack_work(input[i],f2,&s);
            }
            else if(input[i]=='('){
                num2[0]++;
                flag_ch=1;
                stack_work(input[i],f2,&s);
            }
            else if(input[i]==')'){
                if(flag_ch==1||!num2[0]){
                    wrong();
                    return ;
                }
                num2[0]--;
                stack_work(input[i],f2,&s);
            }
            else{
                wrong();
                return;
            }
            i++;
        }
        else i++;
    }

    if (flag_ch) {//如果结尾时非‘）’的符号的话
        wrong();
        return;
    }
    while (!is_empty(&s)) {
        fprintf(f2, "%c ", stack_top(&s));
        stack_pop(&s);
    }
    fprintf(f2, "\nstop");

    //如果运行到可以运行到下面的代码，说明表达式大概率不会出错
    //下面开始对后缀表达式进行计算

    add_history(input);

    fflush(f2);

    while (fscanf(f3, "%s", str)) {
        if (strcmp(str, "stop") == 0) {
            break;
        } else {
            if ((str[0] =='1' || str[0] == '0')) {
                id++;
                i=0;
                num2[id]=0;
                while(i<strlen(str)){
                    num2[id]=(num2[id]<<1)+str[i]-48;
                    i++;
                }

            } else {
                switch (str[0]) {
                    case '|':
                        num2[id-1]|=num2[id];
                        id--;
                        break;
                    case '^':
                        num2[id-1]^=num2[id];
                        id--;
                        break;
                    case '&':
                        num2[id-1]&=num2[id];
                        id--;
                        break;
                    case '+':
                        num2[id - 1] += num2[id];
                        id--;
                        break;
                    case '-':
                        num2[id - 1] -= num2[id];
                        id--;
                        break;
                    case '/':
                        if(num2[id]==0){
                            printf("\033[31mERROR:ZERO\n\033[0m");
                            return ;
                        }
                        num2[id - 1] /= num2[id];
                        id--;
                        break;
                    case '*':
                        num2[id - 1] *= num2[id];
                        id--;
                        break;
                }
            }
        }
    }
    Btransit(str,num2[1]);//将num2[1]转换成2进制的形式
    fprintf(f1, "result>:%s\n", str);
    fflush(f1);
    return ;
}

bool Hdigit(char ch){//判断是不是16进制的数字
    return (ch<='9'&&ch>='0')||(ch>='A'&&ch<='F');
}

void Hsolve(char *file_name,char *input){
    begin_();
    int i = 0;
    while(input[i]==' ')i++;
    while (i < strlen(input)) {
        if (Hdigit(input[i])) {
            flag = 1;//最先出现的是数字
            flag_ch = 0;
            bool flat = 0;
            if (flag_num == 1) {
                wrong();
                return;
            }
            while (i < strlen(input) && Hdigit(input[i])) {
                fprintf(f2, "%c", input[i]);
                i++;
            }
            flag_num=1;
            fprintf(f2," ");
        } else if(input[i]!=' '){
            flag_num=0;
            if(!flag&&input[i]!='('){
                wrong();
                return ;
            }
            else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
                if (flag_ch ==1){
                    wrong();
                    return;
                }
                flag_ch=1;
                stack_work(input[i],f2,&s);
            }
            else if(input[i]=='('){
                num2[0]++;
                flag_ch=1;
                stack_work(input[i],f2,&s);
            }
            else if(input[i]==')'){
                if(flag_ch==1||!num2[0]){
                    wrong();
                    return ;
                }
                num2[0]--;
                stack_work(input[i],f2,&s);
            }
            else{
                wrong();
                return;
            }
            i++;
        }
        else i++;
    }

    if (flag_ch) {//如果结尾时非‘）’的符号的话
        wrong();
        return;
    }
    while (!is_empty(&s)) {
        fprintf(f2, "%c ", stack_top(&s));
        stack_pop(&s);
    }
    fprintf(f2, "\nstop");

    //如果运行到可以运行到下面的代码，说明表达式大概率不会出错
    //下面开始对后缀表达式进行计算

    add_history(input);

    fflush(f2);

    while (fscanf(f3, "%s", str)) {
        if (strcmp(str, "stop") == 0) {
            break;
        } else {
            if (Hdigit(str[0])){ //转化成16进制
                id++;
                i=0;
                num2[id]=0;
                while(i<strlen(str)){
                    if(str[i]<='9'&&str[i]>='0')
                        num2[id]=(num2[id]<<4)+str[i]-48;
                    else
                        num2[id]=(num2[id]<<4)+str[i]-'A'+10;
                    i++;
                }
            } else {
                switch (str[0]) {
                    case '+':
                        num2[id - 1] += num2[id];
                        id--;
                        break;
                    case '-':
                        num2[id - 1] -= num2[id];
                        id--;
                        break;
                    case '/':
                        if(num2[id]==0){
                            printf("\033[31mERROR:ZERO\n\033[0m");
                            return ;
                        }
                        num2[id - 1] /= num2[id];
                        id--;
                        break;
                    case '*':
                        num2[id - 1] *= num2[id];
                        id--;
                        break;
                }
            }
        }
    }
    fprintf(f1, "result>:%llX\n",num2[1]);
    fflush(f1);
    return ;
}
