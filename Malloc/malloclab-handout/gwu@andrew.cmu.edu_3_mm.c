/*
 * mm.c
 * -----------------------------------------------------------------
 * Name: Guofan Wu
 * Andrew ID: gwu 
 * -----------------------------------------------------------------
 * Final Version: based on mm-textbook.c
 * using segregated freelist to keep track of all the free blocks
 * Since the overall heap cannot be longer than 2^32, we could use 
 * a 32-bit unsigned integer instead of 64-bit address with 
 * heap_listp as a reference 
 * In this way, the minimum block is only 16 bit instead of 24 bit
 * The search is based on first-fit scheme 
 * -----------------------------------------------------------------
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
/*#define DEBUG */
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

/*
 * MACROS for pointer operations: taken from mm-textbook.m
 */

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(p) (((size_t)(p) + (ALIGNMENT-1)) & ~0x7)

/* same macros used in textbooks */
#define WSIZE       4       /* Word and header/footer size (bytes) */ 
#define DSIZE       8       /* Double word size (bytes) */
/* 
 * Extend heap by this amount (bytes)
 * whenever the current block is running out of space 
 * or no fit free block
*/
#define CHUNKSIZE 1<<12

/*
* the minimal block size in bytes, used for deciding whether
* this block needs to be split or not
*/
#define BLK_MIN_SZE 16

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

/* Given block ptr bp, compute integer offsets of the previous and next free block*/
#define NEXT_FKPT(p)			p
#define PREV_FKPT(p)			((char*)p+WSIZE)

/* global variables */
/* pointer to the first block*/
static char *heap_listp = 0; 

/* root pointer for the segragated freelist*/
static void *root_pt = 0; 

/* number of block sizes in the freelist*/
/* to make sure the*/
static size_t BucketSize = 7; 

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);

/* Helper functions for mapping between offset integer and pointer */
static inline unsigned int pt2int(void *bp);
static inline void *int2pt(unsigned int val);

/* Helper functions for manipulating segragated explicit freelist */
static inline void* prev_fbk_pt(void *bp);	
static inline void* next_fbk_pt(void *bp);
static inline size_t get_bucket_num(size_t asize); 
static inline void *get_bucket_root(size_t bnum);
static inline void seg_insert(void *bp, size_t asize);
static inline void seg_delete(void *bp);


/*
 * Initialize: return -1 on error, 0 on success.
 */
int mm_init(void) {
	/*
	 * allocate memory for initialization
	 */
	unsigned int bucket_size = BucketSize * WSIZE;	/* seglist pointer size*/
	unsigned int padd_size = bucket_size + 2 * DSIZE; /* the total block size*/
	unsigned int frk_size = (CHUNKSIZE) - padd_size;	/* size of the initial free block*/
	char *heap_tailp;							/* pointer of the tail*/

	if ((heap_listp = (char *)mem_sbrk(CHUNKSIZE)) == (char*)-1)
	{
		return -1; 
	}
	
	heap_tailp = mem_heap_hi(); 
	/* set up prologue and epilogue header */
	PUT(heap_listp, 0);									/* Alignment padding */
	PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));		/* Prologue header */
	PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));		/* Prologue footer */
	PUT(heap_tailp - (1 * WSIZE)+1, PACK(0, 1));			/* Epilogue header */
	heap_listp += (2 * WSIZE);

	/* allocate the root pointer */
	root_pt = heap_listp;
	/* initialize each pointer */
	memset(root_pt, 0, bucket_size);

	/* set up the initial free block */
	PUT(NEXT_BLKP(heap_listp), PACK(frk_size, 0));
	PUT(heap_tailp - DSIZE, PACK(frk_size, 0));
	dbg_printf("the block size is %ud\n", GET_SIZE(NEXT_BLKP(heap_listp)));
	seg_insert(NEXT_BLKP(heap_listp), frk_size); 

	dbg_printf("initiation completes\n");
	return 0;
}

/*
 * malloc: based on the file mm-textbook.m
 */
