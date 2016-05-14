/* 
 * tsh - A tiny shell program with job control
 * 
 * Author : Ishant Dawer (idawer.andrew.cmu.edu)
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>


//#define DEBUG 0

/*
 * PRINTF : Wrapper function for printf required for Debugs 
 * prints only if DEBUG flag is enabled
 */
#ifdef DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) ((void) 0)
#endif


/*
 * Debug flag
 */


/* Misc manifest constants */
#define MAXLINE    1024   /* max line size */
#define MAXARGS     128   /* max args on a command line */
#define MAXJOBS      16   /* max jobs at any point in time */
#define MAXJID    1<<16   /* max job ID */

/* Job states */
#define UNDEF         0   /* undefined */
#define FG            1   /* running in foreground */
#define BG            2   /* running in background */
#define ST            3   /* stopped */

/* 
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/* Parsing states */
#define ST_NORMAL   0x0   /* next token is an argument */
#define ST_INFILE   0x1   /* next token is the input file */
#define ST_OUTFILE  0x2   /* next token is the output file */


/*Permissions for file */

#define MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#define UMASK S_IWGRP|S_IWOTH

/* Global variables */
extern char **environ;      /* defined in libc */
char prompt[] = "tsh> ";    /* command line prompt (DO NOT CHANGE) */
int verbose = 0;            /* if true, print additional output */
int nextjid = 1;            /* next job ID to allocate */
char sbuf[MAXLINE];         /* for composing sprintf messages */

struct job_t {              /* The job struct */
    pid_t pid;              /* job PID */
    int jid;                /* job ID [1, 2, ...] */
    int state;              /* UNDEF, BG, FG, or ST */
    char cmdline[MAXLINE];  /* command line */
};
struct job_t job_list[MAXJOBS]; /* The job list */

struct cmdline_tokens {
    int argc;               /* Number of arguments */
    char *argv[MAXARGS];    /* The arguments list */
    char *infile;           /* The input file */
    char *outfile;          /* The output file */
    enum builtins_t {       /* Indicates if argv[0] is a builtin command */
        BUILTIN_NONE,
        BUILTIN_QUIT,
        BUILTIN_JOBS,
        BUILTIN_BG,
        BUILTIN_FG} builtins;
};

/* End global variables */


/* Function prototypes */
void eval(char *cmdline);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

/* Here are helper routines that we've provided for you */
int parseline(const char *cmdline, struct cmdline_tokens *tok); 
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void initjobs(struct job_t *job_list);
int maxjid(struct job_t *job_list); 
int addjob(struct job_t *job_list, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *job_list, pid_t pid); 
pid_t fgpid(struct job_t *job_list);
struct job_t *getjobpid(struct job_t *job_list, pid_t pid);
struct job_t *getjobjid(struct job_t *job_list, int jid); 
int pid2jid(pid_t pid); 
void listjobs(struct job_t *job_list, int output_fd);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

/*Helper Functions written by idawer*/

int builtin_command(struct cmdline_tokens * ) ; 
void background(char * str);
void foreground(char * str);

/*Wrappers for important functions*/
/*********************************************
 *  * Wrappers for Unix process control functions
 *   ********************************************/

/* $begin forkwrapper */
pid_t Fork(void) 
{
            pid_t pid;

                if ((pid = fork()) < 0)
                            unix_error("Fork error");
                    return pid;
}
/* $end forkwrapper */

void Execve(const char *filename, char *const argv[], char *const envp[]) 
{
            if (execve(filename, argv, envp) < 0)
                        unix_error("Execve error");
}

/* $begin wait */
pid_t Wait(int *status) 
{
            pid_t pid;

                if ((pid  = wait(status)) < 0)
                            unix_error("Wait error");
                    return pid;
}
/* $end wait */

pid_t Waitpid(pid_t pid, int *iptr, int options) 
{
            pid_t retpid;

                if ((retpid  = waitpid(pid, iptr, options)) < 0) 
                            unix_error("Waitpid error");
                    return(retpid);
}

/* $begin kill */
void Kill(pid_t pid, int signum) 
{
            int rc;

                if ((rc = kill(pid, signum)) < 0)
                            unix_error("Kill error");
}
/* $end kill */

