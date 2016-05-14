/* 
 * Simple, 32-bit and 64-bit clean allocator based on explicit free
 * lists, first-fit placement, and boundary tag coalescing, as described
 * in the CS:APP3e text. Blocks must be aligned to doubleword (8 byte) 
 * boundaries. Minimum block size is 24 bytes. 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mm.h"
#include "memlib.h"

/* do not change the following! */
#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/*
 * If NEXT_FIT defined use next fit search, else use first-fit search 
 */
#define NEXT_FITx

/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */ 
#define DSIZE       8       /* Double word size (bytes) */
#define CHUNKSIZE  (1<<12)  /* Extend heap by this amount (bytes) */ 
#define MINSIZE     24

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

/* Given free block ptr bp, computer address of next and previous free blocks */
#define NEXT_FREEBLKP(bp) (*(char **)(bp + DSIZE))
#define PREV_FREEBLKP(bp) (*(char **)(bp))

/* Global variables */
static char* heap_listp = 0;        /* Pointer to first block */  
static char* free_listp = NULL;     // Points to start of linked list of free blocks

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);
static void printblock(void* bp);
static void checkheap(int lineno);
static void checkblock(void* bp);
static void insert(void* bp);
static void removeFree(void* bp);

// mm_init - Initialize the memory manager 
int mm_init(void) {
    printf("\n\t\t Initializing heap...\n\n");
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1) 
        return -1;
    PUT(heap_listp, 0);                          /* Alignment padding */
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue header */ 
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Prologue footer */ 
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));     /* Epilogue header */
    heap_listp += (2*WSIZE); // Set heap_listp to point to prologue footer
    
    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) 
        return -1;
    mm_checkheap(__LINE__);
    return 0;
}

 
// malloc - Allocate a block with at least size bytes of payload 
void* malloc(size_t size) {
    printf("\n\t\t Mallocing a block of size %zu...\n\n", size);
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;      
    
    // Check if the heap has been initialized. If it's not, then initialize it.
    if (heap_listp == 0) {
        mm_init();
        mm_checkheap(__LINE__);
    }
    
    /* Ignore spurious requests */
    if (size == 0) {
        return NULL;
    }

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= MINSIZE) {                                       
        asize = MINSIZE;  
    } else {
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE); 
    }

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        mm_checkheap(__LINE__);
        place(bp, asize);
        mm_checkheap(__LINE__);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize,CHUNKSIZE);  
    mm_checkheap(__LINE__);    
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL) { // We've run out of memory
        return NULL;                                  
    }
    place(bp, asize);
    mm_checkheap(__LINE__);    
    return bp;
} 

// free - Free a block 
void free(void *bp) {
    printf("\n\t\t Freeing block at address %p...\n\n", bp);
    mm_checkheap(__LINE__);
    if (bp == 0) { // We're trying to free NULL
        return;
    }
    
    size_t size = GET_SIZE(HDRP(bp)); 
    if (heap_listp == 0){
        mm_init();
        mm_checkheap(__LINE__);
    }

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    insert(bp);
    mm_checkheap(__LINE__);
    //coalesce(bp);
}

// realloc - Naive implementation of realloc
void* realloc(void *ptr, size_t size) {
    printf("\n\t\t\t Reallocing block at address %p with size %zu...\n\n", ptr, size);
    mm_checkheap(__LINE__);
    size_t oldsize;
    void *newptr;

    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0) {
        mm_free(ptr);
        return 0;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if(ptr == NULL) {
        return mm_malloc(size);
    }

    newptr = mm_malloc(size);

    /* If realloc() fails the original block is left untouched  */
    if(!newptr) {
        return 0;
    }

    /* Copy the old data. */
    oldsize = GET_SIZE(HDRP(ptr));
    if(size < oldsize) oldsize = size;
    memcpy(newptr, ptr, oldsize);

    /* Free the old block. */
    mm_free(ptr);
    mm_checkheap(__LINE__);
    return newptr;
}

// mm_checkheap - Check the heap for correctness. Helpful hint: You
//                can call this function using mm_checkheap(__LINE__);
//                to identify the line number of the call site.
void mm_checkheap(int lineno)  { 
    printf("ENTERING CHECKHEAP AT LINE %d\n", lineno);
    checkheap(lineno);
    printf("EXITING CHECKHEAP AT LINE %d\n", lineno);
}

/************The remaining routines are internal helper routines**************/

