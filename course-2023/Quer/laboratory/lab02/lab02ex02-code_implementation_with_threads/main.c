#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct ThreadData{
    int **C;
    int **A;
    int **B;
    int i;
    int j;
    int x;
};

void mat_mul (int **A, int **B, int r, int x, int c, int **C);
void *add(void *arg);
int main(void) {
    int r=2,x=3,c=2;
    int **A;
    int **B;
    int **C;

    /* Simple matrix initialization and value assignment*/
    A = (int **)malloc(r *sizeof(int *));
    for(int i=0;i<r;i++)
        A[i]=(int *)malloc(x*sizeof(int));

    B = (int **)malloc(x *sizeof(int *));
    for(int i=0;i<x;i++)
        B[i]=(int *)malloc(c*sizeof(int));

    C = (int **)malloc(r *sizeof(int *));
    for(int i=0;i<c;i++)
        C[i]=(int *)calloc(c, sizeof(int));

    int val=0;
    for(int i=0;i<r;i++){
        for(int j=0;j<x;j++){
            A[i][j]=++val;
        }
    }
    val=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<c;j++){
            B[i][j]=++val;
        }
    }
    /* END MATRIX INITIALIZATION */


    mat_mul(A,B,r,x,c,C);
    return 0;
}

void mat_mul (int **A, int **B, int r, int x, int c, int **C){
    pthread_t *t;
    struct ThreadData **td;

    t=(pthread_t *)malloc(r * c * sizeof(pthread_t));
    td = (struct ThreadData **)malloc(r*sizeof(struct ThreadData *));
    for(int i=0;i<r;i++){
        td[i]= (struct ThreadData *)malloc(c*sizeof(struct ThreadData));
    }

    for (int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            td[i][j].C=C; // C matrix is shared among all threads
            td[i][j].A=A;
            td[i][j].B=B;
            td[i][j].i=i;
            td[i][j].j=j;
            td[i][j].x=x;
            pthread_create(&t[i],NULL,add,(void *)&td[i][j]);
        }
    }

    for(int i=0;i<r*c;i++){
        pthread_join(t[i],NULL);
    }

    /* PRINT RESULT */
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",C[i][j]);
        }
        printf("\n");
    }
    return;
}

void *add(void *arg){
    int **C = ((struct ThreadData *)arg)->C;
    int **A = ((struct ThreadData *)arg)->A;
    int **B = ((struct ThreadData *)arg)->B;
    int x = ((struct ThreadData *)arg)->x;
    int i = ((struct ThreadData *)arg)->i;
    int j = ((struct ThreadData *)arg)->j;

    for(int k=0;k<x;k++){
        C[i][j]+=A[i][k]*B[k][j];
    }
    pthread_exit(0);
}