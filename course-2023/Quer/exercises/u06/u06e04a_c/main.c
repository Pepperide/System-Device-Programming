#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define N 20

// First Reader-Writer problem.
// No reader will be kept waiting unless a writer has already obtained permission to use the shared object

sem_t *meR;
sem_t *meW;
sem_t *w;

int nR = 0;

void *readers(void *args){
    int id = *(int *)args;

    sem_wait(meR);
    nR ++;
    if(nR==1)
        sem_wait(w);
    sem_post(meR);

    printf("Thread %d is reading\n", id);

    sem_wait(meR);
    nR--;
    if(nR==0)
        sem_post(w);
    sem_post(meR);
}

void *writers(void *args){
    int id = *(int *)args;

    sem_wait(meW);
    sem_wait(w);

    printf("Thread %d is writing\n", id);

    sem_post(w);
    sem_post(meW);
}

int main() {
    pthread_t *rd;
    pthread_t *wr;
    int id[N];

    setbuf(stdout,0);

    rd = (pthread_t*)malloc(N*sizeof(pthread_t));
    wr = (pthread_t*)malloc(N*sizeof(pthread_t));

    meR = (sem_t *)malloc(sizeof(sem_t));
    meW = (sem_t *)malloc(sizeof(sem_t));
    w = (sem_t *)malloc(sizeof(sem_t));
    sem_init(meR,0,1);
    sem_init(meW,0,1);
    sem_init(w,0,1);

    for(int i=0;i<20;i++){
        id[i] = i;
        pthread_create(&rd[i],NULL,readers,&id[i]);
        pthread_create(&wr[i],NULL,writers,&id[i]);
    }

    for(int i=0;i<20;i++){
        pthread_join(rd[i],NULL);
        pthread_join(wr[i],NULL);
    }
    return 0;
}
