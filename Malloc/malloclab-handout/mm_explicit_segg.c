/*
 * mm.c
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mm.h"
#include "memlib.h"

/* If you want debugging output, use the following macro.  When you hand
 * in, remove the #define DEBUG line. */
//#define DEBUG line

#ifdef DEBUG
# define dbg_printf(...) printf(__VA_ARGS__)
#else
# define dbg_printf(...)
#endif


/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(p) (((size_t)(p) + (ALIGNMENT-1)) & ~0x7)


/* 
 *  * Simple, 32-bit and 64-bit clean allocator based on implicit free
 *   * lists, first fit placement, and boundary tag coalescing, as described
 *    * in the CS:APP2e text. Blocks must be aligned to doubleword (8 byte) 
 *     * boundaries. Minimum block size is 16 bytes. 
 *      */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mm.h"
#include "memlib.h"

/*
 *  * If NEXT_FIT defined use next fit search, else use first fit search 
 *   */
#define NEXT_FITx

/* $begin mallocmacros */
/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */ //line:vm:mm:beginconst
#define DSIZE       8       /* Doubleword size (bytes) */
#define CHUNKSIZE   (1<<8)/* Extend heap by this amount (bytes) */  //line:vm:mm:endconst 
#define NEXT 1  /*Refers to the next element */
#define PREV 0  /*Refers to the previous element */
#define CURR 2  /*Refers to the current element */
#define BUCKET 12/*Refers to the bucket size always a multiple of 2*/


#define BUCKET1 200
#define BUCKET2 400
#define BUCKET3 800
#define BUCKET4 1000
#define BUCKET5 2500
#define BUCKET6 5000
#define BUCKET7 12000
#define BUCKET8 24000
#define BUCKET9 30000
#define BUCKET10 40000
#define BUCKET11 60000

#define BINDEX1 0
#define BINDEX2 1
#define BINDEX3 2
#define BINDEX4 3
#define BINDEX5 4
#define BINDEX6 5
#define BINDEX7 6
#define BINDEX8 7
#define BINDEX9 8
#define BINDEX10 9
#define BINDEX11 10
#define BINDEX12 11


#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc)) //line:vm:mm:pack

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))            //line:vm:mm:get
#define PUT(p, val)  (*(unsigned int *)(p) = (val))    //line:vm:mm:put

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)                   //line:vm:mm:getsize
#define GET_ALLOC(p) (GET(p) & 0x1)                    //line:vm:mm:getalloc
#define GET_PREV_ALLOC(p) ((GET(p) & 0x2)                    //line:vm:mm:getalloc

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)                      //line:vm:mm:hdrp
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) //line:vm:mm:ftrp

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) //line:vm:mm:nextblkp
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE))) //line:vm:mm:prevblkp
/* $end mallocmacros */

/* Given block ptr bp, computer successor address */

#define SUCCESSOR(bp)  ((char ** ) (bp))
#define PREDESSOR(bp)  ((char ** ) (bp) + 1)

#define NEXTFREE(bp)  ((!(*(unsigned int *)(bp)))? 0 :((char*)(heap_listp) + *(unsigned int *)(bp)))
#define PREVFREE(bp)  ((!(*((unsigned int *)(bp) + 1))) ? 0 :((char*)(heap_listp) + *((unsigned int *)(bp)+1)))


#define GETPTR(bp) ((!(*(unsigned int *)(bp)))? 0 :((char*)(heap_listp) + *(unsigned int *)(bp)))
#define PUTPTR(bp,val) (((val) == 0) ? (*(unsigned int *)(bp) = 0):(*(unsigned int *)(bp) = ((char*)(val)- (char*)(heap_listp))))
#define WRITESUCCESSOR(bp,val) (((val) == 0) ? (*(unsigned int *)(bp) = 0):(*(unsigned int *)(bp) = ((char*)(val)- (char*)(heap_listp))))
#define WRITEPREDESSOR(bp,val) (((val) == 0) ? ((*((unsigned int *)(bp) + 1)) = 0):(*((unsigned int *)(bp) + 1) = ((char*)(val) - (char*)(heap_listp))))

#define BUCKET_ELEM(i) ((unsigned int *)(bucket_ptr) + i)


/* $end mallocmacros */

