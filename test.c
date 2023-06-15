#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* computation(void* arg){
    long curr = (long) arg;
    long sum = 0;
    printf("number of increamentation from Thread: %ld\n", curr);
    for(int i = 0; i < curr; i++){
        sum ++;
    }
    return (void*) sum;
}

int main(int argc, char* argv[]){
    pthread_t t1, t2;
    long a = 50;
    long b = 100;
    void* result1;
    void* result2;
    pthread_create(&t1, NULL, computation, (void*) a);
    pthread_create(&t2, NULL, computation, (void*) b);
    pthread_join(t1, &result1);
    pthread_join(t2, &result2);
    //pthread_exit(NULL);
    printf("Total sum is: %ld\n", (long)result1 + (long)result2);
    return 0;
}