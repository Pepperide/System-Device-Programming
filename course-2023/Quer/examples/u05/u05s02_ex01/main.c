#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void waitRandomTime(int max){ sleep((int) (rand() % max) +1); }

void* A(void * args){ printf("A\n"); }
void* B(void * args){ printf("B\n"); }
void* C(void * args){ printf("C\n"); }
void* D(void * args){ printf("D\n"); }
void* E(void * args){ printf("E\n"); }
void* F(void * args){ printf("F\n"); }
void* G(void * args){ printf("G\n"); }

int main() {
    pthread_t tid_abd;
    pthread_t tid_cf;
    pthread_t tid_e;
    pthread_t tid_g;

    srand(time(NULL));

    pthread_create(&tid_abd, NULL,  A, NULL);
    waitRandomTime(1);
    pthread_join(tid_abd,NULL);

    pthread_create(&tid_abd, NULL,  B, NULL);
    pthread_create(&tid_cf, NULL,  C, NULL);
    waitRandomTime(5);
    pthread_join(tid_abd,NULL);

    pthread_create(&tid_abd, NULL,  D, NULL);
    pthread_create(&tid_e, NULL,  E, NULL);
    waitRandomTime(5);

    pthread_join(tid_cf,NULL);
    pthread_create(&tid_cf, NULL,  F, NULL);
    waitRandomTime(5);

    pthread_join(tid_abd,NULL);
    pthread_join(tid_e,NULL);
    pthread_join(tid_cf,NULL);

    pthread_create(&tid_g, NULL,  G, NULL);
    pthread_join(tid_g,NULL);
    return 0;

}

