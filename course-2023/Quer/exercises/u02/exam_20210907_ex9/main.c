#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    int pid;
    char line[200];

    // Pipe initialization. Both processes must share the same pipe
    pipe(fd);
    pid= fork();

    if(pid==0){
        //Child
        //It passes to the parent process a strung from the command line
        close(fd[0]); // Close the read end of the pipe
        while(1){
            scanf("%s", line);
            write(fd[1],line, (strlen(line)+1)* sizeof(char));
        }
    }
    else{
        // Father
        // It prints the received strings and print out them to the screen
        close(fd[1]); //Close the write end of the screen
        while(1){
            read(fd[0],line,200* sizeof(char ));
            printf("%s\n",line);
        }
    }
    return 0;
}