void *malloc (size_t size) {
	
	size_t asize;      /* Adjusted block size */
	size_t extendsize; /* Amount to extend heap if no fit */
	char *bp;

	if (heap_listp == 0) {
		mm_init();
	}
	/* Ignore spurious requests */
	if (size == 0)
		return NULL;

	/* Adjust block size to include overhead and alignment reqs. */
	if (size <= DSIZE)
		asize = 2 * DSIZE;
	else
		asize = DSIZE * ((size + (DSIZE)+(DSIZE - 1)) / DSIZE);

	dbg_printf("malloc %zu, asize = %zu\n", size, asize);

	/* Search the free list for a fit */
	if ((bp = find_fit(asize)) != NULL) {
		seg_delete(bp); 
		place(bp, asize);
		return bp;
	}

	/* No fit found. Get more memory and place the block */
	extendsize = MAX(asize, CHUNKSIZE);
	dbg_printf("Heap size not enough, will extend %zu\n", extendsize);
	if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
		return NULL;
	/* add it to the freelist to prevent segmentation fault */
	place(bp, asize);
	dbg_printf("Block sucessfully allocated\n");
	return bp;
}

/*
 * free: free the space allocated for the pointer ptr 
 */
void free (void *bp) {
	void *new_bp;
	if (bp == NULL)
		return;
	
	size_t size = GET_SIZE(HDRP(bp));
	dbg_printf("free block of size %zu\n", size); 
	if (heap_listp == 0) {
		mm_init();
	}

	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));
	/* 
	 * get the pointer of the new free block
	 * and save it to the segregated list
	 */
	new_bp = coalesce(bp);
	size = GET_SIZE(HDRP(new_bp));
	seg_insert(new_bp, size); 
}

/*
 * realloc - original version in mm-textbook.c
 */
void *realloc(void *ptr, size_t size) {
	size_t oldsize;
	void *newptr;

	/* If size == 0 then this is just free, and we return NULL. */
	if (size == 0) {
		free(ptr);
		return 0;
	}

	/* If oldptr is NULL, then this is just malloc. */
	if (ptr == NULL) {
		return malloc(size);
	}

	newptr = malloc(size);

	/* If realloc() fails the original block is left untouched  */
	if (!newptr) {
		return 0;
	}

	/* Copy the old data. */
	oldsize = GET_SIZE(HDRP(ptr));
	if (size < oldsize) oldsize = size;
	memcpy(newptr, ptr, oldsize);

	/* Free the old block. */
	free(ptr);

	return newptr;
}

/*
 * calloc - using "malloc" to allocate memory and then set the chunk 
 * of memory to zero
 */
void *calloc (size_t nmemb, size_t size) {
	char *p;
	size_t byte_num = nmemb * size; 

	/* allocate memory using malloc */
	if ((p = (char*)malloc(byte_num)) != NULL)
	{
		return memset(p, 0, byte_num);
	}
    return NULL;
}


/*
 * Return whether the pointer is in the heap.
 * May be useful for debugging.
 */
static int in_heap(const void *p) {
    return p <= mem_heap_hi() && p >= mem_heap_lo();
}

/*
 * Return whether the pointer is aligned.
 * May be useful for debugging.
 */
static int aligned(const void *p) {
    return (size_t)ALIGN(p) == (size_t)p;
}

/*
 * mm_checkheap: 
 * 1. check for prologue, epilogue and initial padding 
 * 2. check for block size and whether the header and footer are 
 * consistent
 * 3. check whether each free block is within the range given 
 */
