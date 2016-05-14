/*
 * mm.c
 *
 *  Author : Ishant Dawer (idawer@andrew.cmu.edu)
 *
 *  Malloc : Allocates a memory chunk on the heap as requested by user.
 *  It takes in as size from the user and finds the chunksize in seggregated
 *  lists till it matches the first chunk. Seggregated lists has chunks are 
 *  which are of different sizes such as first list contains chunks of size 
 *  200, second 400 and etc and total number of buckets are 12. Minimum chunk
 *  size that can be allocated is 16 bytes 
 *
 * Parameter : size (size of block requested)
 * Output : pointer to the the block
 *
 *  Free : Frees up the block on heap and it accepts a location to the chunk
 *      Free block contains Header & Footer with next free block pointer and
 *      previous free block pointer (both calculated as offset from the heap
 *      pointer)
 *  paramter : pointer to the block
 *  output  : None
 *
 *  Realloc : Allocates chunk to memory and expands the existing block. If ptr 
 *  is null, it is similar to malloc(size). If ptr is not null, it either 
 *  expands the existing block or returns a new block which meets the size 
 *  requirement
 *
 *  Parameter : ptr (pointer to the exiting block), size(requested size)
 *  Output : ptr (pointer to the next block)
 *
 *  Calloc :  allocates block of array with n elements of size m each with zero
 *
 *  Parameter : memb (number of elements), size (size of each element)
 * 
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

/* Header files for I/O, string manipulation */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Header file for for memory functions such as mem_sbrk etc*/
#include "mm.h"
#include "memlib.h"

/* $begin mallocmacros */
/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */ 
#define DSIZE       8       /* Doubleword size (bytes) */
#define CHUNKSIZE   256 /* Extend heap by this amount (bytes) */
#define NEXT 1  /*Refers to the next element */
#define PREV 0  /*Refers to the previous element */
#define CURR 2  /*Refers to the current element */
#define BUCKET 12/*Refers to the bucket size always a multiple of 2*/

/*
 * Bucket size range for 12 Buckets 
 * such as Bucket1 has a range from 0 -200
 * Bucket2 (range 201 - 400) etc
 */


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
#define BUCKET11 50000
#define BUCKET12 60000

/* 
 * Bucket Indexs to identify the seggregated list 
 * Index are set by findList funtion and used in bucket_ptr
 * which identifies the seggregated list
 */


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

/* MAX macro gives maximum of two values x & y */

#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc)) 

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))        
#define PUT(p, val)  (*(unsigned int *)(p) = (val)) 

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)                  
#define GET_ALLOC(p) (GET(p) & 0x1)                  

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)                      
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE))) 
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* Given block ptr bp, get next free block address and previous block address */

#define NEXTFREE(bp)  ((!(*(unsigned int *)(bp)))? 0 :((char*)(heap_listp) + \
                        *(unsigned int *)(bp)))
#define PREVFREE(bp)  ((!(*((unsigned int *)(bp) + 1))) ? 0 :((char*)\
                        (heap_listp) + *((unsigned int *)(bp)+1)))

/* Given block ptr bp, get and put the pointer to 4 byte memory using offset */
#define GETPTR(bp) ((!(*(unsigned int *)(bp)))? 0 :((char*)(heap_listp) \
                        + *(unsigned int *)(bp)))
#define PUTPTR(bp,val) (((val) == 0) ? (*(unsigned int *)(bp) = 0):(*\
                        (unsigned int *)(bp) = ((char*)(val)- \
                                (char*)(heap_listp))))


/* Given block ptr bp, get and put the successor & predessor to 4 byte memory 
 *  in a free block using offset */
#define WRITESUCCESSOR(bp,val) (((val) == 0) ? (*(unsigned int *)(bp) = 0):\
                (*(unsigned int *)(bp) = ((char*)(val)- (char*)(heap_listp))))

#define WRITEPREDESSOR(bp,val) (((val) == 0) ? ((*((unsigned int *)(bp) + 1)) \
                        = 0):(*((unsigned int *)(bp) + 1) = ((char*)(val) - \
                                        (char*)(heap_listp))))