/* Global variables */
static char *heap_listp = 0;  /* Pointe to first block */  
static char * start = 0; /* Pointer to root of free list */
static char * bucket_ptr = 0;/* Start of the bucket array*/
static int bucket_number = 0;/*By default bucket selected will be zero*/


/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
//static void printblock(void *bp); 
static void checkblock(void *bp);
static void movFreeBlock_top(void * bp);
static void joinTwoBlocks(void * bp,int next);
static void findList(size_t size);
static void updateList();

/* movFreeBlock_top
 */
static void movFreeBlock_top(void * bp) 
{
        dbg_printf("entering movFree\n");
        dbg_printf("prev Start of list is %p\n",start);
        if (bp != start) 
        {

            char * temp = start;
            start = (char *) bp;
            WRITESUCCESSOR(bp,temp);
            WRITEPREDESSOR(bp,0);
            if (temp!=0) { 
                     WRITEPREDESSOR(NEXTFREE(bp),bp);
            }
        }
        dbg_printf("Start of list is %p and next should be prev Start : %p\n",start,*(char**)(start));
        dbg_printf("exiting movFree\n");
}
/* 
 *  * mm_init - Initialize the memory manager 
 *   */
/* $begin mminit */


int mm_init(void) 
{
            /* reinitializing global pointers */
            start = 0;
            /* Create the initial empty heap */
            /* Calculate the size of heap to be created */

            unsigned int number_buckets = ((BUCKET % 2)?( BUCKET + 1) : BUCKET); 
            size_t size = 4*WSIZE + number_buckets * WSIZE;

            if ((heap_listp = mem_sbrk(size)) == (void *)-1) //line:vm:mm:begininit
                        return -1;
                                     //line:vm:mm:endinit  
                bucket_ptr = (char * ) heap_listp ;
                dbg_printf("Bucket pointer is %p and number of buckets are %d and actual buckets are %d\n",bucket_ptr,number_buckets,BUCKET);
                /*Allocating space to array of buckets */
                unsigned int i ;
                for (i = 0 ; i < number_buckets; i++ ) 
                {
                        PUTPTR(BUCKET_ELEM(i),0);
                        dbg_printf("Value at element %d is %p and ptr is %p\n",i,GETPTR(BUCKET_ELEM(i)),BUCKET_ELEM(i));
                }
                heap_listp = (char * ) bucket_ptr + number_buckets*WSIZE;
                PUT(heap_listp, 0);                          /* Alignment padding */
                PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue header */ 
                PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Prologue footer */ 
                
                PUT(heap_listp + (3*WSIZE), PACK(0, 1));     /* Epilogue header */
                heap_listp += (2*WSIZE);/* $end mminit */
                                    /* $begin mminit */

                                        /* Extend the empty heap with a free 
                                         * block of CHUNKSIZE bytes */


                char * bp = NULL;
                if ((bp=extend_heap(CHUNKSIZE/WSIZE)) == NULL) 
                            return -1;
      //          movFreeBlock_top(bp);
      //          mm_checkheap(176);
                    return 0;
}

/*
 * findList : find the starting point of the list
 */

static void findList(size_t size) 
{
        dbg_printf("Entering findList with size %ld\n",size);
   //     unsigned int index = (size /16) -1;
        unsigned int index = BINDEX12;
   /*     if (index >= BUCKET) 
        {
                index = BUCKET -1;
        }*/

        if(size <= BUCKET1) 
        {
                index = BINDEX1;
        } else if (size >= BUCKET1 && size <= BUCKET2) 
        {
                index = BINDEX2;
        } else if (size >= BUCKET2 && size <= BUCKET3)
        {
                index = BINDEX3;
        } else if (size >= BUCKET3 && size <= BUCKET4) 
        {
                index = BINDEX4;
        } else if (size >= BUCKET4 && size <= BUCKET5)
        {
                index = BINDEX5;
        } else if (size >= BUCKET5 && size <= BUCKET6)
        {
                index = BINDEX6;
        } else if (size >= BUCKET6 && size <= BUCKET7)
        {
                index = BINDEX7;
        } else if (size >= BUCKET7 && size <= BUCKET8)
        {
                index = BINDEX8;
        } else if (size >= BUCKET8 && size <= BUCKET9) 
        {
                index = BINDEX9;
        } else if (size >= BUCKET9 && size <= BUCKET10)
        {
                index = BINDEX10;
        } else if (size >= BUCKET10 && size <= BUCKET11)
        {
                index = BINDEX11;
        } else 
        {
                index = BINDEX12;
        }


        start = GETPTR(BUCKET_ELEM(index));
        dbg_printf("Start is pointing to elem %p and list is %d\n",start,index);
        bucket_number = index;
        dbg_printf("setting the bucket pointer to %d\n",bucket_number);
}

