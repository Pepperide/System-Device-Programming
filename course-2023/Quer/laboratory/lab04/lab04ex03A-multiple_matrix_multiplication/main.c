#include <stdio.h>
#include <stdlib.h>

float matrixMul(int n, float *v1, float *v2, float **mat){
    // Multiplication of v1^T * mat * v2
    float *v_temp;
    float res=0;

    v_temp = calloc( n, sizeof(float));

    // v1^T * mat
    for(int i=0; i<n; i++)
        for(int j=0;j<n;j++)
            v_temp[i]+= (v1[i]*mat[i][j]);

    // v_temp * v2
    for(int i=0;i<n;i++)
        res+=(v_temp[i]* v2[i]);

    return res;
}

int main(int argc, char **argv) {
    int n;
    float *v1, *v2;
    float **mat;
    float res;

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

    res = matrixMul(n,v1,v2,mat);
    printf("Result: %.3f\n",res);

    return 0;
}
