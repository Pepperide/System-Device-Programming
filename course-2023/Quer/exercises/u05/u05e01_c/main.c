#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t *sem_a;
sem_t *sem_b;
int n;

void *TA(void* args){
    int id = *(int *)args;

    sleep(rand()%3);

    sem_wait(sem_a);
    printf("TA{%d}",id);
    n++;
    sem_post(sem_b);

    pthread_exit(NULL);
}

void *TB(void* args){
    int id = *(int *)args;

    sleep(rand()%5);

    sem_wait(sem_b);
    printf("TB{%d}",id);
    n++;
    if(n>=3){
        printf("\n");
        n=0;
        sem_post(sem_a);
    }else{
        sem_post(sem_b);
    }

    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t *ta;
    pthread_t *tb;
    int K;

    srand(time(NULL));
    setbuf(stdout, 0);

    if(argc!=2){
        fprintf(stderr,"Error: wrong number of parameters\n");
        exit(0);
    }

    K= atoi(argv[1]);
    ta = (pthread_t *)malloc(K *sizeof(pthread_t));
    tb = (pthread_t *)malloc(2*K *sizeof(pthread_t));

    sem_a = (sem_t *)malloc(sizeof(sem_t));
    sem_b = (sem_t *)malloc(sizeof(sem_t));
    sem_init(sem_a,0,1);
    sem_init(sem_b,0,0);

    for(int i=0;i<K;i++){
        int* id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&ta[i],NULL,TA,id);
    }

    for(int i=0;i<2*K;i++){
        int* id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&tb[i],NULL,TB,id);
    }

    for(int i=0;i<K;i++)
        pthread_join(ta[i],NULL);

    for(int i=0;i<2*K;i++)
        pthread_join(tb[i],NULL);

    return 0;
}
