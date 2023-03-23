#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

struct ThreadData{
    int id;
    int n;
    int *vet;
};

void * binary(void *arg);
int main(int argc, char **argv) {
    int n,max=1;
    pthread_t *t;
    struct ThreadData *td;

    if(argc!=2){
        fprintf(stderr,"Error,wrong number of parameters\n");
        exit(0);
    }
    n=atoi(argv[1]);

    for(int i=0;i<n;i++){
        //Compute the power of two
        max= 2*max;
    }

    t = (pthread_t *)malloc(max*sizeof(pthread_t));
    td = (struct ThreadData *)malloc(max*sizeof(struct ThreadData));

    fflush(stdout);
    for(int i=0;i<max;i++){
        td[i].id=i;
        td[i].n=n;
        td[i].vet = (int *)malloc(n*sizeof(int));
        pthread_create(&t[i],NULL,binary,(void *)&td[i]);
    }
    for(int i=0;i<max;i++){
        for(int j=0;j<n;j++){
            printf("%d",td[i].vet[j]);
        }
        printf("\n");
        pthread_join(t[i],NULL);
    }

    return 0;
}

void * binary(void *arg){
    int id = ((struct ThreadData *) arg)->id;
    int n = ((struct ThreadData *) arg)->n;
    int *vet = ((struct ThreadData *)arg)->vet;

    //The id represent the binary number that it must print and n the n of bit
    for(int i=n-1;i>=0;i--){
        vet[i]=id%2;
        id/=2;
    }

    pthread_exit(0);
}