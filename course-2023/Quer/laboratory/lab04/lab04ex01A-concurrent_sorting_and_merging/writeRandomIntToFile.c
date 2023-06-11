#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv){
    int n;
    int fd;

    // The program accepts 2 parameters: <num of integer> <filename>
    if(argc != 3){
        fprintf(stderr, "Error: wrong number of parameters!\n");
        exit(1);
    }
    n= atoi(argv[1]);
    fd = open(argv[2],O_WRONLY |O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(write(fd,&n, sizeof(int)) == -1){
        fprintf(stderr, "Error: Unable to write the file\n");
        exit(1);
    }
    for(int i=0;i<n;i++){
        srand(time(NULL) + i);
        int num = rand();
        if(write(fd,&num, sizeof(int)) == -1){
            fprintf(stderr, "Error: Unable to write the file\n");
            exit(1);
        }
    }
    close(fd);
    return 0;
}