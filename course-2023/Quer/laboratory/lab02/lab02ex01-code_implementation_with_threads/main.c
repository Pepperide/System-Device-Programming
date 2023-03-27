#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadData{
    long int *tids;
    int n; // To be decremented every time a child thread will be created
    int size; // Size of the generation tree
};

void *thread_generator(void *arg);

int main(int argc, char** argv) {
    int n;
    struct ThreadData td[2];

    pthread_t t[2];

    if(argc!=2){
        fprintf(stderr,"Error on passing parameters\n");
        exit(1);
    }

    n=atoi(argv[1]);

    for(int i=0;i<2;i++){
        td[i].tids = (long int *)malloc(n * sizeof(long int));
        td[i].n=n;
        td[i].size=n;
        td[i].tids[n-1] = pthread_self();
        pthread_create(&t[i],NULL, thread_generator,(void *)&td[i]);
    }

    for(int i=0;i<2;i++){
        pthread_join(t[i],NULL);
    }

    return 0;
}

void *thread_generator(void *arg){
    int n = ((struct ThreadData *)arg)->n;
    int size = ((struct ThreadData *)arg)->size;
    long int *tids = ((struct ThreadData *)arg)->tids;

    struct ThreadData td[2];
    pthread_t t[2];

    if(n==1){
        for(int i=size-1;i>=0;i--){
            printf("%lu ",tids[i]);
        }
        printf("\n");
        pthread_exit((void *)0);
    }

    n-=1;
    for(int i=0;i<2;i++){
        td[i].n=n;
        td[i].size=size;
        td[i].tids = (long int *)malloc(size * sizeof(long int));
        for(int j=size-1;j>=n;j--)
            td[i].tids[j] = tids[j];
        td[i].tids[n-1] = pthread_self();
        pthread_create(&t[i],NULL,thread_generator,(void *)&td[i]);
    }

    for(int i=0;i<2;i++){
        pthread_join(t[i],NULL);
    }

    pthread_exit((void *)0);
}
