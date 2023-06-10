#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int n=0;

sem_t *sem_a;
sem_t *sem_b;
sem_t *m;

void *TA(void* args){
    while(1){
        sleep(rand()%3);

        sem_wait(sem_a);
        sem_wait(m);
        n++;
        printf("A");
        if(n>=3){
            printf("\n");
            n=0;
            sem_post(sem_a);
            sem_post(sem_b);
            sem_post(sem_b);
        }
        sem_post(m);
    }
}
void *TB(void *args){
    while(1){
        sleep(rand()%2);

        sem_wait(sem_b);
        sem_wait(m);
        n++;
        printf("B");
        if(n>=3){
            printf("\n");
            n=0;
            sem_post(sem_a);
            sem_post(sem_b);
            sem_post(sem_b);
        }
        sem_post(m);
    }
}

int main() {
    pthread_t ta;
    pthread_t tb;

    srand(time(NULL));
    setbuf(stdout,0);
    sem_a = (sem_t *)malloc(sizeof(sem_t));
    sem_b = (sem_t *)malloc(sizeof(sem_t));
    m = (sem_t *)malloc(sizeof(sem_t));
    sem_init(sem_a,0,1);
    sem_init(sem_b,0,2);
    sem_init(m, 0,1);

    pthread_create(&ta,NULL,TA, NULL);
    pthread_create(&tb,NULL,TB, NULL);

    pthread_join(ta,NULL);
    pthread_join(tb,NULL);
    return 0;
}
