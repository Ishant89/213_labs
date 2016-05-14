/*
 * Author : Ishant Dawer (idawer@andrew.cmu.edu)
 */

//#define DEBUG
#include<stdio.h>
#include "cachelab.h"

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

/*
 *
 * Timestamp counter
 */

int timestamp=0 ;

int main(int argc,char ** argv) 
{ 
        parseOptions(argc,argv);
/*
 * Creating cache based on the user inputs
 */     
        unsigned int numberOfSets = 1 << setBits;
        Set * Sets = (Set *) calloc(numberOfSets,sizeof(Set  ));


/*
 * Opening the file and reading it line by line 
 */
         
        char OpType;
        unsigned long long Address;
        unsigned int size;
        Long Tag, Set;
        unsigned int numOfHits=0,numOfEvicts=0,numOfMisses=0;
        FILE * fp = fopen(traceFile,"r");
        
        if (fp == NULL) 
        { 
                fprintf(fp,"Unable to open the file\n");
                exit(-1);
        }
        char ch;
        int c;
        while (!feof(fp)) { 
                if ((fgetc(fp)) != 'I') 
                {  
                       
                        c = fscanf(fp," %c %llx,%u%c",&OpType,&Address,&size,&ch);
                        if ( c < 1 )
                               break; 
                        PRINTF("OpType is %c\n",OpType);
                        PRINTF("Address is %llx\n",Address);
                        PRINTF("Tag is %llu\n",tagValue(Address));
                        PRINTF("Set is %llu\n",setValue(Address));
                        
                        Tag = tagValue(Address);
                        Set = setValue(Address);
                        if (isHit(Sets,Tag,Set)) 
                        {
                                printf("%c %llx Hit\n",OpType,Address);
                                PRINTF("Hit\n");
                                numOfHits++;
                        } 
                        else 
                        {
                                numOfMisses++;
                                int a = addToCache(Sets,Tag,Set);
                                if(a) 
                                { 
                                        numOfEvicts++;
                                        printf("%c %llx Miss Evict\n",OpType,Address);
                                        PRINTF("Evict\n");
                                }  else 
                                {
                                    printf("%c %llx Miss\n",OpType,Address);
                                }
                                PRINTF("Miss\n");
                        }
                        if (OpType == 'M') {
                                if (isHit(Sets,Tag,Set)) 
                                {
                                        PRINTF("Hit\n");
                                        printf("%c %llx Hit\n",OpType,Address);
                                        numOfHits++;
                                } 
                                else 
                                {
                                        numOfMisses++;
                                        int a = addToCache(Sets,Tag,Set);
                                        if(a) 
                                        { 
                                                numOfEvicts++;
                                                printf("%c %llx Miss Evict\n",
                                                                OpType,Address);
                                                PRINTF("Evict\n");
                                        } else 
                                        {
                                            printf("%c %llx Miss\n",OpType,Address);
                                        }

                                        PRINTF("Miss\n");
                                }
                        }


                       
                }
                else 
                {
                        c = fscanf(fp," %c %llx,%u%c",&OpType,&Address,&size,&ch);
                }
        }

        //printf("hits:%u misses:%u evictions:%u\n", numOfHits,numOfMisses,numOfEvicts);
/*
 * Free the sets memory
 */
        for (int i = 0 ; i < numberOfSets; i++) 
        { 
                if (Sets[i] != NULL) 
                { 
                        free(Sets[i]);
                }
        }


        free(Sets);
        fclose(fp);

        printSummary(numOfHits,numOfMisses,numOfEvicts);
        exit(0);
}


/*****************************Helper Functions*********************/

/*
 * parseOptions : Parsing the options and populating the 
 * global vars (setBits, blockBits & traceFile)
 */
void parseOptions(int argc, char ** argv) 
{ 
        int opt;
        int sflag=0,Eflag=0,bflag=0,tflag=0;
        while (-1 != (opt = getopt(argc, argv, "s:E:b:t:vh")))
        { 
                switch(opt) 
                { 
                        case 's' : 
                                sflag = 1;
                                setBits = atoi(optarg);
                                break;
                        case 'E' : 
                                Eflag = 1;
                                numLines = atoi(optarg);
                                break;
                        case 'b' : 
                                bflag = 1;
                                blockBits = atoi(optarg);
                                break;
                        case 't' : 
                                tflag = 1;
                                traceFile = optarg;
                                break;
                        case 'v' : 
                                PRINTF("Verbose enabled\n");
                                break;
                        case 'h' : 
                                PRINTF("help enabled\n");
                                break;
                        default : 
                                printf("Wrong argument here\n");
                                break;
                }
        }
}

Long tagValue(Long Address) 
{ 
        int rightOffset = setBits + blockBits;
        return (Long)(Address >> rightOffset );
}

Long setValue(Long Address) 
{ 
        int rightOffset =  blockBits;
        Long value = Address >> rightOffset;
        Long setVal = value & ((1<< setBits) -1);
        return setVal;
}

int isHit(Set * Sets, Long Tag , Long Set) 
{ 
        timestamp++;
        Line * line = NULL;
        PRINTF("Sets are %p\n",Sets[Set]);
        PRINTF("Comp is %d\n",Sets[Set] != NULL);
        if (Sets[Set] != NULL) 
        {
               for (int i = 0 ; i < numLines ; i++) {
                       line = &Sets[Set][i];      
                       if( line->valid && (line->tag == Tag))  
                       {
                               PRINTF("Values are %llu and %llu\n",line->tag,Tag);
                               line->count = timestamp;
                               return 1;
                       } 
               }


        }
        return 0;
}

int addToCache(Set * Sets, Long Tag, Long Set) 
{ 
        Line * line = NULL;
        int numOfEvicts = 0 ;
        if (Sets[Set] == NULL) 
        { 
                Sets[Set] = (Line *) malloc(numLines * sizeof(Line ));
        }
        line = findInvalidLine(&Sets[Set]);
        if (line != NULL) 
        { 
            line -> valid = 1;
            line -> tag = Tag;
        } 
        else 
        {
                line = evictLRLine(&Sets[Set]);
                line->valid = 1;
                line->tag = Tag;
                numOfEvicts++;
        }
        line->count = timestamp;
        return numOfEvicts;
}


Line * findInvalidLine(Line ** line )
{
        Line * lineArr = *line;
        for (int i = 0 ; i < numLines; i++) 
        {
               if (!(lineArr -> valid))
               {
                     return lineArr ;
               }
               lineArr++;
        }
        return NULL;  
}


Line * evictLRLine(Line ** line) 
{ 
        Line * lineArr = *line;
        Line temp;
        for (int i = 0 ; i < (numLines - 1 ) ; i++) 
        { 
            if (lineArr->count < (lineArr + 1 )->count) 
            {
                    temp = *lineArr;
                    *lineArr = *(lineArr + 1);
                    *(lineArr + 1) = temp;

            }
            lineArr++;
        }
        
        return lineArr;
}
