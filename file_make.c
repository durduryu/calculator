#include"file_make.h"
#include<string.h>
#include<stdio.h>
void file_make(char *file_name,FILE** f1) {
    if (strcmp(file_name, "\\terminal") == 0) {
        *f1 = fopen("/dev/tty", "w");
    } else {
        *f1 = fopen(file_name, "w");
    }
    return;
}