// extend_heap - Extend heap with free block and return its block pointer
static void* extend_heap(size_t words) {
    printf("\n\t\t Extending heap by at least %zu words...\n\n", words);
    mm_checkheap(__LINE__);
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)  
        return NULL;                                        

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));         /* Free block header */   
    PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */   
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */ 
    insert(bp);
    mm_checkheap(__LINE__);
    /* Coalesce if the previous block was free */
    //return coalesce(bp);       
    return bp;                                   
}

// coalesce - Boundary tag coalescing. Return ptr to coalesced block
static void* coalesce(void* bp) {
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    

    if (prev_alloc && next_alloc) {            /* Case 1 */
        return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2 */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size,0));
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {                                     /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
            GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}

static void* get_epiloguep(void) {
    char* bp = heap_listp;
    while(GET_SIZE(HDRP(bp)) != 0) {
        bp = NEXT_BLKP(bp);
    }
    return bp;
}

static void print_heap(void) {
    char* bp;
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) != 0; bp = NEXT_BLKP(bp)) {
            printf("Block at %p is of size %d\n", bp, GET_SIZE(HDRP(bp)));
    }
}

// place - Place block of asize bytes at start of free block bp 
//         and split if remainder would be at least minimum block size
static void place(void* bp, size_t asize) {
    //printf("Allocating %zu into pointer %p\n", asize, bp);
    
    mm_checkheap(__LINE__);
    size_t csize = GET_SIZE(HDRP(bp));
    char* ep = get_epiloguep();
    printf("hsize = %d, fsize = %d, csize = %zu, asize = %zu, mem_heap_hi = %p, HDRP(bp) = %p, FTRP(bp) = %p, bp = %p, ep = %p\n", 
            GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), csize, asize, mem_heap_hi(), HDRP(bp), FTRP(bp), bp, ep);
    if ((csize - asize) >= MINSIZE) {
        removeFree(bp);
            /*
            ep = get_epiloguep();
            print_heap();
            printf("At line %d, bp = %p, hsize = %d, fsize = %d, HDRP(bp) = %p, FTRP(bp) = %p, ep = %p\n", 
                    __LINE__, bp, GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), HDRP(bp), FTRP(bp), ep);
            */
        PUT(HDRP(bp), PACK(asize, 1));
            /*
            ep = get_epiloguep();
            print_heap();
            printf("At line %d, bp = %p, hsize = %d, fsize = %d, HDRP(bp) = %p, FTRP(bp) = %p, ep = %p\n", 
                    __LINE__, bp, GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), HDRP(bp), FTRP(bp), ep);
            */
        PUT(FTRP(bp), PACK(asize, 1));
            /*
            ep = get_epiloguep();
            print_heap();
            printf("At line %d, bp = %p, hsize = %d, fsize = %d, HDRP(bp) = %p, FTRP(bp) = %p, ep = %p\n", 
                    __LINE__, bp, GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), HDRP(bp), FTRP(bp), ep);
            mm_checkheap(__LINE__);
            */
            /*
            printf("hsize = %d, fsize = %d, csize = %zu, asize = %zu, mem_heap_hi = %p, HDRP(bp) = %p, FTRP(bp) = %p, bp = %p\n", 
                GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), csize, asize, mem_heap_hi(), HDRP(bp), FTRP(bp), bp);
            */
            /*printf("hsize = %d, fsize = %d, csize = %zu, asize = %zu, mem_heap_hi = %p, HDRP(bp) = %p, FTRP(bp) = %p, bp = %p\n", 
            G   ET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), csize, asize, mem_heap_hi(), HDRP(bp), FTRP(bp), bp);
            */
            //mm_checkheap(__LINE__);
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
            /*printf("hsize = %d, fsize = %d, csize = %zu, asize = %zu, mem_heap_hi = %p, HDRP(bp) = %p, FTRP(bp) = %p, bp = %p\n", 
                GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), csize, asize, mem_heap_hi(), HDRP(bp), FTRP(bp), bp);
            */
        PUT(FTRP(bp), PACK(csize-asize, 0));
        insert(bp);
        mm_checkheap(__LINE__);
        
    }
    else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
        removeFree(bp);
        mm_checkheap(__LINE__);
    }
    mm_checkheap(__LINE__);
}

