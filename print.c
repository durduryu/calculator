#include "print.h"
#include<stdio.h>

void help() {
    printf("\033[32m\\clear:清除这次输入的表达式\n");
    printf("\\exit:退出程序(注意的是输入的只能是\"\\exit\"，不能有空格和其他字符)\n");
    printf("\\help:查询帮助(注意的是输入的只能是\"\\help\",不能有空格和其他字符)\n");
    printf("本计算器默认为10进制\n");
    printf("B:切换成2进制(注意的是输入的只能是\"B\",不能有空格和其他字符)\n");
    printf("D:切换10进制(注意的是输入只能是\"D\",不能有空格和其他字符)\n");
    printf("H:切换成16进制(注意的时输入的只能时\"H\",不能有空格和其他字符\n");
    printf("直接输入正确的四则表达式，可以计算表达式的结果\n");
    printf("每条命令以回车作为响应\n");
    printf("您可以通过上下箭头来查询历史命令(之前输入过的正确表达式)\n");
    printf("如果想要输出后缀表达式，请在运行程序时加上-d的命令行参数");
    printf("如果您需要将输出的表达式结果输出到特定的文件中，可以使用\"-t file_name\"的命令格式(注意的是这个文件名是不会忽略空格的)\n");
    printf("如果你想要恢复输出在终端的话，请将file_name改成\"\\terminal\"");
    printf("祝你使用愉快\n\033[0m");
    return;
}

void wrong(){
    printf("\033[31mWRONG COMMMEND\n\033[0m");
    return;
}