static void updateList() 
{
        dbg_printf("Entering update list\n");
        dbg_printf("prev bucket is %d and bucket previously points to %p\n",bucket_number,GETPTR(BUCKET_ELEM(bucket_number)));
        PUTPTR(BUCKET_ELEM(bucket_number),start);

        dbg_printf("Exiting update list and bucket value set to %p\n",GETPTR(BUCKET_ELEM(bucket_number)));
}


/* $end mminit */

/* 
 *  * mm_malloc - Allocate a block with at least size bytes of payload 
 *   */
/* $begin mmmalloc */
void *malloc(size_t size) 
{
            size_t asize;      /* Adjusted block size */
            size_t extendsize; /* Amount to extend heap if no fit */
            char *bp;      

            dbg_printf("Malloc starting \n");
            dbg_printf("Size is %ld\n",size);
                    /* $end mmmalloc */
            if (heap_listp == 0){
                        mm_init();
            }
                        /* $begin mmmalloc */
                            /* Ignore spurious requests */
            if (size == 0)
                    return NULL;

                                /* Adjust block size to include overhead and 
                                 * alignment reqs. */
                    if (size <= DSIZE)                                          //line:vm:mm:sizeadjust1
                            asize = 2*DSIZE;                                        //line:vm:mm:sizeadjust2
                    else 
                    {

                            asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE); //line:vm:mm:sizeadjust3
                    }
            dbg_printf("Block - words %ld and actual block size %ld\n",asize/WSIZE,asize);
                    findList(asize);
                    dbg_printf("list set to  %p\n",start);
                    /* Search the free list for a fit */

                    if ((bp = find_fit(asize)) != NULL) {  //line:vm:mm:findfitcall
                            place(bp, asize);                  //line:vm:mm:findfitplace
                            dbg_printf("Malloc ending \n");
                            return bp;
                    }

                                            /* No fit found. Get more memory and 
                                             * place the block */
                    extendsize = MAX(asize,CHUNKSIZE);                 //line:vm:mm:growheap1
                    //extendsize = asize;                 //line:vm:mm:growheap1
                    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)  
                            return NULL;                                  //line:vm:mm:growheap2
                    //findList(extendsize);
                    place(bp, asize);                                 //line:vm:mm:growheap3
         //           mm_checkheap(229);
                            dbg_printf("Malloc ending \n");
                      //      mm_checkheap(asize);
                    return bp;
} 
/* $end mmmalloc */

/* 
 *  * mm_free - Free a block 
 *   */
/* $begin mmfree */
void free(void *bp)
{
        dbg_printf("free starting : %p\n",bp);
        /* $end mmfree */
            if(bp == 0) 
                        return;

            /* $begin mmfree */
                size_t size = GET_SIZE(HDRP(bp));
                /* $end mmfree */
                    if (heap_listp == 0){
                                mm_init();
                                    }
                    /* $begin mmfree */

                        PUT(HDRP(bp), PACK(size, 0));
                        PUT(FTRP(bp), PACK(size, 0));
                        WRITESUCCESSOR(bp,0);
                        WRITEPREDESSOR(bp,0);
        dbg_printf("free bp-successor %p & bp-pred %p\n",NEXTFREE(bp),PREVFREE(bp));
                        coalesce(bp);
        dbg_printf("free bp-successor %p & bp-pred %p\n",NEXTFREE(bp),PREVFREE(bp));

        dbg_printf("free ending : %p\n",bp);
        //mm_checkheap(100);
}


/* 
 * joinTwoBlocks(void * bp) : join two blocks in case next/free or both blocks
 * parameters : bp, int next : block pointer, 1 for next and 0 for prev
 */

