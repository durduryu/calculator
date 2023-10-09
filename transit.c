#include"transit.h"

void Btransit(char *str,unsigned long long num){//进行2进制的转换
    bool flag=0;
    int id=0;
    for(int i=63;i>=0;i--){
        int a=(num>>i)&1;
        if(a){
            str[id++]=a+48;
            flag=1;
        }
        else if(flag){
            str[id++]=a+48;
        }
    }
    str[id]='\0';
    return ;
}