void Pause() 
{
            (void)pause();
                return;
}

unsigned int Sleep(unsigned int secs) 
{
            unsigned int rc;

                if ((rc = sleep(secs)) < 0)
                            unix_error("Sleep error");
                    return rc;
}

unsigned int Alarm(unsigned int seconds) {
            return alarm(seconds);
}
 
void Setpgid(pid_t pid, pid_t pgid) {
            int rc;

                if ((rc = setpgid(pid, pgid)) < 0)
                            unix_error("Setpgid error");
                    return;
}

pid_t Getpgrp(void) {
            return getpgrp();
}

/************************************
 *  * Wrappers for Unix signal functions 
 *   ***********************************/


void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
            if (sigprocmask(how, set, oldset) < 0)
                        unix_error("Sigprocmask error");
                return;
}

void Sigemptyset(sigset_t *set)
{
            if (sigemptyset(set) < 0)
                        unix_error("Sigemptyset error");
                return;
}

void Sigfillset(sigset_t *set)
{ 
            if (sigfillset(set) < 0)
                        unix_error("Sigfillset error");
                return;
}

void Sigaddset(sigset_t *set, int signum)
{
            if (sigaddset(set, signum) < 0)
                        unix_error("Sigaddset error");
                return;
}

void Sigdelset(sigset_t *set, int signum)
{
            if (sigdelset(set, signum) < 0)
                        unix_error("Sigdelset error");
                return;
}

int Sigismember(const sigset_t *set, int signum)
{
            int rc;
                if ((rc = sigismember(set, signum)) < 0)
                            unix_error("Sigismember error");
                    return rc;
}

/********************************
 *  * Wrappers for Unix I/O routines
 *   ********************************/

int Open(const char *pathname, int flags, mode_t mode) 
{
            int rc;

                if ((rc = open(pathname, flags, mode))  < 0)
                            unix_error("Open error");
                    return rc;
}

ssize_t Read(int fd, void *buf, size_t count) 
{
            ssize_t rc;

                if ((rc = read(fd, buf, count)) < 0) 
                            unix_error("Read error");
                    return rc;
}

ssize_t Write(int fd, const void *buf, size_t count) 
{
            ssize_t rc;

                if ((rc = write(fd, buf, count)) < 0)
                            unix_error("Write error");
                    return rc;
}

off_t Lseek(int fildes, off_t offset, int whence) 
{
            off_t rc;

                if ((rc = lseek(fildes, offset, whence)) < 0)
                            unix_error("Lseek error");
                    return rc;
}

void Close(int fd) 
{
            int rc;

                if ((rc = close(fd)) < 0)
                            unix_error("Close error");
}

int Select(int  n, fd_set *readfds, fd_set *writefds,
                       fd_set *exceptfds, struct timeval *timeout) 
{
            int rc;

        if ((rc = select(n, readfds, writefds, exceptfds, timeout)) < 0)
                    unix_error("Select error");
            return rc;
}

int Dup2(int fd1, int fd2) 
{
            int rc;

        if ((rc = dup2(fd1, fd2)) < 0)
                    unix_error("Dup2 error");
            return rc;
}



/*
 * main - The shell's main routine 
 */
