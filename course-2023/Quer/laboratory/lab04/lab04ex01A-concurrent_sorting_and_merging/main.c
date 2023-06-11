#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct ThreadData{
    int tid;
    int *v;
    char *filename;
    int len;
};

void* readAndSort(void * args){
    int tid = ((struct ThreadData *) args)->tid;
    int *v;
    char *filename = ((struct ThreadData *) args)-> filename;
    int fd;
    int n;

    // The thread open its own input file
    if((fd = open(filename,O_RDONLY))==-1){
        fprintf(stderr, "Error opening the input file %s", filename);
        exit(1);
    }

    // The thread reads the first integer
    if(read(fd,&n,sizeof(int)) == -1){
        fprintf(stderr, "Error reading the integer on file %s", filename);
        exit(1);
    }

    ((struct ThreadData *)args)->len = n;

    // Allocation of the dynamic array
    v = (int *)malloc(n*sizeof(int));
    ((struct ThreadData *) args)->v = v;

    // Read the others integer
    if(read(fd,v,n * sizeof(int)) == -1){
        fprintf(stderr, "Error reading the integer on file %s", filename);
        exit(1);
    }

    // Sort the array in ascending order
    for(int i=0; i<n; i++){
        for(int j=i;j<n;j++){
            if(v[i]>v[j]){
                int temp = v[j];
                v[j] = v[i];
                v[i] = temp;
            }
        }
    }

    close(fd);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    int n = argc - 1;
    int fd_out;
    pthread_t *t;
    struct ThreadData *td;
    clock_t start, end;

    start = clock();

    if(n < 2){
        fprintf(stderr, "Error: Wrong number of parameters");
        exit(1);
    }

    // The first n-1 strings are input files name
    // One thread for each input file
    t = (pthread_t *) malloc((n-1)*sizeof(pthread_t));
    td = (struct ThreadData *)malloc((n-1)*sizeof(struct ThreadData));
    for(int i=0; i<n-1;i++){
        td[i].tid = i;
        td[i].filename = argv[i+1];
        pthread_create(&t[i],NULL,readAndSort,(void *) &td[i]);
    }

    // Await for termination of all the threads
    int total_len = 0;
    for(int i=0; i< n-1; i++){
        pthread_join(t[i],NULL);
        total_len += td[i].len;
    }

    // Merge all the arrays in a unique array
    int *merged;
    merged = (int *)malloc(total_len * sizeof(int));
    int size = 0;
    for(int i=0; i<n-1;i++){
        for(int j=0;j<td[i].len;j++)
            merged[size+j] = td[i].v[j];
        size += td[i].len;
    }
    // Sort merged array
    for(int i=0; i<size; i++){
        for(int j=i;j<size;j++){
            if(merged[i]>merged[j]){
                int temp = merged[j];
                merged[j] = merged[i];
                merged[i] = temp;
            }
        }
    }

    // The last string is an output file name
    if((fd_out = open(argv[n], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
        fprintf(stderr, "Error on opening file %s", argv[n]);
        exit(1);
    }

    write(fd_out,&size,sizeof(int));
    write(fd_out, merged, size * sizeof(int));

    close(fd_out);
    end = clock();
    double time_taken = ((double)(end - start))/CLOCKS_PER_SEC; // in seconds
    fprintf(stdout, "Time occurred %f seconds", time_taken);
    return 0;
}