/* Get the head of seggregated list at index i with the top of seggregated list
 * pointed by bucket_ptr
 */


#define BUCKET_ELEM(i) ((unsigned int *)(bucket_ptr) + i)


/* $end mallocmacros */

/* Global variables */
static char *heap_listp = 0;  /* Pointe to first block */  

/* start variable will keep the pointer to the node for the 
 * current seggregated list in action 
 * If seggregated list 1 is being used , start will point to the node
 * pointed by the same list's head node.
 * After start is changed or modified, start contents will be modified 
 * to the head node of the same list
 */

static char * start = 0; /* Pointer to root of free list */

/*
 * Bucket_number : It keeps track of the head node which can 
 * be obtained by indexing into the bucket pointer
 * findList function will get the index based on the size of the block 
 * requested and update the index to bucket_number 
 */

static char * bucket_ptr = 0;/* Start of the seggregated lsit array*/
static int bucket_number = 0;/*global variable to track the */
//static char * end = 0 ; /* Pointer to end of free list */


/* Function prototypes for internal helper routines */

/*
 * extend_heap : extends the heap by number of words 
 *
 * parameter : words
 */

static void *extend_heap(size_t words);

/*
 * place : place the block at the block pointed by bp and splits the block
 * i//f actual size of block is greater than 16 bytes. Places removes the block 
 * from the seggregated list and joins other two blocks
 *
 * parameter : block pointer, required size
 */

static void place(void *bp, size_t asize);

/*
 * find_fit : searches the free list for first fit and returns
 * the pointer to the block
 *
 * parameter : actual size of block
 */

static void *find_fit(size_t asize);

/*
 * coalesce : joins two free blocks if they are adjacent to each other
 * and combines the Next Free and Prev Free blocks together and if the
 * block's next FREE is null, it moves the previous block to null. If 
 * bloc is at the begining of the list, it sets the next block previous 
 * pointer to NULL and start points to Next block
 *
 * parameter : block pointer
 */



static void *coalesce(void *bp);

/*
 * checkblock : check the 8 byte alignment of the block 
 * parameter : block pointer
 */

static void checkblock(void *bp);

/*
 * movFreeBlock_top : moving the newly freed block to the top of the list
 * or the large block which is split after allocating heap for the requested
 * block in case the required size is less than 16 bytes of the total size
 *
 * parameter : block pointer
 */


static void movFreeBlock_top(void * bp);

/*
 * joinTwoBlocks : It takes care of combining Next and free blocks of adjacent 
 * block in case the block pointed to by bp is getting coalesced with the 
 * adjacent block .
 * It also takes care when place request for heap allocation is in process by 
 * taking care of the same block's Previous and Next nodes
 *
 * parameter : pointer to block (bp) , next (NEXT - 1 for hadling next block 
 * nodes, PREV-0 for handling previous block's nodes, CURR- 0 for handling its 
 * nodes
 */

static void joinTwoBlocks(void * bp,int next);

/*
 * findList : It helps in finding the seggregated list based on the size of the
 * block request. It sets the global pointer start to the value located by head 
 * of the desired seggregated list and sets the global variable to bucket_number
 *
 * parameters : size (size of the block)
 */

static void findList(size_t size);

/*
 * updateList - updates the value of global start variable to the desired 
 * seggregated list (found by findList). bucket_number set by findList function
 * becomes an index to bucket_ptr. Start is updated to that head. 
 */

static void updateList();

/*
 * movFreeBlock_top : moving the newly freed block to the top of the list
 * or the large block which is split after allocating heap for the requested
 * block in case the required size is less than 16 bytes of the total size
 *
 * parameter : block pointer
 */
static void movFreeBlock_top(void * bp) 
{
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
}
/* 
 *  * mm_init - Initialize the memory manager 
 *  This initializes a 12 words for storing the heads of all seggregated list
 *  and then allocates 4 words for epilogue and prologue headers. 
 *  It extends the heap by chunksize by chunksize of 256 bytes
 */   