static void joinTwoBlocks(void * bp,int next) 
{
   dbg_printf("Entering join method with bp as %p and next as %d\n",bp,next); 
    char * Blk = NULL;
    switch (next) 
    {
            case NEXT:
                    Blk = NEXT_BLKP(bp);
                    break;
            case PREV :
                    Blk = PREV_BLKP(bp);
                    break;
            case CURR :
                    Blk = bp;
    }
    char * nextBlk = NEXTFREE(Blk);
    char * prevBlk = PREVFREE(Blk);

   dbg_printf("Next Blk starts at %p and prev blk starts at %p\n",nextBlk,prevBlk); 
    
    if (nextBlk == NULL && prevBlk == NULL ) 
    {
        dbg_printf("The only block in the free list\n");
        start = 0 ;
    }

    
    if (nextBlk == NULL && prevBlk != NULL ) 
    {
        dbg_printf("the last block in the free list\n");
        dbg_printf("About to write in prevBlk's succ (%p) as 0 \n", prevBlk);
        WRITESUCCESSOR(prevBlk,0);
    }

    if (nextBlk != NULL && prevBlk == NULL ) 
    {
        dbg_printf("the first block in the free list\n");
        dbg_printf("About to write in nextBlk's pred (%p) as 0 \n", nextBlk);
        WRITEPREDESSOR(nextBlk,0);
        dbg_printf("nextblk(%p)  pred is %p \n", nextBlk,PREVFREE(nextBlk));
        dbg_printf("nextblk(%p)  succ  is %p \n", nextBlk,NEXTFREE(nextBlk));
        start = nextBlk;
    }     
    if (nextBlk != NULL && prevBlk != NULL ) 
    {
        dbg_printf("somewhere in the middle in the free list\n");
        dbg_printf(" Blk : %p About to write in nextBlk's pred (%p) as %p and prevBlk's succ (%p) as %p \n",Blk, nextBlk,prevBlk,prevBlk,nextBlk);
        WRITESUCCESSOR(prevBlk,nextBlk);
        WRITEPREDESSOR(nextBlk,prevBlk);
    } 
   dbg_printf("Exiting join method with bp as %p and next as %d\n",bp,next); 
}



/* $end mmfree */
/*
 *  * coalesce - Boundary tag coalescing. Return ptr to coalesced block
 *   */
/* $begin mmfree */
static void *coalesce(void *bp) 
{
        dbg_printf("entering coalesce %p\n",bp);
            size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
            size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
            size_t size = GET_SIZE(HDRP(bp));

            
            if (prev_alloc && next_alloc) {            /* Case 1 */
                    findList(size);
                    movFreeBlock_top(bp);
                    updateList();
        dbg_printf("exiting coalesce\n");
                    return bp;
            }

            else if (prev_alloc && !next_alloc) {      /* Case 2 */
                    findList(GET_SIZE(HDRP(NEXT_BLKP(bp))));
                    joinTwoBlocks(bp,NEXT);
                    updateList();

                    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
                    PUT(HDRP(bp), PACK(size, 0));
                    PUT(FTRP(bp), PACK(size,0));
                    dbg_printf("Size becomes %ld and located at %p\n",size,bp);
            }

            else if (!prev_alloc && next_alloc) {      /* Case 3 */
 
                    findList(GET_SIZE(HDRP(PREV_BLKP(bp))));
                    joinTwoBlocks(bp,PREV);
                    updateList();

                    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
                    PUT(FTRP(bp), PACK(size, 0));
                    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
                    bp = PREV_BLKP(bp);
                    dbg_printf("Size becomes %ld and located at %p\n",size,bp);
            }

            else {                                     /* Case 4 */

                    findList(GET_SIZE(HDRP(NEXT_BLKP(bp))));
                    joinTwoBlocks(bp,NEXT);
                    updateList();

                    findList(GET_SIZE(HDRP(PREV_BLKP(bp))));
                    joinTwoBlocks(bp,PREV);
                    updateList();

                    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
                    GET_SIZE(FTRP(NEXT_BLKP(bp)));
                    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
                    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
                    bp = PREV_BLKP(bp);
                    dbg_printf("Size becomes %ld and located at %p\n",size,bp);
            }
                                    /* $end mmfree */
                                        findList(size);
                                        movFreeBlock_top(bp);
                                        updateList();

                                        /* $begin mmfree */

        dbg_printf("exiting coalesce\n");
                                            return bp;
}
/* $end mmfree */

