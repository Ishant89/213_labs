#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>

#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) ((void) 0)
#endif


/*
 * Global variables : set bits, block bits
 * and number of Lines
 */

unsigned long long setBits ;
unsigned long long blockBits ;
short int numLines ;
char * traceFile;


/*
 * Parsing command line arguments
 */

void parseOptions(int , char ** );

/*
 * Struct for Lines
 */

struct Line 
{ 
        unsigned int valid : 1;
        unsigned long long tag ;
        unsigned int count ;
};

/*
 * alias for struct Lines
 */


typedef struct Line Line;

/*
 * pointer to group of lines is Set
 */

typedef struct Line * Set;

/*
 *
 * alias for unsigned long long int
 */

typedef unsigned long long Long;


/*
 * Extract Tag Value from the address
 */

Long tagValue(Long );

/*
 * Extract set Value from the address
 */

Long setValue(Long );
/*
 * Max Bits
 */

/*
 * isHit : to see if Cache is hit
 */


int isHit(Set * , Long  , Long );


/*
 * addToCache : 
 */

int addToCache(Set * , Long , Long );

/*
 * findInvalidLine
 */

Line * findInvalidLine(Line ** );

/*
 * evictLRLine()
 */

Line * evictLRLine(Line **);


#define MAXBITS 64
