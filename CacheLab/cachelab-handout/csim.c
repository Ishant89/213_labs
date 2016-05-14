/*
 * Author : Ishant Dawer (idawer@andrew.cmu.edu)
 */

//#define DEBUG

/*
 * Standard I/O
 */

#include<stdio.h>
#include "cachelab.h"

#include<stdlib.h>
/*
 * Getopt to parse command line args 
 * e.g. : ./csim -s 3 -E 2 -b 4 -t trace/file1
 */

#include<getopt.h>

/*
 * printf wrapper for debugging output
 */

#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) ((void) 0)
#endif


/*
 * Global variables : set bits, block bits
 * and number of Lines
 */

unsigned long long setBits ; //number of bits (-s 4)
unsigned long long blockBits ; //number of block bits (-b 5)
short int numLines ; //number of Lines (-E 2)
char * traceFile; //filename (-t trace/file1)
int helpFlag = 0; //help enabled

/*
 * Parsing command line arguments
 * Input : argc (args count), argv[][] (array of strings)
 * Description : Parse command line args e.g. : 
 * parsing "./csim -s 4 -b 4 -E 1 -t trace/file1" will set following variables 
 * setBits = 4
 * blockBits = 4
 * numberLines = 1
 * filename = "trace/file1"
 */

void parseOptions(int , char ** );

/*
 * Struct for Lines : contains following components
 * int valid :1 - Valid bit in line
 * long long tag - cache tag (can contain 64 bits) in line
 * int count - counter contains value for LRU cache( Lower value of line 
 *             gets replaced first
 */

struct Line 
{ 
        unsigned int valid : 1;
        unsigned long long tag ;
        unsigned int count ;
};

/*
 * alias for struct Lines : struct Line is known as Line
 */


typedef struct Line Line;

/*
 * pointer to group of lines is Set
 * alias for Line * (pointer to Line) is Set
 */

typedef struct Line * Set;

/*
 * alias for unsigned long long int
 * Long - unsigned long long
 */

typedef unsigned long long Long;


/*
 * Extract Tag Value from the address
 * Input : Long Address (address from trace file)
 * Output : Long Tag (Tag value for cache matching)
 */

Long tagValue(Long );

/*
 * Extract set Value from the address
 * Input : Long Address (address from trace file)
 * Output : Set index (Set in  cache)
 */

Long setValue(Long );
/*
 * Max Bits in Address (64)
 */

#define MAXBITS 64

/*
 * isHit : To see if Cache is hit
 * Input : Array of Sets, Tag value, Set value
 * Output: 1 for hit or 0 for miss
 */


int isHit(Set * , Long  , Long );


/*
 * addToCache : Adding to cache in case of Miss
 * Input : Array of Sets, Tag value, Set value
 * Output :  Zero in case of evict & 1 in case of evict
 */

int addToCache(Set * , Long , Long );

/*
 * findInvalidLine : finding line with invalid bit
 * Input : Array of Lines in a set 
 * Output : Pointer to a Line with invalid bit
 */

Line * findInvalidLine(Line ** );

/*
 * evictLRLine : Evicting line which is least recently used
 * There is a global counter which is copied to Line counter everytime
 * it is accessed (Hit/Miss/Evict)
 * Input : Array of lines
 * Output : Line pointer to be evicted
 */

Line * evictLRLine(Line **);



/*
 * Global timestamp counter
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
        if (Sets == NULL) 
        { 
                printf("Unable to alloc memory to Sets\n");
                exit(-1);
        }


/*
 * OpType - Determing if op is L,M or S
 * Address - Memory address in hexadecimal
 * Size - Size of token read
 * Tag - Tag value from address
 * Set - Set value from address
 * numOfHits - counter to track number of hits
 * numOfEvicts - counter to track number of Evicts
 * numOfMisses - counter to track number of Misses
 * E.g : OpType = 'L', Address = 0x20, Size = 4
 *       Tag,Set = (calculated using functions)
 */

         
        char OpType;
        unsigned long long Address;
        unsigned int size;
        Long Tag, Set;
        unsigned int numOfHits=0,numOfEvicts=0,numOfMisses=0;
