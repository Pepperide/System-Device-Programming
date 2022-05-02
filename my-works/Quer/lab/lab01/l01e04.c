#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int n, h;
    pid_t pid;
    
    if(argc != 3){
        fprintf(stderr,"Wrong number of parameters\n");
        exit(1);
    }
    n = atoi (argv[1]);
    h = atoi (argv[2]);

    pid = getpid();
    printf("Padre: %d\n",pid);

    for(int i=0;i<=h;i++){       
        if(pid = fork()){
            for(int j=0;j<(n-1);j++)
            {
                if(fork()){ 
                    wait();
                    return(0);
                }
                else
                    printf("Figlio %d --> PID: %d; PPID: %d\n",i+1,getpid(),getppid());
            }
        }
        else{
            printf("Figlio %d --> PID: %d; PPID: %d\n",i+1,getpid(),getppid());
        }
  
    }

    wait();
    return 0;
}