// removeFree - removes free_bp from linked list
static void removeFree(void* free_bp) {
    // Handle predecessor's succ field
    if (PREV_FREEBLKP(free_bp) != NULL) {
        NEXT_FREEBLKP(PREV_FREEBLKP(free_bp)) = NEXT_FREEBLKP(free_bp);
    } else {
        // Case where we're at the front of the list
        free_listp = NEXT_FREEBLKP(free_bp);
    }

    // Handle successor's pred field
    if (NEXT_FREEBLKP(free_bp) != NULL) {
        PREV_FREEBLKP(NEXT_FREEBLKP(free_bp)) = PREV_FREEBLKP(free_bp);
    }
}

// insert - inserts free_bp to beginning of linked list
static void insert(void* free_bp) {
    printf("inserting free_bp = %p, GET_SIZE(HDRP(free_bp)) = %d, FTR = %p, max_address = %p\n", 
            free_bp, GET_SIZE(HDRP(free_bp)), FTRP(free_bp), mem_heap_hi());
    // Update the pred and succ fields of free_bp
    PREV_FREEBLKP(free_bp) = NULL;
    NEXT_FREEBLKP(free_bp) = free_listp;

    // Update the pred field of free_listp
    if (free_listp != NULL) {
        PREV_FREEBLKP(free_listp) = free_bp;
    }
    free_listp = free_bp;
    mm_checkheap(__LINE__);
}
 
// find_fit - Find a fit for a block with asize bytes 
static void* find_fit(size_t asize) {
    mm_checkheap(__LINE__);
    /* First-fit search */
    void *bp;

    /*for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            mm_checkheap(__LINE__);
            return bp;
        }
    }*/
    for (bp = free_listp; bp != NULL; bp = NEXT_FREEBLKP(bp)) {
        if (asize <= GET_SIZE(HDRP(bp))) {
            mm_checkheap(__LINE__);
            return bp;
        }
    }
    mm_checkheap(__LINE__);
    return NULL; /* No fit */
}

static void printblock(void *bp) {
    size_t hsize, halloc, fsize, falloc;
              
    hsize = GET_SIZE(HDRP(bp));
    halloc = GET_ALLOC(HDRP(bp));  
    fsize = GET_SIZE(FTRP(bp));
    falloc = GET_ALLOC(FTRP(bp));  

    if (hsize == 0) {
        printf("%p: EOL\n", bp);
        return;
    }

    printf("%p: header: [%ld:%c] footer: [%ld:%c]\n", bp, 
            hsize, (halloc ? 'a' : 'f'), 
            fsize, (falloc ? 'a' : 'f')); 
}

static void checkblock(void *bp) {
    if ((size_t)bp % 8) {
        printf("Error: %p is not doubleword aligned\n", bp);
        printblock(bp);
        exit(1);
    }
    if (GET(HDRP(bp)) != GET(FTRP(bp))) {
        printf("Error: header does not match footer\n");
        printblock(bp);
        exit(1);
    }
}

/* 
 *  * checkheap - Minimal check of the heap for consistency 
 *   */
void checkheap(int verbose) {
    char *bp = heap_listp;
    
    if (verbose) {
        //printf("Heap (%p):\n", heap_listp);
    }

    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
        printf("Bad prologue header\n");
        exit(1);
    }
    checkblock(heap_listp);

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (verbose) 
            printblock(bp);
        checkblock(bp);
    }

    if (verbose)
        //printblock(bp);

    printf("epilogue size = %d, epilogue alloc bit = %d\n", GET_SIZE(HDRP(bp)), GET_ALLOC(HDRP(bp)));
    printf("Epilogue address = %p \t max_heap_address = %p\n", HDRP(bp), mem_heap_hi());
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp)))) {
        printf("Bad epilogue header\n");
        exit(1);
    }
}