/*
 *  * mm_realloc - Naive implementation of realloc
 *   */
void *realloc(void *ptr, size_t size)
{
            size_t oldsize;
            void *newptr;

                    /* If size == 0 then this is just free, and we return NULL. 
                     * */
            if(size == 0) {
                                mm_free(ptr);
                                    return 0;
                                        }

                        /* If oldptr is NULL, then this is just malloc. */
                        if(ptr == NULL) {
                                    return malloc(size);
                                        }

                            newptr = malloc(size);

                                /* If realloc() fails the original block is left 
                                 * untouched  */
                                if(!newptr) {
                                            return 0;
                                                }

                                    /* Copy the old data. */
                                    oldsize = GET_SIZE(HDRP(ptr));
                                        if(size < oldsize) oldsize = size;
                                            memcpy(newptr, ptr, oldsize);

                                                /* Free the old block. */
                                             mm_free(ptr);

                                                    return newptr;
}

 


/* 
 *  * The remaining routines are internal helper routines 
 *   */

/* 
 *  * extend_heap - Extend heap with free block and return its block pointer
 *   */
/* $begin mmextendheap */
static void *extend_heap(size_t words) 
{
        dbg_printf("Entering extend_heap\n");
            char *bp;
                size_t size;

                    /* Allocate an even number of words to maintain alignment */
                    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE; //line:vm:mm:beginextend
                        if ((long)(bp = mem_sbrk(size)) == -1)  
                                    return NULL;                                        //line:vm:mm:endextend

                            /* Initialize free block header/footer and the 
                             * epilogue header */
                            PUT(HDRP(bp), PACK(size, 0));         /* Free block header */   //line:vm:mm:freeblockhdr
                            PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */   //line:vm:mm:freeblockftr
                            PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */ //line:vm:mm:newepihdr
                            WRITESUCCESSOR(bp,0);
                            WRITEPREDESSOR(bp,0);
                            dbg_printf("New block created--block(bp, size) : %p,%ld\n",bp,size);

                                        /* Coalesce if the previous block was 
                                         * free */
        dbg_printf("Exiting extend_heap after coalesce\n");
                                        return coalesce(bp);                                          //line:vm:mm:returnblock
}
/* $end mmextendheap */

/* 
 *  * place - Place block of asize bytes at start of free block bp 
 *   *         and split if remainder would be at least minimum block size
 *    */
/* $begin mmplace */
/* $begin mmplace-proto */
static void place(void *bp, size_t asize)
             /* $end mmplace-proto */
{
        dbg_printf("Entering place \n");
            size_t csize = GET_SIZE(HDRP(bp));   
            findList(csize);
            joinTwoBlocks(bp,CURR);
            updateList();
      /*      if ((NEXTFREE(bp) == NULL) && (PREVFREE(bp) == NULL)) 
            {
                    start = 0;
            } */
            if ((csize - asize) >= (2*DSIZE)) { 
                    
                    PUT(HDRP(bp), PACK(asize, 1));
                    PUT(FTRP(bp), PACK(asize, 1));
                    bp = NEXT_BLKP(bp);
                    PUT(HDRP(bp), PACK(csize-asize, 0));
                    PUT(FTRP(bp), PACK(csize-asize, 0));
                    findList(csize-asize);
                    movFreeBlock_top(bp);
                    updateList();
                  dbg_printf("Block is split and other half is at %p with size %ld\n",bp,csize-asize); 

            }
            else { 
                    PUT(HDRP(bp), PACK(csize, 1));
                    PUT(FTRP(bp), PACK(csize, 1));
                  dbg_printf("Block is not split\n"); 

            }

        dbg_printf("start is %p\n", start);
        dbg_printf("Exiting place \n");
}
/* $end mmplace */

/* 
 *  * find_fit - Find a fit for a block with asize bytes 
 *   */
