#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N 20

int v[N] = {59,21,74,2,7,3,44,62,2,17,0,4,2,11,543,0,32,78,6,3};
int sorted = 0;

sem_t *sem_slave;
sem_t *sem_master;

void* master(void* args){
    int val;
    int isSorted;

    while(!sorted){
        isSorted = 1;
        for(int i=0; i< N-1;i++){
            sem_wait(sem_master);
        }
        for(int i=1;i<N;i++){
            if(v[i-1]>v[i])
                isSorted = 0;
        }
        if(isSorted){
            sorted = 1;
        }
        for(int i=0;i<N;i++){
            // Wake up all the workers
            sem_post(&sem_slave[i]);
        }
    }

}

void *slave(void *args){
    int id = *(int*)args;

    while(!sorted){

        sem_wait(&sem_slave[id]); // Reserve my own slot of the vector
        sem_wait(&sem_slave[id + 1]); // Reserve the next slot to be compared with mine
        if(v[id]>v[id+1]){
            int temp = v[id+1];
            v[id+1]=v[id];
            v[id] = temp;
        }
        sem_post(&sem_slave[id+1]);
        sem_post(&sem_slave[id]);

        sem_post(sem_master);
    }

}

int main() {
    int ids[N];
    pthread_t *s;
    pthread_t m; // It checks if the array is sorted or not

    s=(pthread_t*)malloc((N-1) * sizeof(pthread_t));

    sem_master = (sem_t *) malloc(sizeof(sem_t));
    sem_slave = (sem_t *)malloc(N * sizeof(sem_t)); // A semaphore force each element of the array

    sem_init(sem_master,0,N-1);
    for(int i=0;i<N;i++){
        // At the beginning all the slaves must wait
        sem_init(&sem_slave[i],0,0);
    }

    pthread_create(&m,NULL,master,NULL);
    for(int i=0; i<N-1;i++){
        ids[i]=i;
        pthread_create(&s[i],NULL,slave,&ids[i]);
    }

    pthread_join(m,NULL);
    for(int i=0;i<N-1;i++)
        pthread_join(s[i],NULL);

    for(int i=0;i<N;i++)
        printf("%d ",v[i]);
    return 0;
}
