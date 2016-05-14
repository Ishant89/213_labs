#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#define DEBUG

#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(STRING) ((void) 0)
#endif


void parseOptions(int argc, char ** argv) 
{ 
        int opt, s;
        while (-1 != (opt = getopt(argc, argv, "s:v")))
        { 
                switch(opt) 
                { 
                        case 's' : 
                                s = atoi(optarg);
                                PRINTF("S is %d",s);
                                break;
                        default : 
                                printf("Wrong argument here");
                                break;
                }
        }
}



