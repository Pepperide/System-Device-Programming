#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int isFinish = 0;
int last_sig = -1;
int last_last_sig = -1;
void signal_handler(int sig){
    if(last_last_sig == sig && last_last_sig == last_sig){
        isFinish = 1;
    }
    if(sig == SIGUSR1) {
        printf("Signal received from P1\n");
    }
    if(sig == SIGUSR2)
        printf("Signal received from P2\n");

    last_last_sig = last_sig;
    last_sig = sig;
}

void P1();
void P2();
int main() {
    pid_t pid_P1, pid_P2;
    srand(time(NULL)); // To generate random numbers

    //Instantiate the signal handler with SIGUSR1 and SIGUSR2
    if(signal(SIGUSR1, signal_handler)== SIG_ERR || signal(SIGUSR2, signal_handler) == SIG_ERR){
        fprintf(stderr, "Error instantiating the signal handler\n");
        exit(1);
    }

    // Generating two child processes P1 and P2
    pid_P1 = fork();
    if(pid_P1==0){
        //Process P1
        P1();
    }else{
        pid_P2 = fork();
        if(pid_P2 == 0){
            //Process P2
            P2();
        }
    }

    // Waiting for process' signals
    while(!isFinish){
        pause();
    }
    char cmd[200];
    sprintf(cmd, "kill -9 %d %d", pid_P1, pid_P2);
    system(cmd);
    return 0;
}

void P1(){
    // Associated signal SIGUSR1
    while(1){
        sleep(rand()%3); // wait 0, 1, 2 or 3 seconds
        kill(getppid(), SIGUSR1);
    }
}

void P2(){
    // Associated signal SIGUSR2
    while(1){
        sleep(rand()%2); // wait 0, 1, 2
        kill(getppid(), SIGUSR2);
    }
}