int mm_init(void) 
{
	start = 0;

	unsigned int number_buckets = ((BUCKET % 2)?( BUCKET + 1) : BUCKET); 
	size_t size = 4*WSIZE + number_buckets * WSIZE;

	if ((heap_listp = mem_sbrk(size)) == (void *)-1) 
		return -1;
			   
	bucket_ptr = (char * ) heap_listp ;
	unsigned int i ;
	for (i = 0 ; i < number_buckets; i++ ) 
	{
		PUTPTR(BUCKET_ELEM(i),0);
	}
	heap_listp = (char * ) bucket_ptr + number_buckets*WSIZE;
	PUT(heap_listp, 0);                          /* Alignment padding */
	PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue header */ 
	PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Prologue footer */ 

	PUT(heap_listp + (3*WSIZE), PACK(0, 1));     /* Epilogue header */
	heap_listp += (2*WSIZE);

	char * bp = NULL;
	if ((bp=extend_heap(CHUNKSIZE/WSIZE)) == NULL) 
		    return -1;
	    return 0;
}



/*
 * findList : It helps in finding the seggregated list based on the size of the
 * block request. It sets the global pointer start to the value located by head 
 * of the desired seggregated list and sets the global variable to bucket_number
 *
 * parameters : size (size of the block)
 */
static void findList(size_t size) 
{
        unsigned int index = BINDEX12;

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
        bucket_number = index;
}

/*
 * updateList - updates the value of global start variable to the desired 
 * seggregated list (found by findList). bucket_number set by findList function
 * becomes an index to bucket_ptr. Start is updated to that head. 
 */
static void updateList() 
{
        PUTPTR(BUCKET_ELEM(bucket_number),start);

}



/* 
 *  _malloc - Allocate a block with at least size bytes of payload 
 *  From the size, it finds for the fit in the appropriate seggregated 
 *  list                  
 */

void *malloc(size_t size) 
{
	size_t asize;      /* Adjusted block size */
	size_t extendsize; /* Amount to extend heap if no fit */
	char *bp;      

	/* $end mmmalloc */
	if (heap_listp == 0){
	mm_init();
	}
	/* $begin mmmalloc */
	    /* Ignore spurious requests */
	if (size == 0)
	return NULL;

	if (size <= DSIZE)            
	    asize = 2*DSIZE;         
	else 
	{

	    asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE); 
	}
	findList(asize);
	/* Search the free list for a fit */

	if ((bp = find_fit(asize)) != NULL) {  
	    place(bp, asize);                 
	    return bp;
	}

			    /* No fit found. Get more memory and 
			     * place the block */
	extendsize = MAX(asize,CHUNKSIZE);   
	if ((bp = extend_heap(extendsize/WSIZE)) == NULL)  
	    return NULL;                   
	place(bp, asize);       
	return bp;
} 

/* 
 *  free - Free a block and then sets the NEXT Free and prev free pointer
 *  to null and then coalesce with adjacent blocks and finally is moved to 
 *  the top of appropriate seggregated list based on the final size of free
 *  block
 *              
 *  parameter - pointer to the block to be freed              
 */ 
void free(void *bp)
{
	/* $end mmfree */
	if(bp == 0) 
		return;

	/* $begin mmfree */
	size_t size = GET_SIZE(HDRP(bp));
	/* $end mmfree */
	if (heap_listp == 0)
	{
		mm_init();
	}
	    /* $begin mmfree */

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	WRITESUCCESSOR(bp,0);
	WRITEPREDESSOR(bp,0);
	coalesce(bp);
}



/*
 * joinTwoBlocks : It takes care of combining Next and free blocks of adjacent 
 * block in case the block pointed to by bp is getting coalesced with the 
 * adjacent block .
 * It also takes care when place request for heap allocation is in process by 
 * taking care of the same block's Previous and Next nodes
 *
 * parameter : pointer to block (bp) , next (NEXT - 1 for hadling next block 
 * nodes, PREV-0 for handling previous block's nodes, CURR- 0 for handling its 
 * nodes
 */

