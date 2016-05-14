/*
 *  File : cache.h
 *
 *  Author : Ishant Dawer(idawer@andrew.cmu.edu)
 *
 *  Defining the structs and function types required for implementing 
 *  the cache
 */

/* Defining structure for each entry in the cache 
 *
 * Fields : 
 *
 * 1. URL (String)
 * 2. Web Response content (Pointer )
 * 3. Size of the object
 * 4. LRU count
 *
 */
#include "csapp.h"
typedef struct cacheLine cacheLine;
struct cacheLine 
{
        char * url;
        void * content;
        size_t size;
        unsigned int count;
        struct cacheLine * next;
};



//#define DEBUG 0

/* Wrapper for printf*/
#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) ((void) 0)
#endif


sem_t mutex; //Defining the mutex for Write & Read lock

/* Declaring header of the linkedlist */
/* 
 * addIntoCache : Web-object is cached into cache in the form of linked-list
 * node (led by head) with key as URL and value as Object Response from URL
 *
 * Input : URL string, content memory location, size of the content
 *
 * Output : Null
 */

void addIntoCache(char * url,void * content,size_t size);

/* 
 * readFromCache : Reading from the cache when URL given in the 
 * input is matched with one of the nodes 
 */

cacheLine * readFromCache(char * url);

/* 
 * evcitFromCache : Evict from the cache which is least recently used 
 */


void evictFromCache(void);

/*
 * FreeCache : Signal handler for SIGINT 
 * It exits the proxy process and frees the memory 
 */

void FreeCache(int signum);


/* 
 * verifyCacheSize : Testing function to check if total cache size after 
 * adding all the nodes is equal to TotalCacheSize maintained in global
 * counter 
 */

int verifyCacheSize();