int 
main(int argc, char **argv) 
{
    char c;
    char cmdline[MAXLINE];    /* cmdline for fgets */
    int emit_prompt = 1; /* emit prompt (default) */

    /* Redirect stderr to stdout (so that driver will get all output
     * on the pipe connected to stdout) */
    dup2(1, 2);

    /* Parse the command line */
    while ((c = getopt(argc, argv, "hvp")) != EOF) {
        switch (c) {
        case 'h':             /* print help message */
            usage();
            break;
        case 'v':             /* emit additional diagnostic info */
            verbose = 1;
            break;
        case 'p':             /* don't print a prompt */
            emit_prompt = 0;  /* handy for automatic testing */
            break;
        default:
            usage();
        }
    }

    /* Install the signal handlers */

    /* These are the ones you will need to implement */
    Signal(SIGINT,  sigint_handler);   /* ctrl-c */
    Signal(SIGTSTP, sigtstp_handler);  /* ctrl-z */
    Signal(SIGCHLD, sigchld_handler);  /* Terminated or stopped child */
    Signal(SIGTTIN, SIG_IGN);
    Signal(SIGTTOU, SIG_IGN);

    /* This one provides a clean way to kill the shell */
    Signal(SIGQUIT, sigquit_handler); 

    /* Initialize the job list */
    initjobs(job_list);


    /* Execute the shell's read/eval loop */
    while (1) {

        if (emit_prompt) {
            printf("%s", prompt);
            fflush(stdout);
        }
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
            app_error("fgets error");
        if (feof(stdin)) { 
            /* End of file (ctrl-d) */
            printf ("\n");
            fflush(stdout);
            fflush(stderr);
            exit(0);
        }
        
        /* Remove the trailing newline */
        cmdline[strlen(cmdline)-1] = '\0';
        
        /* Evaluate the command line */
        eval(cmdline);
        
        fflush(stdout);
        fflush(stdout);
    } 
    
    exit(0); /* control never reaches here */
}

/* 
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requested a built-in command (quit, jobs, bg or fg)
 * then execute it immediately. Otherwise, fork a child process and
 * run the job in the context of the child. If the job is running in
 * the foreground, wait for it to terminate and then return.  Note:
 * each child process must have a unique process group ID so that our
 * background children don't receive SIGINT (SIGTSTP) from the kernel
 * when we type ctrl-c (ctrl-z) at the keyboard.  
 */
void 
eval(char *cmdline) 
{
    int bg,state;   /* should the job run in bg or fg? */
    struct cmdline_tokens tok;
    pid_t pid ; /*Child process (BG or Fg) ID*/

   /* Parse command line */
    bg = parseline(cmdline, &tok); 
  

    if (bg == -1) /* parsing error */
    {
        return;
    }
    if (tok.argv[0] == NULL) /* ignore empty lines */
    {
        return;
    } 
    
    /*Blocking all the signals: SIGTSTP,SIGINT,SIGCHLD*/
    

    int Signals[] = {SIGTSTP,SIGINT,SIGCHLD};

    /*Declaring signal sets */
    sigset_t setOld,setNew;

    /* Empty the sets */
    Sigemptyset(&setOld);
    Sigemptyset(&setNew);
   
   /*Block other signals using setOld*/
    

    /*Adding  3 signals to the sets*/

    int i;
    for(i = 0 ; i < 3; i++) 
    { 
            Sigaddset(&setNew,Signals[i]);
    }
    /* Blocking those signals */
    Sigprocmask(SIG_BLOCK,&setNew,&setOld);

   /*
    * Check if the user is inputting a Builtin 
    * Command : jobs,bg,gf or quit
    */

    if (!builtin_command(&tok))  
    {
         if ((pid=Fork()) == 0 ) 
         {
                 
                 /*Setting the ppid for all the children processes*/
                 Setpgid(0,0);

                /*Redirecting the input/output logic*/
                                  
                char * filename = NULL; 

                /*Checking for input filename */
                 if ((filename = tok.infile) != NULL ) 
                 {
                         int fd1 = Open(filename,O_RDONLY,MODE);
                         Dup2(fd1,STDIN_FILENO); //Redirecting stdin to fd
                         Close(fd1);
                 }
                 if ((filename = tok.outfile) != NULL ) 
                 {
                         int fd2 = Open(filename,O_WRONLY|O_CREAT,MODE);
                         Dup2(fd2,STDOUT_FILENO);//Redirecting stdiout to fd
                         Close(fd2);
                 }

                /*Unblocking the SIGINT,SIGTSTP & SIGCHDL signals inherited 
                 * from parent
                 */

                 Sigprocmask(SIG_UNBLOCK,&setNew,&setOld);


                 /*Executing a new program in child's context*/
                 
                 if (execve(tok.argv[0],tok.argv,environ) == -1) 
                 {
                         unix_error("Execve error");
                         exit(0);
                 }
         }


         if (!bg)
         { 
                 state = FG;
         } else { 
                 state = BG;
         }

         /*Adding job to the list */

         if (!addjob(job_list,pid,state,cmdline)) 
         {
                printf("Unable to add to the job list\n");
                fflush(stdout); 
         } 
  
         if (!bg) 
         {      
                 /* 
                  * Sigsuspend to suspend execution till Foreground process
                  * is reaped 
                  */

                 while  (fgpid(job_list)) { 
                         sigsuspend(&setOld); 
                 }
         } else 
         {
                 fprintf(stdout,"[%d] (%d) %s\n",pid2jid(pid),pid,cmdline);
         }

    }
        /* Unblocking the signals */
         Sigprocmask(SIG_UNBLOCK,&setNew,&setOld);
      
    return;
}

