#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void* TA(void *arg);
void* TB(void *arg);

/* Global variables shared among all threads */
sem_t sem_A, sem_B;

int main(int argc,char** argv) {
    int n;
    pthread_t *threads_A; // Array of thread of type A
    pthread_t *threads_B; // Array of thread of type B
    int *id;

    if(argc!=2){
        printf("Error, wrong parameters\n");
        exit(1);
    }

    sem_init(&sem_A,0,1); // Type A threads can start writing
    sem_init(&sem_B,0,0);

    /* Thread generation */
    n = atoi(argv[1]);
    threads_A = (pthread_t *)malloc(n * sizeof(pthread_t));
    threads_B = (pthread_t *)malloc(n * sizeof(pthread_t));
    id = (int *)malloc(n * sizeof(int));

    for (int i=0;i<n;i++){
        id[i]=i; // Since we have to pass a pointer we have to store the index value to avoid changes
        pthread_create(&threads_A[i],NULL,TA,(void *) &id[i]);
        pthread_create(&threads_B[i],NULL,TB,(void *) &id[i]);
    }


    /* Thread joining */
    for(int i=0;i<n;i++){
        pthread_join(threads_A[i],NULL);
        pthread_join(threads_B[i],NULL);
    }

    free(threads_A);
    free(threads_B);
    free(id);
    return 0;
}

void* TA(void *arg){
    int id;
    id=*((int *)arg); //We have to cast the value since all args are void*
    while(1){
        sem_wait(&sem_A);
        printf("A%d ",id);
        fflush(stdout); // It forces the writing operation on the stdout
        sem_post(&sem_B);
    }
    pthread_exit(NULL);
}

void* TB(void *arg){
    int id;
    id=*((int *)arg); //We have to cast the value since all args are void*
    while(1){
        sem_wait(&sem_B);
        printf("B%d ",id);
        fflush(stdout);
        sem_post(&sem_A);
    }
    pthread_exit(NULL);
}
