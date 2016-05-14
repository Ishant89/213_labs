#include<stdio.h>
#include<stdlib.h>
//#define NEXTFREE(bp)  (*(char **)(bp))
//#define PREVFREE(bp)  (*((char **)(bp) + 1))

char * heap_listp = (char*) 0x800000010 ;

#define NEXTFREE(bp)  ((!(*(unsigned int *)(bp)))? 0 :((char*)(heap_listp) + *(unsigned int *)(bp)))
#define PREVFREE(bp)  ((!(*((unsigned int *)(bp) + 1))) ? 0 :((char*)(heap_listp) + *((unsigned int *)(bp)+1)))


/* Given ptr bp, compute the address of next & free block's header and footer */
/*#define NEXTFREEHDR(bp)   HDRP(NEXTFREE(bp))
#define PREVFREEHDR(bp)   HDRP(PREVFREE(bp))
#define NEXTFREEFTR(bp)   FTRP(NEXTFREE(bp))
#define PREVFREEFTR(bp)   FTRP(PREVFREE(bp))
*/
/* Givenn ptr bp, update the nextfree block value and prev free block value */
#define PUTPTR(p, val)  (*(char **)(p) = (val))
//#define WRITESUCCESSOR(bp,val) (*(char**)(bp) = (val))
//#define WRITEPREDESSOR(bp,val) (*(((char**)(bp) + 1)) = (val))
   // char *free1 = (char * ) malloc(sizeof(char));
    //char * prevfree = (char * ) malloc(sizeof(char));
#define WRITESUCCESSOR(bp,val) ((val) == 0) ? (*(unsigned int *)(bp) = 0):(*(unsigned int *)(bp) = ((char*)(val)- (char*)(heap_listp)))
#define WRITEPREDESSOR(bp,val) ((val) == 0) ? ((*((unsigned int *)(bp) + 1)) = 0):(*((unsigned int *)(bp) + 1) = ((char*)(val) - (char*)(heap_listp)))

/* void movFreeBlock_top(void * bp,char * start)
{
            char * temp = start;
                start = (char *) bp;
                    WRITESUCCESSOR(bp,temp);
                        WRITEPREDESSOR(bp,0);
                            if (temp!=0) {
                                                 WRITEPREDESSOR(NEXTFREE(bp),bp);
                                                     }
}
*/
int main() { 
    char * bp = (char * ) malloc(sizeof(char));
    WRITESUCCESSOR(bp,0x800000016);
    WRITEPREDESSOR(bp,0x800000012);
    char * start = 0;

    /*printf("start is %p and bp is %p \n",start,bp);
    printf("nextfree bfr is %p and bp is %p \n",NEXTFREE(bp),bp);
    printf("prevfree bfr is %p and bp is %p \n",PREVFREE(bp),bp);
    movFreeBlock_top(bp,start);
    printf("start is %p and bp is %p \n",start,bp);
    printf("nextfree after is %p and bp is %p \n",NEXTFREE(bp),bp);
    printf("prevfree after is %p and bp is %p \n",PREVFREE(bp),bp);
    //printf("prevfree of next elem after is %p and bp is %p \n",PREVFREE(NEXTFREE(bp)),bp);
*/
    printf("Write Successor is %p and bp is %p \n",NEXTFREE(bp),bp);
    printf("Write Predessor is %p and bp is %p \n",PREVFREE(bp),bp);

    WRITESUCCESSOR(bp,0);
    WRITEPREDESSOR(bp,0);
    printf("Write Successor is %p and bp is %p \n",NEXTFREE(bp),bp);
    printf("Write Predessor is %p and bp is %p \n",PREVFREE(bp),bp);
   // free(prevfree);
   free(bp);

}