/*
 * builtin_command - Check & execute builtin-command (fg,bg, jobs or quit) 
 *                  if it exists
 *
 * Parameters : 
 *      tok :  Pointer to a cmdline_tokens structure. The elements of this
 *        structure will be populated with the parsed tokens.Characters
 *        enclosed in single or double quotes are treated as a 
 *        single argument.
 *
 * Returns : 
 *      1 : if it is a  builtin-command  
 *      0 : if it is not a builtin-command
 */

int builtin_command(struct cmdline_tokens * tok) 
{ 
/* Indicates if argv[0] is a builtin command */
         enum  builtins_type {
                         BUILTIN_NONE,
                         BUILTIN_QUIT,
                         BUILTIN_JOBS,
                         BUILTIN_BG,
                         BUILTIN_FG} type = tok->builtins;

         char * filename = NULL;
         int fd = STDOUT_FILENO; //default STDOUT descriptor in fd
         int oldFd = dup(STDOUT_FILENO);//Saving STDOUT descriptor
         switch(type) 
         { 
                 case BUILTIN_NONE : 
                      return 0;
                      break;
                 
                 case BUILTIN_QUIT : 
                      PRINTF("Exiting\n"); //Exiting the Tsh 
                      exit(0);
                 
                 case BUILTIN_JOBS:
                      /*
                       *  If filename is null, then output should be
                       *  directed to stdout otherwise output should
                       *  be directed to file and after file is written
                       *  output should be redirected back to STDOUT
                       */

                      if ((filename = tok->outfile) != NULL ) 
                      {
                         fd = Open(filename,O_WRONLY|O_CREAT,MODE);
                         Dup2(fd,STDOUT_FILENO);
                         Close(fd);
                      }
                    /* Job list to file or STDOUT */ 
                      listjobs(job_list,STDOUT_FILENO);
                    /* Restoring output to STDOUT */
                      Dup2(oldFd,STDOUT_FILENO);
                 
                      break;
                 
                 case BUILTIN_BG:
                 /*Moving the process to BG */
                      background(tok->argv[1]);
                      break;
                 
                 case BUILTIN_FG:
                 /*Moving the process to FG */
                      foreground(tok->argv[1]);
                      break;
         }
        return 1;
}

    

/*
 * background : Moves the job to background state
 *
 * parameters : pid_t pid (process ID)
 *
 * output : void
 */

void background(char * str) 
{
        int jid = atoi(&str[1]); //Fetching the job id from %5, jid -5

        /* Getting job from job_list with jid */
        struct job_t * job = getjobjid(job_list,jid);
        
        if (job != NULL) 
        {
                /* Fetching PID from the job*/
                pid_t pid = job->pid;
                /*Sending signal SIGCONT to start the process */
                Kill(pid,SIGCONT);
                /* Changing the state of job to BG*/
                job->state = BG;
                fprintf(stdout,"[%d] (%d) %s\n",jid,pid,job->cmdline);
        } else 
        {
                fprintf(stdout,"Not able to find job \n");
        }
}

/*
 * foreground : Moves the job to foreground state
 *
 * parameters : pid_t pid (process ID)
 *
 * output : void
 */