static void joinTwoBlocks(void * bp,int next) 
{
    char * Blk = NULL;
    switch (next) 
    {
            /* Handling next block nodes*/
            case NEXT:
                    Blk = NEXT_BLKP(bp);
                    break;
            /* Handling prevblock nodes*/
            case PREV :
                    Blk = PREV_BLKP(bp);
                    break;
            /* Handling its own nodes*/
            case CURR :
                    Blk = bp;
    }
    char * nextBlk = NEXTFREE(Blk);
    char * prevBlk = PREVFREE(Blk);

    
    if (nextBlk == NULL && prevBlk == NULL ) 
    {
        start = 0 ;
    }

    
    if (nextBlk == NULL && prevBlk != NULL ) 
    {
        WRITESUCCESSOR(prevBlk,0);
    }

    if (nextBlk != NULL && prevBlk == NULL ) 
    {
        WRITEPREDESSOR(nextBlk,0);
        start = nextBlk;
    }     
    if (nextBlk != NULL && prevBlk != NULL ) 
    {
        WRITESUCCESSOR(prevBlk,nextBlk);
        WRITEPREDESSOR(nextBlk,prevBlk);
    } 
}



/*
 *  coalesce : combine two adjacent free blocks and handles the adjcent block
 *  free and previous pointers by calling joinTwoBlocks functions and moves the
 *  resultant block to the top of seggregated list
 *
 *  
 *  parameter : block pointer
 *
 *  
 */
static void *coalesce(void *bp) 
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HDRP(bp));

	char * start1 = start;
	int prevBucket = bucket_number;

	if (prev_alloc && next_alloc) {            /* Case 1 */
	    findList(size); //Selecting the seggregated list and setting start 
	    movFreeBlock_top(bp);//moving to top of the list
	    updateList();//updating the seggregated list
	    return bp;
	}

	else if (prev_alloc && !next_alloc) {      /* Case 2 */
	    findList(GET_SIZE(HDRP(NEXT_BLKP(bp))));
	    joinTwoBlocks(bp,NEXT);
	    updateList();

        /* Coalescing the next block*/
	    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
	    PUT(HDRP(bp), PACK(size, 0));
	    PUT(FTRP(bp), PACK(size,0));
	}

	else if (!prev_alloc && next_alloc) {      /* Case 3 */
        /* Selecting the seggregated list*/
	    findList(GET_SIZE(HDRP(PREV_BLKP(bp))));
	    joinTwoBlocks(bp,PREV);
	    updateList();
        /* Coalescing the prev block*/

	    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
	    PUT(FTRP(bp), PACK(size, 0));
	    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
	    bp = PREV_BLKP(bp);
	}

	else {                                     /* Case 4 */

        /* Selecting the seggregated list*/
	    findList(GET_SIZE(HDRP(NEXT_BLKP(bp))));
	    joinTwoBlocks(bp,NEXT);
	    updateList();

        /* Selecting the seggregated list*/
	    findList(GET_SIZE(HDRP(PREV_BLKP(bp))));
	    joinTwoBlocks(bp,PREV);
	    updateList();

        /* Coalescing the prev and next block*/
	    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
	    GET_SIZE(FTRP(NEXT_BLKP(bp)));
	    PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
	    PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
	    bp = PREV_BLKP(bp);
	}
        /* Selecting the seggregated list and moving to the top*/
	findList(size);
	movFreeBlock_top(bp);
	updateList();

	start = start1;

	bucket_number = prevBucket;
	return bp;
}
/* $end mmfree */

/*
 *  * realloc- Naive implementation of realloc
 */