/* $begin mmfirstfit */
/* $begin mmfirstfit-proto */
static void *find_fit(size_t asize)
        /* $end mmfirstfit-proto */
{
        /* $end mmfirstfit */
        dbg_printf("Entering find_fit \n");
        /* $begin mmfirstfit */
            /* First fit search */
            void *bp;
            //mm_checkheap(420);
            char * start1;
            int i = bucket_number ;
           for ( start1 = GETPTR(BUCKET_ELEM(bucket_number)); i < BUCKET; start1=GETPTR(BUCKET_ELEM(i)))
           {
                   dbg_printf("Checking in the list with head %pi and bucket is %d\n",start1,i);
             for (bp = start1; bp != NULL ; bp = (void *) NEXTFREE(bp)) 
             {
                            dbg_printf(" checking at %p for asize is  %ld and free node is %d\n",bp,asize,GET_SIZE(HDRP(bp)));
                            dbg_printf(" next in the list is %p and prev in the list is %p\n",*(char**)(bp),*((char**)(bp) + 1));
                            if (asize <= GET_SIZE(HDRP(bp))) {
                                dbg_printf("Block found at %p with size %d\n",bp,GET_SIZE(HDRP(bp)));
                                dbg_printf("Exiting find_fit \n");
                                            return bp;
                            }
             
             }
             i++;
           }
       dbg_printf("Block not found & heap will be extended\n");
        dbg_printf("Exiting find_fit \n");
                                    return NULL; /* No fit */
                                    /* $end mmfirstfit */
}

/*static void printblock(void *bp) 
{
            size_t hsize, halloc, fsize, falloc;

                mm_checkheap(0);
                    hsize = GET_SIZE(HDRP(bp));
                        halloc = GET_ALLOC(HDRP(bp));  
                            fsize = GET_SIZE(FTRP(bp));
                                falloc = GET_ALLOC(FTRP(bp));  

                                    if (hsize == 0) {
                                                printf("%p: EOL\n", bp);
                                                    return;
                                                        }

                                          printf("%p: header: [%p:%c] footer: 
                                         *  [%p:%c]\n", bp, 
                                         *      hsize, (halloc ? 'a' : 'f'), 
                                         *          fsize, (falloc ? 'a' : 
                                         *          'f')); 
}*/

static void checkblock(void *bp) 
{
            if ((size_t)bp % 8)
                        printf("Error: %p is not doubleword aligned\n", bp);
                if (GET(HDRP(bp)) != GET(FTRP(bp)))
                            printf("Error: header does not match footer %d and %d\n",GET(HDRP(bp)),GET(FTRP(bp)));
}

/* 
 *  * checkheap - Minimal check of the heap for consistency 
 *   */
void mm_checkheap(int verbose) 
{
        if (0) { 
            char *bp = heap_listp;
            int i = 0 ;
            char * temp = start;
                if (verbose)
                            printf("Heap (%p):\n", heap_listp);

                    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp)))
                                printf("Bad prologue header\n");
                        checkblock(heap_listp);

                            for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
                                        if (verbose) 
                                                        //printblock(bp);
                                            checkblock(bp);
                                                }

                                if (verbose)
                                            //printblock(bp);
                                    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
                                                printf("Bad epilogue header\n");
          if(verbose == 229 )    
          {                  
            while(temp != NULL ) 
            {
                       // printf("Address is %p\n",temp);
                            temp= NEXTFREE(temp);
                            i++;
            }
            printf("Number of free nodes are %d\n",i);


            
          }


        }

        if ( verbose == 100) 
        {
                printf("Free opertion \n");

                printf("List\tNode\n");
                unsigned int * temp;
                int i = 0; 
                char * bp; 
                for (;i < BUCKET;i++) 
                {
                        printf("%d\t",16*(i+1));  
                      temp = BUCKET_ELEM(i);  
                      for (bp=GETPTR(temp);bp!=NULL;bp = (char*)NEXTFREE(bp)) 
                      {
                              printf("%p\t",bp);
                      }
                      printf("\n");
                }
        }

       printf("Malloc opertion %d\n",verbose);

                printf("List\tNode\n");
                unsigned int * temp;
                int i = 0; 
                char * bp; 
                for (;i < BUCKET;i++) 
                {
                        printf("%d\t",16*(i+1));  
                      temp = BUCKET_ELEM(i);  
                      for (bp=GETPTR(temp);bp!=NULL;bp = (char*)NEXTFREE(bp)) 
                      {
                              printf("%p\t",bp);
                      }
                      printf("\n");
                }


}