/*static void printblock(void* bp) {
    size_t hsize = GET_SIZE(HDRP(bp));
    size_t halloc = GET_ALLOC(HDRP(bp));
    size_t fsize = GET_SIZE(FTRP(bp));
    size_t falloc = GET_ALLOC(FTRP(bp));

    if (hsize == 0) {
        printf("\t\t %p: EOL\n", bp);
        return;
    }

    printf("\t\t %p: header: [%ld:%c] footer : [%ld:%c]\n", bp,
            hsize, (halloc ? 'a' : 'f'),
            fsize, (falloc ? 'a' : 'f'));
}

static void checkblock(void* bp) {
    // Check for proper alignment
    if ((size_t)bp % 8) {
        printf("\t ERROR: Block at address %p is not doubleword aligned\n", bp);
        printblock(bp);
        exit(1);
    }
    
    // Ensure that header and footer match
    if (GET(HDRP(bp)) != GET(FTRP(bp))) {
        printf("\t ERROR: Header and footer do not match (bp = %p)\n", bp);
        printblock(bp);
        exit(1);
    }
    
    // Ensure that the block address is within bounds
    if ((void*)bp < mem_heap_lo() || mem_heap_hi() < (void*)bp) {
        printf("\t ERROR: Block address not in bounds\n");
        printblock(bp);
        exit(1);
    }

    // If the block is free, ensure that it occurs in the free list exactly once
    if (!GET_ALLOC(HDRP(bp))) {
        char* free_bp;
        int found = 0;
        
        for (free_bp = free_listp; free_bp != NULL; free_bp = NEXT_FREEBLKP(free_bp)) {
            if (free_bp == bp) {
                found++;
            }

            if (found > 1) {
                printf("\t ERROR: Free block repeated in free list (bp = %p)\n", bp);
                printblock(free_bp);
                exit(1);
            }
        }
        if (found == 0) {
            printf("\t ERROR: free block not in free list (bp = %p)\n", bp);
            printblock(bp);
            exit(1);
        }
    }
}

static void checkheap(int lineno) {
    char* slow;
    char* fast;
    char* free_bp;
    char* bp;
    int implicit_free_count = 0;
    int explicit_free_count = 0;
    printf("ENTERING CHECKEAP AT LINE %d\n", lineno);
    printf("Heap address : %p\n", heap_listp);
    
    // Check prologue header
    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp))) {
        printf("\t ERROR: Bad prologue header\n");
        printf("\t\t Heap prologue header address : %p\n", HDRP(heap_listp));
        printf("\t\t Heap prologue header contents : %d\n", *HDRP(heap_listp));
        exit(1);
    }

    // Check prologue footer
    if (GET_SIZE(heap_listp) != DSIZE || !GET_ALLOC(heap_listp)) {
        printf("\t ERROR: Bad prologue footer\n");
        printf("\t\t Heap prologue footer address : %p\n", heap_listp);
        printf("\t\t Heap prologue footer contents : %d\n", *heap_listp);
        exit(1);
    }
    
    // Check free list for cycles
    slow = free_listp;
    fast = free_listp;

    while ((slow != NULL) && (fast != NULL) && (NEXT_FREEBLKP(fast) != NULL)) {
        printf("slow = %p", slow);
        printf("\tfast = %p\n", fast);
        slow = NEXT_FREEBLKP(slow);
        fast = NEXT_FREEBLKP(NEXT_FREEBLKP(fast));
        if (slow == fast) {
            printf("slow = %p\n", slow);
            printf("fast = %p\n", fast);
            printf("\t ERROR: Cycle found in free list\n");
            exit(1);
        }
    }
   
    // Traverse heap linearly by reading sizes
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        checkblock(bp);
        if (!GET_ALLOC(HDRP(bp))) implicit_free_count++;
    }    

    // Check free list for consistent ordering
    for (free_bp = free_listp; free_bp != NULL; free_bp = NEXT_FREEBLKP(free_bp)) {
        explicit_free_count++;
        if ((PREV_FREEBLKP(free_bp) != NULL) && (NEXT_FREEBLKP(PREV_FREEBLKP(free_bp)) != free_bp)) {
            printf("\t ERROR: linked list ordering inconsistent\n");
            printf("\t\t NEXT_FREEBLKP(PREV_FREEBLKP(free_bp)) != free_bp\n");
            printblock(free_bp);
            exit(1);
        }

        if ((NEXT_FREEBLKP(free_bp) != NULL) && (PREV_FREEBLKP(NEXT_FREEBLKP(free_bp)) != free_bp)) {
            printf("\t ERROR: linked list ordering inconsistent\n");
            printf("\t\t PREV_FREEBLKP(NEXT_FREEBLKP(free_bp)) != free_bp\n");
            printblock(free_bp);
            exit(1);
        }
    }

    if (explicit_free_count != implicit_free_count) {
        printf("\t ERROR: Number of free blocks in explicit and implicit lists differ\n");
        printf("\t\t explicit_free_count = %d; implicit_free_count = %d\n", explicit_free_count, implicit_free_count);
        exit(1);
    }


    // Check epilogue block
    if ((GET_SIZE(HDRP(bp)) != 0) || !GET_ALLOC(HDRP(bp))) {
        printf("ERROR: Bad epilogue header\n");
        printf("\t\t Epilogue block address : %p\n", bp);
        printf("\t\t Epilogue block contents : %d\n", *bp);
        exit(1);
    }
    printf("EXITING CHECKHEAP AT LINE %d\n", lineno);
}*/