void foreground(char * str) 
{
        int jid = atoi(&str[1]);//Fetching the job id from %5, jid -5

        /* defining set of signale */
        sigset_t setOld;
        Sigemptyset(&setOld);


        /* Getting job from job_list with jid */
        struct job_t * job = getjobjid(job_list,jid);

        if (job != NULL) 
        {
                /* Fetching PID from the job*/
                pid_t pid = job->pid;
                /*Sending signal SIGCONT to start the process */
                Kill(pid,SIGCONT);
                /* Changing the state of job to BG*/
                job->state = FG;
        } else 
        {
                fprintf(stdout,"Not able to find job \n");
        }
        sigsuspend(&setOld);

}


/* 
 * parseline - Parse the command line and build the argv array.
 * 
 * Parameters:
 *   cmdline:  The command line, in the form:
 *
 *                command [arguments...] [< infile] [> oufile] [&]
 *
 *   tok:      Pointer to a cmdline_tokens structure. The elements of this
 *             structure will be populated with the parsed tokens. Characters 
 *             enclosed in single or double quotes are treated as a single
 *             argument. 
 * Returns:
 *   1:        if the user has requested a BG job
 *   0:        if the user has requested a FG job  
 *  -1:        if cmdline is incorrectly formatted
 * 
 * Note:       The string elements of tok (e.g., argv[], infile, outfile) 
 *             are statically allocated inside parseline() and will be 
 *             overwritten the next time this function is invoked.
 */
int 
parseline(const char *cmdline, struct cmdline_tokens *tok) 
{

    static char array[MAXLINE];          /* holds local copy of command line */
    const char delims[10] = " \t\r\n";   /* argument delimiters (white-space) */
    char *buf = array;                   /* ptr that traverses command line */
    char *next;                          /* ptr to the end of the current arg */
    char *endbuf;                        /* ptr to end of cmdline string */
    int is_bg;                           /* background job? */

    int parsing_state;                   /* indicates if the next token is the
                                            input or output file */

    if (cmdline == NULL) {
        (void) fprintf(stderr, "Error: command line is NULL\n");
        return -1;
    }

    (void) strncpy(buf, cmdline, MAXLINE);
    endbuf = buf + strlen(buf);

    tok->infile = NULL;
    tok->outfile = NULL;

    /* Build the argv list */
    parsing_state = ST_NORMAL;
    tok->argc = 0;

    while (buf < endbuf) {
        /* Skip the white-spaces */
        buf += strspn (buf, delims);
        if (buf >= endbuf) break;

        /* Check for I/O redirection specifiers */
        if (*buf == '<') {
            if (tok->infile) {
                (void) fprintf(stderr, "Error: Ambiguous I/O redirection\n");
                return -1;
            }
            parsing_state |= ST_INFILE;
            buf++;
            continue;
        }
        if (*buf == '>') {
            if (tok->outfile) {
                (void) fprintf(stderr, "Error: Ambiguous I/O redirection\n");
                return -1;
            }
            parsing_state |= ST_OUTFILE;
            buf ++;
            continue;
        }

        if (*buf == '\'' || *buf == '\"') {
            /* Detect quoted tokens */
            buf++;
            next = strchr (buf, *(buf-1));
        } else {
            /* Find next delimiter */
            next = buf + strcspn (buf, delims);
        }
        
        if (next == NULL) {
            /* Returned by strchr(); this means that the closing
               quote was not found. */
            (void) fprintf (stderr, "Error: unmatched %c.\n", *(buf-1));
            return -1;
        }

        /* Terminate the token */
        *next = '\0';

        /* Record the token as either the next argument or the i/o file */
        switch (parsing_state) {
        case ST_NORMAL:
            tok->argv[tok->argc++] = buf;
            break;
        case ST_INFILE:
            tok->infile = buf;
            break;
        case ST_OUTFILE:
            tok->outfile = buf;
            break;
        default:
            (void) fprintf(stderr, "Error: Ambiguous I/O redirection\n");
            return -1;
        }
        parsing_state = ST_NORMAL;

        /* Check if argv is full */
        if (tok->argc >= MAXARGS-1) break;

        buf = next + 1;
    }

    if (parsing_state != ST_NORMAL) {
        (void) fprintf(stderr,
                       "Error: must provide file name for redirection\n");
        return -1;
    }

    /* The argument list must end with a NULL pointer */
    tok->argv[tok->argc] = NULL;

    if (tok->argc == 0)  /* ignore blank line */
        return 1;

    if (!strcmp(tok->argv[0], "quit")) {                 /* quit command */
        tok->builtins = BUILTIN_QUIT;
    } else if (!strcmp(tok->argv[0], "jobs")) {          /* jobs command */
        tok->builtins = BUILTIN_JOBS;
    } else if (!strcmp(tok->argv[0], "bg")) {            /* bg command */
        tok->builtins = BUILTIN_BG;
    } else if (!strcmp(tok->argv[0], "fg")) {            /* fg command */
        tok->builtins = BUILTIN_FG;
    } else {
        tok->builtins = BUILTIN_NONE;
    }

    /* Should the job run in the background? */
    if ((is_bg = (*tok->argv[tok->argc-1] == '&')) != 0)
        tok->argv[--tok->argc] = NULL;

    return is_bg;
}


