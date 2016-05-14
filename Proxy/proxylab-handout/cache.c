/*
 * File : cache.c
 *
 * Author : Ishant Dawer (idawer@andrew.cmu.edu)
 *
 * Cache.c : Implementing caching of web pages such that each web page that is 
 * cached should not exceed more than 100KB and total size of the cache is 1 MB.
 *
 */
 

#include "cache.h"

/* Maximum Cache Size */
#define MAX_CACHE_SIZE 1049000

/* Global variables*/

size_t totalCacheUsed = 0 ;//After every addition into cache, this gets updated
unsigned int globalTimeStamp = 0;// Global counter for LRU, this gets updated
unsigned int readCount=0;//Counter to record number of Read Threads



cacheLine * head = NULL; //pointer to the head of the linked list

/* 
 * addIntoCache : Web-object is cached into cache in the form of linked-list
 * node (led by head) with key as URL and value as Object Response from URL
 *
 * Input : URL string, content memory location, size of the content
 *
 * Output : Null
 */


void addIntoCache(char * url,void * content,size_t ContentSize1)
{
/* Applying Writer Lock so that multiple writes are serialized */
        P(&mutex);
        size_t ContentSize = ContentSize1,urlLength = strlen(url)+1;
        cacheLine * temp;

        PRINTF("In the addIntoCache\n");
/* Adding the new node to the list */
        cacheLine * entry = (cacheLine*) Malloc(sizeof(cacheLine));

/* Adding URL */
        entry->url = (char *) Malloc(urlLength);
/* Adding Content */
        entry->content = (char *) Malloc(ContentSize);

/* Adding Size */        
        entry->size = ContentSize;
/* Adding global timestamp for LRU */
        entry->count = globalTimeStamp;

        globalTimeStamp++;
        PRINTF("GlobalTimeStamp is %d\n",globalTimeStamp);
        PRINTF("Total cache used before adding %ld\n",totalCacheUsed);
        
        while((totalCacheUsed +ContentSize) > MAX_CACHE_SIZE) 
        {
/* If not enough cache memory, evict from Cache */
                evictFromCache();
        } 
        

        memcpy(entry->url,url,urlLength);
        memcpy(entry->content,content,ContentSize);
/* Incrimenting the total cache used */
        totalCacheUsed += ContentSize;
        PRINTF("Total cache used after adding %ld\n",totalCacheUsed);
/* Moving node to the top of head */
        temp = head;
        head = entry;
        entry->next = temp;
/* Releasing the mutex */ 
        V(&mutex);
        
        PRINTF("Exiting the addIntoCache\n");
}


/* 
 * evcitFromCache : Evict from the cache which is least recently used 
 */

void evictFromCache() 
{
        PRINTF("In the evictFromCache Cache\n");
        cacheLine * iterator,*temp;
        unsigned int count1;
/* Minimum count */
        unsigned int minCount = 0,i=0 ;
        PRINTF("Selecting cacheline to be evicted\n");
/* Finding the minimum count which is a globalstamp */
        for (iterator=head;iterator != NULL;iterator = iterator->next)
        {
                count1 = iterator->count;
                if (i==0) 
                {
                        minCount = count1;
                        continue;
                }

                if (count1 < minCount)
                {
                        minCount = count1;


                }
                i++;

        }
        PRINTF("the minimum count is %d\n",minCount);
/* Removing the node */
        if(head-> count != minCount) { 

                for (iterator=head;iterator->next != NULL;iterator = 
                                iterator->next)
                {
                        if(iterator->next->count == minCount)
                        {
                                temp = iterator-> next;
                                iterator->next = iterator->next->next;
                                break;
                        }
                }
        } else 
        {
                temp = head;
                head = head->next;

        } 
/* Decrementing the TotalCache after removing the node */
        totalCacheUsed = totalCacheUsed - temp->size;
/* Freeing the node */
        Free(temp->url);
        Free(temp->content);
        Free(temp);
        
        PRINTF("Exiting the evictFromCache Cache\n");
}


/* 
 * readFromCache : Reading from the cache when URL given in the 
 * input is matched with one of the nodes 
 */

cacheLine * readFromCache(char * url)
{
        cacheLine * iterator;
        PRINTF("In the read Cache\n");
        for (iterator=head;iterator != NULL;iterator = iterator->next)
        {
                if(strcmp(iterator->url,url) == 0)
                {
                        PRINTF("URLs match %s\n",url);
/* Applying mutex on global timestamp */
                        P(&mutex);
                        iterator->count = globalTimeStamp;
                        globalTimeStamp++;
/* Releasing the mutex */
                        V(&mutex);
                        PRINTF("GlobalTimeStamp is %d\n",globalTimeStamp);
                        PRINTF("Out from  the read Cache\n");
/* Returning the iterator */
                        return iterator;
                }
        }
        PRINTF("Out from  the read Cache\n");
        return NULL;
}

/* 
 * verifyCacheSize : Testing function to check if total cache size after 
 * adding all the nodes is equal to TotalCacheSize maintained in global
 * counter 
 */


int verifyCacheSize() 
{
        cacheLine * iterator;
        unsigned int memory=0;
        for (iterator=head;iterator!=NULL;iterator=iterator->next)
        {
                PRINTF("Tags are %s\n",iterator->url);
                memory+=iterator->size;
        }


        if(memory==totalCacheUsed)
        {
                printf("memory is equal to totalCache\n");
                return 1 ;
        } 

        printf("memory is not equal to totalCache\n");
        return 0;
}


/*
 * FreeCache : Signal handler for SIGINT 
 * It exits the proxy process and frees the memory 
 */


void FreeCache(int signum) 
{
        cacheLine * iterator;
        printf("Freeing the memory \n");
        for (iterator=head;iterator!=NULL;iterator=iterator->next)
        {
                Free(iterator->url);
                Free(iterator->content);
                Free(iterator);
        }
        exit(0);
}
