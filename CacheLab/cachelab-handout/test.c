#include"csim.h"
#include<stdio.h>

int main() { 
        Line  x ;
        x.valid = 1;
        x.tag = 0 ;
        x.count = 10;
        Line y ; 
        y.valid = 1;
        y.tag = 0;
        y.count = 20;
        y = x;
        printf("Struct y is %d\n",y.count);
}