/*****************
 * Signal handlers
 *****************/

/* 
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP, SIGTSTP, SIGTTIN or SIGTTOU signal. The 
 *     handler reaps all available zombie children, but doesn't wait 
 *     for any other currently running children to terminate.  
 */
void 
sigchld_handler(int sig) 
{
    pid_t pid1 ;//Pid of child process reaped
    /* status of terminated/stopped child*/
    int status;

    /* 
     * Reap all the children with waitpid set for No Hang for both 
     * Stopped/terminated children
     */

    while((pid1 = waitpid(-1,&status,WNOHANG|WUNTRACED)) > 0 ) 
    {
           
                       
           if (WIFSTOPPED(status)) 
            {
                    /*changing the status in job_list*/
                    fprintf(stdout,"Job [%d] (%d) stopped by signal %d\n"
                                    ,pid2jid(pid1),pid1,SIGTSTP);
                    struct job_t * jobStopped = getjobpid(job_list,pid1);
                    /* Stopping the job and changing the state to ST*/
                    jobStopped -> state = ST;
                    continue;
            }
            if (WIFSIGNALED(status)) 
            {
                    /*changing the status in job_list*/
                    fprintf(stdout,"Job [%d] (%d) terminated by signal %d\n"
                                    ,pid2jid(pid1),pid1,SIGINT);
            }
            if(!deletejob(job_list,pid1)) 
            {
                    fprintf(stdout,"Unable to delete job");
            }
            
    }

    return;
}

/* 
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.  
 */