void *realloc(void *ptr, size_t size)
{
	size_t oldsize;
	void *newptr;

	/* If size == 0 then this is just free, and we return NULL. 
	* */
	if(size == 0) 
	{
		mm_free(ptr);
		return 0;
	}

	/* If oldptr is NULL, then this is just malloc. */
	if(ptr == NULL) 
	{
		return malloc(size);
	}

	newptr = malloc(size);

		/* If realloc() fails the original block is left 
		 * untouched  */
	if(!newptr) 
	{
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
 * calloc - Allocate the block and set it to zero.
 */
void *calloc (size_t memb, size_t size)
{
	size_t bytes = memb * size;
	void *newptr;

	newptr = malloc(bytes);
	memset(newptr, 0, bytes);

	return newptr;
}


/*
 * extend_heap : extends the heap by number of words 
 *
 * parameter : words
 */

static void *extend_heap(size_t words) 
{
	char *bp;
	size_t size;

	/* Allocate an even number of words to maintain alignment */
	size = (words % 2) ? (words+1) * WSIZE : words * WSIZE; 
	if ((long)(bp = mem_sbrk(size)) == -1)  
		    return NULL;                               

	    /* Initialize free block header/footer and the 
	     * epilogue header */
	PUT(HDRP(bp), PACK(size, 0));         /* Free block header */  
	PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */ 
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */ 
	WRITESUCCESSOR(bp,0);
	WRITEPREDESSOR(bp,0);

	/* Coalesce if the previous block was 
	* free */
	return coalesce(bp);                                          
}
/* $end mmextendheap */

/*
 * place : place the block at the block pointed by bp and splits the block
 * i//f actual size of block is greater than 16 bytes. Places removes the block 
 * from the seggregated list and joins other two blocks
 *
 * parameter : block pointer, required size
 */
static void place(void *bp, size_t asize)
             /* $end mmplace-proto */
{
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
                    char * start1 = start;
                    int prevBucket = bucket_number;
                    findList(csize-asize);
                    movFreeBlock_top(bp);
                    updateList();
                    start = start1;
                    bucket_number = prevBucket;

            }
            else { 
                    PUT(HDRP(bp), PACK(csize, 1));
                    PUT(FTRP(bp), PACK(csize, 1));

            }

}

/*
 * find_fit : searches the free list for first fit and returns
 * the pointer to the block
 *
 * parameter : actual size of block
 */

static void *find_fit(size_t asize)
{
	/* First fit search */
	void *bp;
	//mm_checkheap(420);
	char * start1;
	int i = bucket_number ;
	for ( start1 = GETPTR(BUCKET_ELEM(bucket_number)); i < BUCKET; 
                    start1=GETPTR(BUCKET_ELEM(i)))
	{
	for (bp = start1; bp != NULL ; bp = (void *) NEXTFREE(bp)) 
	{
		if (asize <= GET_SIZE(HDRP(bp))) {
			    return bp;
		}

	}
	i++;
	}
	return NULL; /* No fit */
}


/*
 * checkblock : Check block's alignment (8-bit)
 */

static void checkblock(void *bp) 
{
	if ((size_t)bp % 8)
		printf("Error: %p is not doubleword aligned\n", bp);
	if (GET(HDRP(bp)) != GET(FTRP(bp)))
		printf("Error: header does not match footer %d and %d\n",GET(HDRP(bp)),
                        GET(FTRP(bp)));
}

/* 
 *  * checkheap - Minimal check of the heap for consistency 
 *   */
void mm_checkheap(int verbose) 
{
            char *bp = heap_listp;
            //int i = 0 ;
            //char * temp = start;
/*1.  Checking epilogue and prologue blocks */

            if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || 
                            !GET_ALLOC(HDRP(heap_listp)))
                    printf("Bad prologue header\n");

            if (verbose)
                for (bp=heap_listp; GET_SIZE(HDRP(bp))> 0; bp = NEXT_BLKP(bp)) 
                {
                }
                if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
                        printf("Bad epilogue header\n");

/*2. Checking block's alignment */
                    checkblock(heap_listp);

            for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) 
            {

                    if (verbose)
                            checkblock(bp);
            }


