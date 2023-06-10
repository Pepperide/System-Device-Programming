#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 10

sem_t *mutex;
sem_t *sem_p;
sem_t *sem_m;
sem_t *sem_s;
sem_t *sem_nl;
int n=0;
char next ='+';

void* plus(){
    while(1){
        sleep(1);
        sem_wait(sem_p);
        sem_wait(mutex);
        printf("+");
        n++;
        if(n>=N){
            next = '-';
            sem_post(sem_nl);
        }
        else
            sem_post(sem_p);

        sem_post(mutex);
    }
}
void* minus(){
    while(1){
        sleep(1);
        sem_wait(sem_m);
        sem_wait(mutex);
        printf("-");
        n++;
        if(n>=N){
            next = '*';
            sem_post(sem_nl);
        }
        else
            sem_post(sem_m);

        sem_post(mutex);
    }
}
void* star(){
    while(1){
        sleep(1);
        sem_wait(sem_s);
        sem_wait(mutex);
        printf("*");
        n++;
        if(n>=N){
            next = '+';
            sem_post(sem_nl);
        }
        else
            sem_post(sem_s);

        sem_post(mutex);
    }
}
void* newline(){
    while(1){
        sleep(1);
        sem_wait(sem_nl);
        sem_wait(mutex);
        printf("\n");
        n=0;
        switch(next){
            case '+':
                sem_post(sem_p);
                break;
            case '-':
                sem_post(sem_m);
                break;
            case '*':
                sem_post(sem_s);
                break;
        }
        sem_post(mutex);
    }
}

int main() {
    pthread_t tp;
    pthread_t tm;
    pthread_t ts;
    pthread_t tnl;

    srand(time(NULL));
    setbuf(stdout, 0);

    mutex = (sem_t *)malloc(sizeof(sem_t));
    sem_p = (sem_t *)malloc(sizeof(sem_t));
    sem_m = (sem_t *)malloc(sizeof(sem_t));
    sem_s = (sem_t *)malloc(sizeof(sem_t));
    sem_nl = (sem_t *)malloc(sizeof(sem_t));
    sem_init(mutex,0,1);
    sem_init(sem_p,0,1);
    sem_init(sem_m,0,0);
    sem_init(sem_s,0,0);
    sem_init(sem_nl,0,0);

    pthread_create(&tp,NULL,plus,NULL);
    pthread_create(&tm,NULL,minus,NULL);
    pthread_create(&ts,NULL,star,NULL);
    pthread_create(&tnl,NULL,newline,NULL);

    pthread_join(tp,NULL);
    pthread_join(tm,NULL);
    pthread_join(ts,NULL);
    pthread_join(tnl,NULL);
    return 0;
}