void 
sigint_handler(int sig) 
{
   
        pid_t fgGRP =  fgpid(job_list);

/* Sending SIGKILL if fg process is not zero */
        if (fgGRP) {
                Kill(-fgGRP,SIGKILL);
        } else { 
                PRINTF("Parent process cannot be terminated\n");
        }

        if(fgpid(job_list) == 0 ) 
        {
                fprintf(stdout,"FG process killed\n");
                PRINTF("FG process killed\n");
        }

    return;
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.  
 */
void 
sigtstp_handler(int sig) 
{
   
        pid_t fgGRP =  fgpid(job_list);


/* Sending SIGSTOP if fg process is not zero */
        if (fgGRP) {
                Kill(-fgGRP,SIGSTOP);
        } else { 
                PRINTF("Parent process cannot be stopped\n");
        }

        if(fgpid(job_list) == 0 ) 
        {
                PRINTF("FG process stopped\n");
        }
    return;
}

/*********************
 * End signal handlers
 *********************/

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

/* clearjob - Clear the entries in a job struct */
void 
clearjob(struct job_t *job) {
    job->pid = 0;
    job->jid = 0;
    job->state = UNDEF;
    job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void 
initjobs(struct job_t *job_list) {
    int i;

    for (i = 0; i < MAXJOBS; i++)
        clearjob(&job_list[i]);
}

/* maxjid - Returns largest allocated job ID */
int 
maxjid(struct job_t *job_list) 
{
    int i, max=0;

    for (i = 0; i < MAXJOBS; i++)
        if (job_list[i].jid > max)
            max = job_list[i].jid;
    return max;
}

/* addjob - Add a job to the job list */
int 
addjob(struct job_t *job_list, pid_t pid, int state, char *cmdline) 
{
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++) {
        if (job_list[i].pid == 0) {
            job_list[i].pid = pid;
            job_list[i].state = state;
            job_list[i].jid = nextjid++;
            if (nextjid > MAXJOBS)
                nextjid = 1;
            strcpy(job_list[i].cmdline, cmdline);
            if(verbose){
                printf("Added job [%d] %d %s\n",
                       job_list[i].jid,
                       job_list[i].pid,
                       job_list[i].cmdline);
            }
            return 1;
        }
    }
    printf("Tried to create too many jobs\n");
    return 0;
}

/* deletejob - Delete a job whose PID=pid from the job list */
int 
deletejob(struct job_t *job_list, pid_t pid) 
{
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++) {
        if (job_list[i].pid == pid) {
            clearjob(&job_list[i]);
            nextjid = maxjid(job_list)+1;
            return 1;
        }
    }
    return 0;
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t 
fgpid(struct job_t *job_list) {
    int i;

    for (i = 0; i < MAXJOBS; i++)
        if (job_list[i].state == FG)
            return job_list[i].pid;
    return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t 
*getjobpid(struct job_t *job_list, pid_t pid) {
    int i;

    if (pid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (job_list[i].pid == pid)
            return &job_list[i];
    return NULL;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *job_list, int jid) 
{
    int i;

    if (jid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (job_list[i].jid == jid)
            return &job_list[i];
    return NULL;
}

/* pid2jid - Map process ID to job ID */
int 
pid2jid(pid_t pid) 
{
    int i;

    if (pid < 1)
        return 0;
    for (i = 0; i < MAXJOBS; i++)
        if (job_list[i].pid == pid) {
            return job_list[i].jid;
        }
    return 0;
}

/* listjobs - Print the job list */
void 
listjobs(struct job_t *job_list, int output_fd) 
{
    int i;
    char buf[MAXLINE];

    for (i = 0; i < MAXJOBS; i++) {
        memset(buf, '\0', MAXLINE);
        if (job_list[i].pid != 0) {
            sprintf(buf, "[%d] (%d) ", job_list[i].jid, job_list[i].pid);
            if(write(output_fd, buf, strlen(buf)) < 0) {
                fprintf(stderr, "Error writing to output file\n");
                exit(1);
            }
            memset(buf, '\0', MAXLINE);
            switch (job_list[i].state) {
            case BG:
                sprintf(buf, "Running    ");
                break;
            case FG:
                sprintf(buf, "Foreground ");
                break;
            case ST:
                sprintf(buf, "Stopped    ");
                break;
            default:
                sprintf(buf, "listjobs: Internal error: job[%d].state=%d ",
                        i, job_list[i].state);
            }
            if(write(output_fd, buf, strlen(buf)) < 0) {
                fprintf(stderr, "Error writing to output file\n");
                exit(1);
            }
            memset(buf, '\0', MAXLINE);
            sprintf(buf, "%s\n", job_list[i].cmdline);
            if(write(output_fd, buf, strlen(buf)) < 0) {
                fprintf(stderr, "Error writing to output file\n");
                exit(1);
            }
        }
    }
}
/******************************
 * end job list helper routines
 ******************************/


/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void 
usage(void) 
{
    printf("Usage: shell [-hvp]\n");
    printf("   -h   print this message\n");
    printf("   -v   print additional diagnostic information\n");
    printf("   -p   do not emit a command prompt\n");
    exit(1);
}

/*
 * unix_error - unix-style error routine
 */
void 
unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/*
 * app_error - application-style error routine
 */
void 
app_error(char *msg)
{
    fprintf(stdout, "%s\n", msg);
    exit(1);
}

/*
 * Signal - wrapper for the sigaction function
 */
handler_t 
*Signal(int signum, handler_t *handler) 
{
    struct sigaction action, old_action;

    action.sa_handler = handler;  
    sigemptyset(&action.sa_mask); /* block sigs of type being handled */
    action.sa_flags = SA_RESTART; /* restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0)
        unix_error("Signal error");
    return (old_action.sa_handler);
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void 
sigquit_handler(int sig) 
{
    printf("Terminating after receipt of SIGQUIT signal\n");
    exit(1);
}
