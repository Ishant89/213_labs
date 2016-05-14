/*
 * Author : Ishant Dawer (idawer.andrew.cmu.edu)
 */


//#define DEBUG
#include "csim.h"


/*
 *
 * Timestamp counter
 */

int timestamp=0 ;

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


