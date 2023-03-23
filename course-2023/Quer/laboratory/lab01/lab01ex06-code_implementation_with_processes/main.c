#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/wait.h"
#include "semaphore.h"

void generate(int start, int h, int n);

int main(int argc, char **argv) {
    int n, h;

    if (argc != 3) {
        fprintf(stderr, "Error, too few parameters\n");
        exit(0);
    }
    h = atoi(argv[1]);
    n = atoi(argv[2]);

    generate(0,h,n);

    return 0;
}

void generate(int start, int h, int n){
    if(start>=h){
        return;
    }
    for(int i=0;i<n;i++){
        if(fork()==0){
            //Child
            printf("I am CHILD %d PID=%d (Father is %d)\n",i+1,getpid(),getppid());
            generate(start+1,h,n);
            wait(NULL);
            exit(0);
        }else{
            //Father
            if(i==0)
                printf("I am the FATHER PID=%d\n",getpid());
            wait(NULL);
        }
    }

    return;
}