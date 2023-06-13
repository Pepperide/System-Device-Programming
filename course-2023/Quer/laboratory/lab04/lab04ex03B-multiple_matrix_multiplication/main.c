#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

struct ThreadData{
    int id;
    int n;
    float *v1;
    float *v2;
    float **mat;
    float *v;
};
int done = 0;
sem_t m;
float final_res=0;

void* matrixMul(void *args){
    struct ThreadData td = *(struct ThreadData *)args;

    for(int i=0; i<td.n; i++)
        td.v[td.id] += (td.v1[i] * td.mat[i][td.id]);

    sem_wait(&m);
    done ++;
    if(done >= td.n){
        for(int i=0; i<td.n; i++)
            final_res += (td.v[i] * td.v2[i]);
        printf("Result: %.3f\n",final_res);
    }
    sem_post(&m);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    int n;
    float *v1, *v2;
    float **mat;
    float res=0;
    pthread_t *t;
    struct ThreadData *td;

    if(argc!=2){
        fprintf(stderr, "Error, wrong number of parameters!\n");
        exit(1);
    }

    n=atoi(argv[1]);

    v1 = (float *)malloc(n*sizeof(float));
    v2 = (float *)malloc(n*sizeof(float));
    mat = (float **)malloc(n*sizeof(float*));
    for(int i=0; i<n; i++)
        mat[i] = (float *)malloc(n*sizeof(float));

    // Fill v1, v2 and mat with random value in range [-0.5,0.5]
    for(int i =0; i<n; i++){
        for(int j=0; j<n; j++){
            mat[i][j] = ((float)rand()/(float)RAND_MAX) - 0.5; // [-0.5,0.5]
        }
        v1[i] = ((float)rand()/(float)RAND_MAX) - 0.5;
        v2[i] = ((float)rand()/(float)RAND_MAX) - 0.5;
    }

    printf("v1^T: \n[");
    for(int i=0;i<n;i++)
        printf("%.3f, ", v1[i]);
    printf("]\n");

    printf("mat: \n[");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%.3f, ",mat[i][j]);
        }
        i<n-1?printf("\n"):1;
    }
    printf("]\n");

    printf("v2: \n[");
    for(int i=0;i<n;i++)
        printf("%.3f, ", v2[i]);
    printf("]\n");

    t = (pthread_t *)malloc(n * sizeof(pthread_t));
    td = (struct ThreadData *)malloc(n * sizeof(struct ThreadData));
    float *v = (float *) calloc(n , sizeof(float));
    sem_init(&m,0,1);
    for(int i=0; i<n; i++){
        td[i].id = i;
        td[i].n = n;
        td[i].v1 = v1;
        td[i].v2 = v2;
        td[i].mat = mat;
        td[i].v = v;
        pthread_create(&t[i], NULL, matrixMul, (void *)&td[i]);
    }

    for(int i=0; i<n; i++){
        pthread_join(t[i],NULL);
    }

    return 0;
}
