#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NP 2
#define NC 2
#define N_LOOPS 5

int buffer;
int count = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_p = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_c = PTHREAD_COND_INITIALIZER;

void *producers(void *args){
    srand(time(NULL));
    for(int i=0;i<N_LOOPS;i++){
        pthread_mutex_lock(&m);
        while(count == 1){
            pthread_cond_wait(&cv_p,&m);
        }

        buffer = rand()%100; // Assign a random number between 0 and 99
        count = 1; //A new value is present
        pthread_cond_signal(&cv_c); //Signal to one consumer that a value is present
        pthread_mutex_unlock(&m);
    }

}

void *consumers(void *args){

    for(int i = 0; i<N_LOOPS; i++){

        pthread_mutex_lock(&m);
        while(count==0){
            pthread_cond_wait(&cv_c, &m);
        }
        printf("Value read: %d\n", buffer);
        count = 0; // The buffer has been read
        pthread_cond_signal(&cv_p); // Signal to one producer that the value has been consumed
        pthread_mutex_unlock(&m);
    }

}

int main() {
    pthread_t *p;
    pthread_t *c;

    p = (pthread_t*)malloc(NP *sizeof(pthread_t));
    c = (pthread_t*)malloc(NC *sizeof(pthread_t));

    for(int i=0;i<NP;i++)
        pthread_create(&p[i],NULL,producers,NULL);
    for(int i=0;i<NC;i++)
        pthread_create(&c[i],NULL,consumers,NULL);

    for(int i=0;i<NP;i++)
        pthread_join(p[i],NULL);
    for(int i=0;i<NC;i++)
        pthread_join(c[i],NULL);

    return 0;
}
