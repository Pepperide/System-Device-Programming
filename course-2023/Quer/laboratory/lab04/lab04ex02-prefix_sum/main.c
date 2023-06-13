#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>

struct ThreadData{
    int id;
    int step;
    int *v;
};
int N_THREADS;
int N_ACTIVE;

sem_t barrier_sum;
sem_t barrier_upd;
sem_t m_sum;
sem_t m_upd;

int count = 0;


void* prefix_sum(void *args){
    struct ThreadData td = *(struct ThreadData *) args;
    int sum, gap;
    int n_active_threads = N_THREADS;


    for(int i=0; i<td.step; i++){
        n_active_threads = N_THREADS - pow(2,i) + 1;
        gap = pow(2,i);
        if(td.id <= gap - 1)
            break;

        sem_wait(&m_sum);

        sum = td.v[td.id] + td.v[td.id - gap];

        count ++;
        if( count >= n_active_threads ){
            count = 0;
            for(int j=0; j< n_active_threads; j++)
                sem_post(&barrier_sum);
        }
        sem_post(&m_sum);
        sem_wait(&barrier_sum);

        // Now the thread can update the original array
        sem_wait(&m_upd);
        td.v[td.id] = sum;

        count ++;
        if( count >= n_active_threads ){
            count = 0;
            for(int j=0; j< n_active_threads; j++)
                sem_post(&barrier_upd);
        }

        sem_post(&m_upd);
        sem_wait(&barrier_upd);


    }

    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    int n, n_elem;
    int *v;
    pthread_t *t;
    struct ThreadData *td;

    srand(time(NULL));
    setbuf(stdout, 0);
    if(argc!=2){
        fprintf(stderr,"Error, wrong number of parameters!\n");
        exit(1);
    }
    // Receives an integer value n as an argument of the command line
    n=atoi(argv[1]);
    n_elem = pow(2,n);
    N_THREADS = n_elem - 1;

    // Randomly generates an array v of 2^n integer elements in the range [1-9]
    // The main thread allocates, fills, and prints the initial content of the array v
    v = (int *)malloc(n_elem * sizeof(int));
    for(int i=0;i<n_elem;i++)
        v[i] = rand()%9 +1;



    printf("Initial array: ");
    for(int i=0;i<n_elem;i++)
        printf("%d ",v[i]);
    printf("\n\n");

    // Computes the prefix sum of
    t = (pthread_t *)malloc(N_THREADS * sizeof(pthread_t));
    td = (struct ThreadData *)malloc(N_THREADS * sizeof(struct ThreadData));
    sem_init(&barrier_sum,0,0);
    sem_init(&barrier_upd,0,0);
    sem_init(&m_sum,0,1);
    sem_init(&m_upd,0,1);
    for(int i=0; i<N_THREADS; i++ ){
        td[i].id = i+1;
        td[i].step = n;
        td[i].v = v;
        pthread_create(&t[i],NULL,prefix_sum, (void *)&td[i]);
    }

    // Print the result
    printf("Result array: ");
    printf("%d ",v[0]);
    for(int i=0; i<N_THREADS; i++ ){
        pthread_join(t[i], NULL);
        printf("%d ",v[i+1]);
    }

    return 0;
}
