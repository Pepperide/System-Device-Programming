#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void p1(int p_read, int p_write);
void p2(int p_read, int p_write);
void p3(int p_read, int p_write);

int main() {
    int p12[2], p23[2], p31[2]; // p[0] used for reading, p[1] used for writing
    int pid1, pid2;
    char cmd[200];

    /* Before creating processes we have to set up the pipes */
    setbuf(stdout,0); // To avoid buffering on stdout
    pipe(p12);
    pipe(p23);
    pipe(p31);

    /* Create the three processes and assign the proper end of the pipe*/
    pid1 = fork();
    if(pid1==0){
        /* It's a best practice to close the unused end of each pipe*/
        close(p12[0]);
        close(p23[0]);
        close(p23[1]);
        close(p31[1]);

        p1(p31[0],p12[1]);
    }else{
        pid2=fork();
        if(pid2==0){
            close(p12[1]);
            close(p23[0]);
            close(p31[0]);
            close(p31[1]);
            p2(p12[0],p23[1]);
        }else{
            close(p12[0]);
            close(p12[1]);
            close(p23[1]);
            close(p31[0]);
            p3(p23[0],p31[1]);

        }
    }
    return 0;
}

void p1(int p_read, int p_write){
    int n;
    n=0; // Initial value just for the first iteration

    /* First process must read from stdin an integer value which corresponds to number of seconds to sleep */
    while(1){
        fprintf(stdout,"P1 waiting: %d seconds\n",n);
        sleep(n);
        fprintf(stdout,"P1 reading: ");
        scanf("%d",&n);
        /* P1 first must write to the pipe and then read */
        write(p_write,&n,sizeof(int));
        read(p_read,&n,sizeof(int)); // read() is a blocking function
    }
    return;
}

void p2(int p_read, int p_write){
    int n;
    while(1){
        read(p_read,&n,sizeof(int));
        fprintf(stdout,"P2 waiting: %d seconds\n",n);
        sleep(n);
        fprintf(stdout,"P2 reading: ");
        scanf("%d",&n);
        write(p_write,&n,sizeof(int));
    }
    return;
}

void p3(int p_read, int p_write){
    int n;
    while(1){
        read(p_read,&n,sizeof(int));
        fprintf(stdout,"P3 waiting: %d seconds\n",n);
        sleep(n);
        fprintf(stdout,"P3 reading: ");
        scanf("%d",&n);
        write(p_write,&n,sizeof(int));
    }
    return;
}