/*
 * Proxy Server (proxy.c)
 * 
 * Author : Ishant Dawer (idawer@andrew.cmu.edu)
 *
 * Description :  This implements HTTP proxy where it will accept incoming
 *  requests from browser  and forward them to Web-servers. All responses from
 *  the server will be forwarded to browser.
 *
 *  Proxy server is concurrent as it can parse multiple requests from server 
 *  and process them as described above
 *
 *  It also caches the web objects if web object size is less than 100KB and 
 *  implements the cache size of 1MB
 *
 *
 */

#include "csapp.h"

/* Header file for cache where Mutex and cache functions such as addIntoCache
 * , readFromCache, testing functions such as verifyCache is declared*/

#include "cache.h"




/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including these long lines in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *accept_hdr = "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
static const char *accept_encoding_hdr = "Accept-Encoding: gzip, deflate\r\n";
static const char *Connection_hdr = "Connection: close\r\n";
static const char *proxy_conn_hdr = "Proxy-Connection: close\r\n";

/*
 * doit : This function handles parsing of Client request from the browser and 
 * does the following actions 
 *
 * 1. Parses the URL and extracts port (or set to default 80), hostname, URI
 * 2. Generate Request headers (values shown above) and copies remaining 
 *    different headers from the request with the same key-value
 * 3. Establishes a connection to the web-server and forwards the request to 
 *    the browser.
 * 4. If the object size is less than 100 KB, it caches the objects
 *
 * Input : Connection Descriptor
 *
 * Output : Null
 */

void doit(int fd);

/*
 * read_requesthdrs : This function helps in getting and parsing all the 
 * request headers from the Client browser. It checks for the headers mentioned
 * in Line 34-39 and replaces them with the values mentioned in same lines
 * It attaches new headers from the Client request to the final request it will
 * send
 *
 * Input : rp (RIO reader from Client, Data-output data, input -filename, input 
 * - hostname)
 *
 * Output : Null
 */



void read_requesthdrs(rio_t *rp,char * Data,char * filename,char * hostname);

/*
 * clienterror : It handles the response back to client in case of any failures
 * (Bad URL, handles errors like 400s, 500s or page not found)
 *
 * Input : (Fd- connection descriptor, cause - cause string, errnum - error code
 * shortmsg-- HTTP shortmsg, longmsg - HTTP detailed message
 */



void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);


/*
 *
 * parseHostNamePort : This parses filename , hostname and port from the URL
 *
 * Input : URI (link)
 *
 * Output : filename, hostname, port (or default 80)
 */


void parseHostNamePort(char * uri, char * filename, char * hostname,
                char* port);

/*
 * clientThread : Handling different HTTP requests and threads detach 
 * doit function is called
 *
 *
 * Input : pointer to Client descriptor
 */


void * clientThread(void * arg);

int main(int argc, char **argv) 
{
    int listenfd, *connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    /* Check command line args */
    if (argc != 2) {
	//fprintf(stderr, "usage: %s <port>\n", argv[0]);
    	exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
/* Initializing  mutex (Reader/Writer) to 1 */
    Sem_init(&mutex,0,1); 

/* 
 * Signal handlers for handling SIGPIPE (ignoring it), 
 * Signal handler (SIGINT) Exiting the proxy after clearing
 * the heap memory
 */


    Signal(SIGPIPE,SIG_IGN);
    Signal(SIGINT,FreeCache);

    while (1) {
            clientlen = sizeof(clientaddr);
            connfd = Malloc(sizeof(int));
            
            *connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
                            port, MAXLINE, 0);
            printf("Accepted connection from (%s, %s)\n", hostname, port);
/* Creating threads for each request */            
            Pthread_create(&tid,NULL,clientThread,connfd);

    //        verifyCacheSize();
    }
}

/*
 * clientThread : Handling different HTTP requests and threads detach 
 * doit function is called
 *
 *
 * Input : pointer to Client descriptor
 */

void * clientThread(void * arg)
{
        printf("Thread created is %lu\n",pthread_self());
        int connfd = *(int*)arg;
        Pthread_detach(pthread_self());
        Free(arg);
        doit(connfd);                                   
	    Close(connfd);                                 
        printf("Thread destroyed is %lu\n",pthread_self());
        return NULL;
}

/*
 * doit : This function handles parsing of Client request from the browser and 
 * does the following actions 
 *
 * 1. Parses the URL and extracts port (or set to default 80), hostname, URI
 * 2. Generate Request headers (values shown above) and copies remaining 
 *    different headers from the request with the same key-value
 * 3. Establishes a connection to the web-server and forwards the request to 
 *    the browser.
 * 4. If the object size is less than 100 KB, it caches the objects
 *
 * Input : Connection Descriptor
 *
 * Output : Null
 */

void doit(int fd) 
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE],hostname[MAXLINE],port[MAXLINE];
    char requestData[MAXLINE];
    int serverConnFd;
    rio_t rio;
    rio_t rio_server;
    char * url = (char * ) Malloc(MAXLINE);
    cacheLine * line;
    
    /* Defining CacheBuffer */
    void * cacheBuffer = Malloc(MAX_OBJECT_SIZE);
    
    /* Retaining buffer pointer for Freeing later */
    void * tempCache=cacheBuffer;

    /* Reading from connection into this buffer */
    void * buff = Malloc(MAXLINE);
    int count1= 0;
