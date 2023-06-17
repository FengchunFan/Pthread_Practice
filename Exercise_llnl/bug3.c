/*****************************************************************************
* FILE: bug3.c
* DESCRIPTION:
*   This "hello world" Pthreads program demonstrates an unsafe (incorrect)
*   way to pass thread arguments at thread creation. Compare with hello_arg1.c.
* AUTHOR: Blaise Barney
* LAST REVISED: 07/16/14
* OBSERVATION: sleep() need to include <unistd.h> library
               the argument being passed in is incorrect: &t, this is the address
               one way to fix:
               pass in directly the t, and call it as long object in PrintHello function
               similar idea as in hello_arg1.c
               another way to fix:
               call pointer in print function in the PrintHello() function
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS     8

void *PrintHello(void *threadid)
{
   //long taskid; //orginal and fix1
   long* taskid;
   sleep(1);
   taskid = (long *)threadid; //orginal code
   //taskid = (long) threadid; //fix1
   //printf("Hello from thread %ld\n", taskid); //original
   printf("Hello from thread %ld\n", *taskid); //fix2
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
long thread_id[NUM_THREADS];
int rc;
long t;

for(t=0;t<NUM_THREADS;t++) {
  printf("Creating thread %ld\n", t);
  thread_id[t] = t;
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &thread_id[t]);
  //rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t); //orginal
  //rc = pthread_create(&threads[t], NULL, PrintHello, (void *) t); //fix1
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
   }

pthread_exit(NULL);
}
