/******************************************************************************
* FILE: hello_arg1.c
* DESCRIPTION:
*   A "hello world" Pthreads program which demonstrates one safe way
*   to pass arguments to threads during thread creation.
* AUTHOR: Blaise Barney
* LAST REVISED: 08/04/15
* OBSERVATION: 8 threads are created at the same time
               only one argument is passed in the create function
               with the sleep() function, we can see creating message on top and thread message on bottom
               without the sleep() function, messages are mixed
               order of creating message is ordered and thread message is unordered
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS	8

char *messages[NUM_THREADS];

void *PrintHello(void *threadid)
{
   long taskid;

   //sleep(1);
   taskid = (long) threadid;
   printf("Thread %d: %s\n", taskid, messages[taskid]);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
long taskids[NUM_THREADS];
int rc, t;

messages[0] = "English: Hello World!";
messages[1] = "French: Bonjour, le monde!";
messages[2] = "Spanish: Hola al mundo";
messages[3] = "Klingon: Nuq neH!";
messages[4] = "German: Guten Tag, Welt!"; 
messages[5] = "Russian: Zdravstvuyte, mir!";
messages[6] = "Japan: Sekai e konnichiwa!";
messages[7] = "Latin: Orbis, te saluto!";

for(t=0;t<NUM_THREADS;t++) {
  taskids[t] = t;
  printf("Creating thread %d\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }

pthread_exit(NULL);
}