/*
 * Opening the file and reading it line by line 
 */

        FILE * fp = fopen(traceFile,"r");
        
        if (fp == NULL) 
        { 
                fprintf(fp,"Unable to open the file\n");
                exit(-1);
        }
        char ch; //Garbage value to contain '\n' at the end of line
        int count;//count for fscanf to check if the characters read are > 1
        while (!feof(fp)) { 
                if ((fgetc(fp)) != 'I') 
                {  
                      /*
                       * Parsing line by line
                       */

                        count = fscanf(fp," %c %llx,%u%c",&OpType,&Address,&size
                                        ,&ch);

                        if ( count < 1 )
                               break;

                       /*
                        * Getting Tag value & SetValue from Address
                        */

                        Tag = tagValue(Address);
                        Set = setValue(Address);

                        int anotherIteration  = 0;

                        if (OpType == 'M') 
                        { 
                                anotherIteration = 1;
                        }
                        do { 
                                if (isHit(Sets,Tag,Set)) 
                                {
                                        numOfHits++;
                                } 
                                else 
                                {
                                        numOfMisses++;
                                        int a = addToCache(Sets,Tag,Set);
                                        if(a) 
                                        { 
                                                numOfEvicts++;
                                        } 
                                }
                        } while ((OpType == 'M') && anotherIteration--); 
                }
                else 
                {
                        /*
                         * Skipping the line that starts with 'I'
                         */

                        count = fscanf(fp," %c %llx,%u%c",&OpType,&Address,&size
                                        ,&ch);
                }
        }

/*
 * Free the sets memory
 * Make all the lines free 
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
 * Parsing command line arguments
 * Input : argc (args count), argv[][] (array of strings)
 * Description : Parse command line args e.g. : 
 * parsing "./csim -s 4 -b 4 -E 1 -t trace/file1" will set following variables 
 * setBits = 4
 * blockBits = 4
 * numberLines = 1
 * filename = "trace/file1"
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
                                helpFlag = 1;
                                break;
                        default : 
                                printf("Wrong argument here\n");
                                break;
                }
                if (sflag && Eflag && bflag && tflag) 
                { 
                    printf("Mandatory args (-s, -E, -b or -t)are missing\
                                        \n"); 
                }
        }
}



/*
 * Extract Tag Value from the address
 * Input : Long Address (address from trace file)
 * Output : Long Tag (Tag value for cache matching)
 */

Long tagValue(Long Address) 
{ 
        int rightOffset = setBits + blockBits;
        return (Long)(Address >> rightOffset );
}

/*
 * Extract set Value from the address
 * Input : Long Address (address from trace file)
 * Output : Set index (Set in  cache)
 */

Long setValue(Long Address) 
{ 
        int rightOffset =  blockBits;
        Long value = Address >> rightOffset;
        Long setVal = value & ((1<< setBits) -1);
        return setVal;
}

/*
 * isHit : To see if Cache is hit
 * Input : Array of Sets, Tag value, Set value
 * Output: 1 for hit or 0 for miss
 */

int isHit(Set * Sets, Long Tag , Long Set) 
{ 
        timestamp++;
        Line * line = NULL;
        if (Sets[Set] != NULL) 
        {
               for (int i = 0 ; i < numLines ; i++) {
                       line = &Sets[Set][i];      
                       if( line->valid && (line->tag == Tag))  
                       {
                               line->count = timestamp;
                               return 1;
                       } 
               }


        }
        return 0;
}

/*
 * addToCache : Adding to cache in case of Miss
 * Input : Array of Sets, Tag value, Set value
 * Output :  Zero in case of evict & 1 in case of evict
 */
int addToCache(Set * Sets, Long Tag, Long Set) 
{ 
        Line * line = NULL;
        int numOfEvicts = 0 ;
        if (Sets[Set] == NULL) 
        { 
                Sets[Set] = (Line *) malloc(numLines * sizeof(Line ));
                if (Sets[Set] == NULL) 
                { 
                        printf("Unable to allocate memory for line for Set %llu"
                                        ,Set);
                        exit(-1);
                }
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

/*
 * findInvalidLine : finding line with invalid bit
 * Input : Array of Lines in a set 
 * Output : Pointer to a Line with invalid bit
 */
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

/*
 * evictLRLine : Evicting line which is least recently used
 * There is a global counter which is copied to Line counter everytime
 * it is accessed (Hit/Miss/Evict)
 * Input : Array of lines
 * Output : Line pointer to be evicted
 */

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
