#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <time.h>

void P1(int *p1p2, int *p2p1){
    int n=-1;
    char *text;
    char charset[28];
    char ok;

    // Init the charset
    for(int i=0;i<26;i++)
        charset[i] = i + 97;
    charset[26]=' ';
    charset[27]='\n';

    close(p1p2[0]); // close the read end of the pipe from p1 to p2
    close(p2p1[1]); // close the write end of the pipe from p2 to p1

    while(n!=0){
        sleep(2);
        n = rand()%10;
        text = (char *)malloc(n *sizeof(char));

        for(int i=0; i<n; i++)
            text[i] = charset[rand()%28];

        // Wake up P2
        write(p1p2[1],&n,sizeof(int));

        // Wait for P2 response
        read(p2p1[0],&ok,sizeof(char));

        // Send message
        write(p1p2[1], text, n* sizeof(char));
        printf("P1 - Message sent: %s\n", text);

        // Wait for P2 message
        read(p2p1[0],text,n * sizeof(char));
        printf("P1 - Message received: %s\n", text);

        free(text);
    }
}

void P2(int *p1p2, int *p2p1){
    char *text;
    int n=-1;

    close(p1p2[1]); // close the write end of the pipe from p1 to p2
    close(p2p1[0]); // close the read end of the pipe from p2 to p1

    while(n!=0){
        sleep(1);
        // Wait for P1 data
        read(p1p2[0],&n,sizeof(int));
        text = (char *)malloc(n * sizeof(char));

        // Signal to P1 that P2 is ready for the text
        write(p2p1[1],"o", sizeof(char));

        // Wait for text message from P1
        read(p1p2[0],text,n * sizeof(char));
        printf("P2 - Message received: %s\n", text);
        for(int i=0;i<n;i++)
            text[i] = toupper(text[i]);

        //Send the new message to P1
        write(p2p1[1],text, n* sizeof(char));
        printf("P2 - Message sent: %s\n", text);

        free(text);
    }
}

int main() {
    int fd_P1P2[2], fd_P2P1[2];
    pid_t pid1, pid2;

    // Init pipe fro process communication
    if(pipe(fd_P1P2) == -1 || pipe(fd_P2P1)== -1 ){
        fprintf(stderr, "Error! Unable to create the pipe!\n");
        exit(1);
    }

    srand(time(NULL));
    pid1 = fork();
    if(pid1==0){
        // Process P1
        P1(fd_P1P2,fd_P2P1);
    }else{
        pid2 = fork();
        if(pid2 == 0){
            // Process P2
            P2(fd_P1P2,fd_P2P1);
        }else{
            // Main Process
            // Waits for child process termination
            if(wait(NULL) ==-1){
                fprintf(stderr, "Error! Unable to wait a process termination\n");
                exit(1);
            }
            if(wait(NULL) ==-1){
                fprintf(stderr, "Error! Unable to wait a process termination\n");
                exit(1);
            }
        }
    }
    return 0;
}