/* Setting Cache buffer to zero */
    memset(cacheBuffer,0,MAX_OBJECT_SIZE);

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE)) 
        return;


    /* Extracting HTTP Method GET/POST, URL, HTTP version*/
    sscanf(buf, "%s %s %s", method, uri, version);  

    /* Copying URI to another variable URL used for key in cache*/
    strcpy(url,uri);

    /* Checking if method is GET otherwise don't proceed further */

    if (strcasecmp(method, "GET")) {              
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }                                            
   

    /* 
     * Checking if url is in cache, return the object otherwise
     * fwd a request to web-server
     * */

    if((line=readFromCache(url)) != NULL) 
    {
            void * content = line->content;
            size_t size = line->size;
            PRINTF("Found in the cache\n");
            rio_writen(fd,content,size);
            Free(url); 
            return;
    } 

    /* Parsing Hostname, filename and port */

    parseHostNamePort(uri,filename,hostname,port); 


    read_requesthdrs(&rio,requestData,filename,hostname);  

    /* connecting to web-server */
    serverConnFd = open_clientfd(hostname,port);

    /* Initializing Rio reader for server descriptor*/
    Rio_readinitb(&rio_server, serverConnFd);

    /* Write the HTTP request to the web-server*/
    rio_writen(serverConnFd,requestData,strlen(requestData));

   /* Number of bytes read from the server */ 
    ssize_t count=0;

    while((count = rio_readnb(&rio_server,buff,MAXLINE)) > 0)
    {
            /* Count1- counter for the number of bytes for single
             * HTTP response 
             */

            count1 += count;
            if (count1 < MAX_OBJECT_SIZE)
            {
             /* Copying to the buffer for caching later */
                    memcpy(tempCache,buff,count);
                    tempCache = tempCache + count;
            } 
            rio_writen(fd,buff,count); 
            PRINTF(" count is %d\n",count1);
    } 

    /* Writing to the cache if object size is less than 100KB*/
    if (count1 < MAX_OBJECT_SIZE)
    {
            PRINTF("Adding to the cache %s and count %d\n",url,count1);
            addIntoCache(url,cacheBuffer,count1);
    }

    /* Free the heap memory and Closing the server descriptor*/
    Free(cacheBuffer);
    Free(url);
    Free(buff);
    Close(serverConnFd);


    return;
}


/*
 * read_requesthdrs : This function helps in getting and parsing all the 
 * request headers from the Client browser. It checks for the headers mentioned
 * in Line 34-39 and replaces them with the values mentioned in same lines
 * It attaches new headers from the Client request to the final request it will
 * send
 *
 * Input : rp (RIO reader from Client, Data-output data, input -filename, input 
 * - hostname)
 *
 * Output : Null
 */

void read_requesthdrs(rio_t *rp,char * requestData,char * filename,
                char * hostname) 
{
    PRINTF("In the request HDRs\n");
    char buf[MAXLINE];
    Rio_readlineb(rp, buf, MAXLINE);

    sprintf(requestData,"GET %s HTTP/1.0\r\n",filename);
    sprintf(requestData,"%s%s",requestData,user_agent_hdr);
    sprintf(requestData,"%s%s",requestData,accept_hdr);
    sprintf(requestData,"%s%s",requestData,accept_encoding_hdr);
    sprintf(requestData,"%s%s",requestData,proxy_conn_hdr);
    sprintf(requestData,"%s%s",requestData,Connection_hdr);
    while(strcmp(buf, "\r\n")) {      

           if(!((strstr(buf,"User-Agent") > 0) || (strstr(buf,"Accept") > 0) ||
                                  (strstr(buf,"Accept-Encoding") > 0) ||
                                 (strstr(buf,"Proxy-Connection") > 0) ||
                                (strstr(buf,"Connection") > 0)))
           {
                sprintf(requestData,"%s%s",requestData,buf);
           }

        
    	Rio_readlineb(rp, buf, MAXLINE);
    }
    if(!(strstr(requestData,"Host") > 0)) 
    {
        sprintf(requestData,"%sHost: %s\r\n",requestData,hostname);
    }
    sprintf(requestData,"%s\r\n",requestData);
    PRINTF("Ending the request HDRs\n");
    return;
}

/*
 *
 * parseHostNamePort : This parses filename , hostname and port from the URL
 *
 * Input : URI (link)
 *
 * Output : filename, hostname, port (or default 80)
 */


void parseHostNamePort(char * uri, char * filename, char * hostname, char* port)
{
        char * ptr;
        char str2[MAXLINE];
        if (strstr(uri,"http") > 0) 
        {
                strcpy(str2,uri+7);
                uri = str2;
        }
        if((ptr = strstr(uri,"/")) > 0 ) 
        {
           strcpy(filename,ptr);
           *ptr = '\0';
        } else { 
                strcpy(filename,"/");
        }
        if((ptr = strstr(uri,":")) > 0 ) 
        {
           strcpy(port,ptr+1);
           *ptr='\0';
        } else { 
               strcpy(port,"80"); 
        }    
           strcpy(hostname,uri);
}

/*
 * clienterror : It handles the response back to client in case of any failures
 * (Bad URL, handles errors like 400s, 500s or page not found)
 *
 * Input : (Fd- connection descriptor, cause - cause string, errnum - error code
 * shortmsg-- HTTP shortmsg, longmsg - HTTP detailed message
 */


void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
/* $end clienterror */