void mm_checkheap(int lineno) 
{
	void *heap_tailp = mem_heap_hi();
	void *bp; 
	unsigned int prev_bp_status;
	unsigned int fbk_num1 = 0;
	unsigned int fbk_num2 = 0;
	void *prev_bp, *next_bp; 
	size_t i,bnum; 

	/* check the prologue */
	dbg_printf("Check the prologue\n"); 
	if (!GET_ALLOC(HDRP(heap_listp)) || !GET_ALLOC(FTRP(heap_listp)) || GET(HDRP(heap_listp))!= GET(FTRP(heap_listp)))
	{
		dbg_printf("The prologue allocation has error at line %d \n", lineno);
		return;
	}

	/* check the epilogue */
	dbg_printf("Check the prologue\n");
	if (GET((char*)heap_tailp-3)!=(unsigned int)1)
	{
		dbg_printf("The epilogue allocation has error at line %d\n ", lineno);
		return;
	}

	/* check whether the block is aligned and its header and footer matches*/
	bp = NEXT_BLKP(heap_listp);
	prev_bp_status = !GET_ALLOC(HDRP(bp));
	for (; GET_SIZE(HDRP(bp))>0; bp = NEXT_BLKP(bp))
	{
		/* header footer consistency */
		if (GET_SIZE(HDRP(bp)) != GET_SIZE(FTRP(bp)))
		{
			dbg_printf("Header and footer's sizes are not consistent at line %d\n", lineno);
			return;
		}

		if (GET_ALLOC(HDRP(bp)) != GET_ALLOC(FTRP(bp)))
		{
			dbg_printf("Header and footer's allocators are not consistent at line %d\n", lineno);
			return;
		}
		/* check minimum block size */
		if (GET_SIZE(HDRP(bp))<BLK_MIN_SZE)
		{
			dbg_printf("Block size has error at line %d\n", lineno);
			return;
		}
		/* check the coalesce is correct or not*/
		if (prev_bp_status == GET_ALLOC(HDRP(bp)))
		{
			dbg_printf("Coalesce has error at line %d\n", lineno);
			return;
		}
		/* update the previous block status*/
		prev_bp_status = GET_ALLOC(HDRP(bp));
		
		/* keep track of the free block number*/
		if (!prev_bp_status)
			fbk_num1++; 

		/* check whether the block is aligned or not*/
		if (!aligned(bp))
		{
			dbg_printf("Free block is not aligned at line %d\n", lineno);
			return;
		}
	}
	/* check the freelist */
	for (i = 0; i < BucketSize; i++)
	{
		bp = int2pt(GET(get_bucket_root(i)));
		for (; bp != NULL; bp = next_fbk_pt(bp))
		{
			/* check whether the pointer is properly assigned */
			if (!in_heap(bp))
			{
				dbg_printf("Pointer runs out of heap at line %d\n", lineno);
				return;
			}
			bnum = get_bucket_num(GET_SIZE(HDRP(bp)));
			/* check whether the number is properly assigned */
			if (bnum != i)
			{
				dbg_printf("Free block size doesn't match at line %d\n", lineno);
				return;
			}

			/* update the number of free blocks */
			if (GET_ALLOC(HDRP(bp)))
				fbk_num2++;
			
			/* check the pointer consistency */
			prev_bp = prev_fbk_pt(bp);
			next_bp = next_fbk_pt(bp);
			if (next_bp != NULL)
			{
				if (prev_fbk_pt(next_bp) != bp)
				{
					dbg_printf("Pointer is not consistent in list at line %d\n", lineno);
					return;
				}
			}
			if (prev_bp != NULL)
			{
				if (next_fbk_pt(prev_bp) != bp)
				{
					dbg_printf("Pointer is not consistent in list at line %d\n", lineno);
					return;
				}
			}
		}
	}
	/*
	 * Check the number of free blocks is the same 
	 */
	if (fbk_num1 != fbk_num2)
	{
		dbg_printf("Numbers of free blocks are not consistent at line %d\n", lineno);
		return;
	}
	
}


/*
* The remaining routines are internal helper routines 
* 
*/

/*
* extend_heap - Extend heap with free block and return its block pointer
*/
static void *extend_heap(size_t words)
{
	char *bp;
	size_t size;

	/* Allocate an even number of words to maintain alignment */
	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
	if ((long)(bp = mem_sbrk(size)) == -1)
		return NULL;

	/* Initialize free block header/footer and the epilogue header */
	PUT(HDRP(bp), PACK(size, 0));         /* Free block header */
	PUT(FTRP(bp), PACK(size, 0));         /* Free block footer */
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

	/* Coalesce if the previous block was free */
	return coalesce(bp);
}

