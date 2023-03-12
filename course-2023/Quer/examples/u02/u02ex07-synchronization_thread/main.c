#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int array_sum(int *vet, int n);
void *adder(void *arg);

struct ThreadData{
    int id;
    int *vet;
    int n;
    sem_t *sem;
};

int main() {
    int vet[] = {1,3,-2,4,7,11,-8,2,1,-5,16,4,2,-5,2,1};
    int N, retValue;

    N = sizeof(vet)/sizeof(int); //Array length
    retValue = array_sum(vet,N);

    printf("Sum: %d",retValue);
    return 0;
}

int array_sum(int *vet, int n){
    int k=n/2;
    pthread_t *threads;
    struct ThreadData *td;
    sem_t *sem;

    threads = (pthread_t *)malloc(k * sizeof(pthread_t)); //n/2 threads and semaphores
    sem=(sem_t *)malloc(k*sizeof(sem_t));
    td=(struct ThreadData *)malloc(k * sizeof(struct ThreadData));

    /*Initializing semaphores to 0 (All blocked)*/
    for(int i=0;i<k;i++)
        sem_init(&sem[i],0,0);

    for(int i=0;i<k;i++){
        td[i].id=i;
        td[i].vet = vet; //Array of n elements
        td[i].n = n;
        td[i].sem = sem; //Array of n/2 semaphores
    }

    /* Thread creation */
    for(int i=0;i<k;i++)
        pthread_create(&threads[i],NULL,adder,(void *)&td[i]);

    pthread_join(threads[0], NULL); // Wait for the last thread
    for(int i=0;i<k;i++)
        sem_destroy(&sem[i]);
    free(threads);
    free(sem);
    free(td);
    return vet[0]; //Return the sum of the element of the array. First element is the sum
}

void *adder(void *arg){
    sem_t *sem = ((struct ThreadData *)arg)->sem; //Array of semaphores
    int *vet = ((struct ThreadData *)arg)->vet;
    int id = ((struct ThreadData *)arg)->id;
    int n = ((struct ThreadData *)arg)->n;
    int k=n/2;

    while(k!=0){
        if(k<n/2){
            sem_wait (&sem[id+k]);
        }
        vet[id] += vet[id+k]; //Each thread must add its associated value of the array
        k = k/2;
        if(id>=k){
            // This thread must be stopped and it releases the semaphore
            // When a thread ends, the following addition can be performed
            sem_post (&sem[id]);
            break;
        }
    }
    pthread_exit(0);
}