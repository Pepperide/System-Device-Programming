#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int last_last=-1;
int last=-1;
int finish = 0;

void signal_handler(int sig);
int main(void) {

    if((signal(SIGUSR1,signal_handler))==SIG_ERR || (signal(SIGUSR2,signal_handler))==SIG_ERR){
        fprintf(stderr,"Error on instantiation the signals\n");
        exit(0);
    }
    while(finish == 0){
        pause();
    }
    return 0;
}

void signal_handler(int sig){
    if(sig == last_last && sig == last){
        finish=1;
    }
    else{
        if(sig!=last){
            if(last!=-1)
                fprintf(stdout,"SUCCESS\n");
        }
        else{
            fprintf(stderr,"ERROR\n");
        }
        last_last = last;
        last = sig;
    }

    return;
};