/*
 * coalesce - Boundary tag coalescing. 
 * Return ptr to coalesced block, also update the freelist 
 */
static void *coalesce(void *bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
	size_t size = GET_SIZE(HDRP(bp));
	char *prev_bp, *next_bp;

	dbg_printf("Coalesce has started\n"); 
	/* 
	 * Case 1: both the previous and next block are allocated
	 */
	if (prev_alloc && next_alloc) {     
		dbg_printf("Case 1\n");
		return bp;
	}

	/* 
	 * Case 2: only the previous block is allocated 
	 */
	else if (prev_alloc && !next_alloc) { 
		dbg_printf("Case 2\n");
		next_bp = NEXT_BLKP(bp); 
		/* delete the next free block*/
		seg_delete(next_bp); 
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		PUT(FTRP(bp), PACK(size, 0));
	}

	/* 
	 * Case 3: only the next block is allocated 
	 */
	else if (!prev_alloc && next_alloc) {
		dbg_printf("Case 3\n");
		size += GET_SIZE(HDRP(PREV_BLKP(bp)));
		prev_bp = PREV_BLKP(bp);
		/* delete the previous block*/
		seg_delete(prev_bp); 
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	}

	/* 
	 * Case 4: coalese with both the previous and next blocks 
	 */
	else {            
		dbg_printf("Case 4\n");
		/* delete both the previous and next free blocks */
		prev_bp = PREV_BLKP(bp);
		next_bp = NEXT_BLKP(bp);
		seg_delete(prev_bp);
		seg_delete(next_bp); 

		/* update the current block*/
		size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
			GET_SIZE(FTRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp); 
	}
	return bp;
}

/*
 * place - Place block of asize bytes at start of free block bp
 *         and split if remainder would be at least minimum block size
 */
static void place(void *bp, size_t asize)
{
	size_t csize = GET_SIZE(HDRP(bp));

	/*
	 * If the remaining block size is large enough, then
	 * split it out 
	 */
	if ((csize - asize) >= (BLK_MIN_SZE)) {
		dbg_printf("Split the free block at %zu\n", (size_t)bp);
		PUT(HDRP(bp), PACK(asize, 1));
		PUT(FTRP(bp), PACK(asize, 1));
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK(csize - asize, 0));
		PUT(FTRP(bp), PACK(csize - asize, 0));
		seg_insert(bp, csize - asize); 
	}
	else {
		dbg_printf("Allocate the free block at %zu\n", (size_t)bp);
		PUT(HDRP(bp), PACK(csize, 1));
		PUT(FTRP(bp), PACK(csize, 1));
	}
}

/*
 * find_fit - Find a fit for a block with asize bytes
 * for segragated list, only first or best fit works 
*/
static void *find_fit(size_t asize)
{
	/* First-fit search */
	void *bp;
	void *bucket_root;	/* root of this bucket*/
	void *bucket_start; /* the address of the first block*/
	size_t bnum;		/* index of the block*/
	
	dbg_printf("start finding a fit\n");
	for (bnum = get_bucket_num(asize); bnum < BucketSize; bnum++) 
	{
		dbg_printf("try bucket %zu now\n", bnum);
		bucket_root = get_bucket_root(bnum);
		bucket_start = int2pt(GET(bucket_root));
		for (bp = bucket_start; bp != NULL; bp = next_fbk_pt(bp))
		{
			dbg_printf("searching in bucket %zu now\n", bnum);
			dbg_printf("the current block size is %ud now\n", GET_SIZE(HDRP(bp)));
			if (GET_SIZE(HDRP(bp)) >= asize)
			{
				/* find out a suitable fit for the */
				return bp; 
			}
		}
	}
	dbg_printf("No suitable block currently\n");
	return NULL; /* No fit */
}

/*
  self-defined helper function list 
*/
/*
 * pt2int: map a pointer to the offset value with respect to heap_listp
 */
static inline unsigned int pt2int(void *bp)
{
	if (bp == NULL) return 0;
	return (unsigned int)((size_t)bp - (size_t)heap_listp);
}

/*
 * int2pt: map the offset value with respect to heap_listp to a pointer
 * the inverse of pt2int
 */
