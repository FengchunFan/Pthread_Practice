/******************************************************************************
* FILE: hello.c
* DESCRIPTION:
*   A "hello world" Pthreads program.  Demonstrates thread creation and
*   termination.
* AUTHOR: Blaise Barney
* LAST REVISED: 08/09/11
* OBSERVATION: 5 threads created in order 0 - 4, but the order of thread appearance is random
*              using (long) for threadid type to match void pointer size, int works but will give warning
*              able to change file from pthread_exit to pthread_join with same behavior
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#define NUM_THREADS	5

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   //int tid;
   //tid = (int)(intptr_t)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   //printf("Hello World! It's me, thread #%d!\n", tid);
   //pthread_exit(NULL);
   return NULL;
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   //int t;
   for(t=0;t<NUM_THREADS;t++){
     printf("In main: creating thread %ld\n", t);
     //printf("In main: creating thread %d\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
     if (rc){ //pthread functions will return 0 if ok, thus if not there is an error
       printf("ERROR; return code from pthread_create() is %d\n", rc);
       exit(-1);
       }
   }
   for(t=0;t<NUM_THREADS;t++){
    pthread_join(threads[t], NULL);
   }

   /* Last thing that main() should do */
   //pthread_exit(NULL);
}