/* 3. Checking Heap boundaries */
            if (bucket_ptr != mem_heap_lo()) 
            {
                    printf("Bad starting memory boundary\n");
                    exit(-1);
            }
                                          
            for (bp=heap_listp; GET_SIZE(HDRP(bp))> 0; bp = NEXT_BLKP(bp)) 
            {
            }
            if (bp != mem_heap_hi() + 1) 
            {
                    printf("Bad ending memory boundary\n");
                    exit(-1);
            }

/* 4. Check each block's header and footer consistency */

            for (bp=heap_listp; GET_SIZE(HDRP(bp))> 0; bp = NEXT_BLKP(bp)) 
            {
                    if (GET_SIZE(HDRP(bp)) != GET_SIZE(FTRP(bp))) { 
                            printf("Size is different in header \
                                            and footer of block %p\n",bp);
                            exit(-1);
                    }
                    if (GET_ALLOC(HDRP(bp)) != GET_ALLOC(FTRP(bp))) { 
                            printf("Alloc is different in header \
                                            and footer of block %p\n",bp);
                            exit(-1);
                    }
                    if (GET(HDRP(bp)) != GET(FTRP(bp))) { 
                            printf("Fields are different in header \
                                            and footer of block %p\n",bp);
                            exit(-1);
                    }
            }

/* 5. No two consecutive free blocks are together in the heap*/
            for (bp=heap_listp; GET_SIZE(HDRP(bp))> 0; bp = NEXT_BLKP(bp)) 
            {
                    if (!GET_ALLOC(HDRP(bp)) && 
                                    !GET_ALLOC(HDRP(NEXT_BLKP(bp)))) 
                    { 
                            printf("Two free blocks are together %p \n",bp);
                            exit(-1);
                    }
                    
            }
/* 6. Checking if the pointers are consistent in the seggregated list and free 
 * list pointers are in the range between mem_heap_lo & mem_heap_high */
            char * start1 = NULL;
            int i = 0 ;
            char * temp1;
            for (start1=GETPTR(BUCKET_ELEM(i));i < BUCKET; 
                            start1=GETPTR(BUCKET_ELEM(i)))
            {
                for(temp1 = start1;temp1!=NULL;temp1 = NEXTFREE(temp1)) 
                {
                       if(!((void*)temp1 < (void*)mem_heap_hi()) && 
                                       !((void*)temp1>(void*) mem_heap_lo())) 
                       {
                               printf("Free list pointers are out \
                                               of range %p\n",temp1);
                       }
                       if(NEXTFREE(temp1) != NULL) 
                       {
                               if(temp1 != PREVFREE(NEXTFREE(temp1))) 
                               {
                                       printf("Prev and next pointers\
                                                       are not \
                                                       matching %p\n",temp1);
                               }
                       }
                }
                i++;
            }
/* 
 * 7. Checking if free pointers are equal in the seggregated list and implicit
 * 
 */
            int countSeg = 0 ;
            int countImp = 0 ;
            for (start1=GETPTR(BUCKET_ELEM(i));i < BUCKET; 
                            start1=GETPTR(BUCKET_ELEM(i)))
            {
                for(temp1 = start1;temp1!=NULL;temp1 = NEXTFREE(temp1)) 
                {
                      countSeg++; 
                }
                i++;
            }

            for (bp=heap_listp; GET_SIZE(HDRP(bp))> 0; bp = NEXT_BLKP(bp)) 
            {
                countImp++;

            }

            
/* 8. checking if the bucket ranges are in the same list */
            i = 0 ;
            int bucketIndex ;
           for (start1=GETPTR(BUCKET_ELEM(i));i < BUCKET; 
                            start1=GETPTR(BUCKET_ELEM(i)))
            {
                for(temp1 = start1;temp1!=NULL;temp1 = NEXTFREE(temp1)) 
                {
                        findList(GET_SIZE(HDRP(temp1)));
                        bucketIndex = bucket_number;
                        if(bucketIndex != i ) 
                        {
                                printf("Bucket size not in proper list\
                                                block : %p \n",temp1);
                                exit(-1);
                        }
                }
                i++;
            } 
}