static inline void *int2pt(unsigned int val)
{
	if (val == 0) return NULL;
	/* since for 64 bit system, size_t is 8 byte */
	return (void *)((unsigned long)val + (unsigned long)heap_listp);
}

/*
 * prev_fbk_pt: return pointer to the previous block
 */
static inline void* prev_fbk_pt(void *bp) 
{
	unsigned int prev_bp;
	prev_bp = GET(PREV_FKPT(bp));
	/* 
	 * dbg_printf("The previous pointer is %ud\n", prev_bp);
	 */
	return int2pt(prev_bp);
}

/*
 * next_fbk_pt: return pointer to the next block
 */

static inline void* next_fbk_pt(void *bp)
{
	unsigned int next_bp;
	next_bp = GET(NEXT_FKPT(bp));
	/*
	* dbg_printf("The next pointer is %ud\n", next_bp);
	*/
	return int2pt(next_bp);
}

/*
 * get_bucket_size: compute the index of the current free block in the 
 * bucket list 
 * needs to return an integer val between 0 ~ BucketSize
 */
static inline size_t get_bucket_num(size_t asize) 
{
	if (asize < (1 << 3)) 
		return 0;
	if (asize >= (1 << 3) && asize < (1 << 6)) 
		return 1;
	if (asize >= (1 << 6) && asize < (1 << 9)) 
		return 2;
	if (asize >= (1 << 8) && asize < (1 << 10))
		return 3;
	if (asize >= (1 << 10) && asize < (1 << 12))
		return 4;
	if (asize >= (1 << 12) && asize < (1 << 14))
		return 5;
	return 6;
}

static inline void *get_bucket_root(size_t bnum)
{
	return (void *)((char *)root_pt + bnum * WSIZE);
}

/*
* seg_insert: insert a free block into the list according to its size
*/
static inline void seg_insert(void *bp, size_t asize)
{
	size_t bnum = get_bucket_num(asize);
	void *bucket_root;	/* root of this bucket*/
	void *bucket_start; /* the address of the first block*/

	/* get the address of the first block*/
	bucket_root = get_bucket_root(bnum);
	bucket_start = int2pt(GET(bucket_root));

	if (bucket_start == NULL)
	{
		/*
		 * if this bucket is empty, update its root at the heap top 
		 */
		dbg_printf("Insert the first node in bucket %zu\n", bnum);
		PUT(PREV_FKPT(bp), pt2int(bucket_root));
		PUT(NEXT_FKPT(bp), (unsigned int)0);
		PUT(bucket_root, pt2int(bp));
	}
	else
	{
		/*
		* otherwise, set the inserted block as the new start and
		* relinke the list
		*/
		dbg_printf("Add new node into the bucket %zu\n", bnum);
		PUT(NEXT_FKPT(bp), pt2int(bucket_start));
		PUT(PREV_FKPT(bp), pt2int(bucket_root));
		PUT(PREV_FKPT(bucket_start), pt2int(bp));
		PUT(bucket_root, pt2int(bp));
	}
}

/*
* seg_delete: delete a free block from the list
*/
static inline void seg_delete(void *bp)
{
	void *prev_bp = prev_fbk_pt(bp);
	void *next_bp = next_fbk_pt(bp);

#ifdef DEBUG
	size_t bnum = get_bucket_num(GET_SIZE(HDRP(bp)));
#endif /* for debugging */

	if (next_bp == NULL)
	{
		/*
		 * if the block to be deleted is the last one
		 * in bucket, update the root 
		 */
		dbg_printf("Delete the last node in bucket %zu\n", bnum);
		dbg_printf("The root is given by %zu\n", bnum);
		PUT(NEXT_FKPT(prev_bp), 0); 
	}
	else
	{
		/*
		 * otherwise, relink the list
		 */
		dbg_printf("Delete a node in bucket %zu\n", bnum);
		PUT(NEXT_FKPT(prev_bp), pt2int(next_bp));
		PUT(PREV_FKPT(next_bp), pt2int(prev_bp));
	}
}