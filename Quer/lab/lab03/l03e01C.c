#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/select.h>

#define WAIT_TIME_1 1
#define WAIT_TIME_2 2
#define STR_SIZE 5+1
#define NUM_STR 2

void randomString(char *s, int size, int seed);
void capitalize(char *s);

int main(){
    pid_t pid1,pid2;
    int p1[2],p2[2];

    if(pipe(p1)==0){
        pid1=fork();

        if(pid1==0){
            //C1
            
        }else{
            pid2=fork();

            if(pid2==0){
                //C2

            }else{
            //Father
            
            }
        }
    }else{
        fprintf(stderr,"Pipe failure");
        exit(EXIT_FAILURE);
    }


    return 0;
}

void randomString(char *s, int size, int seed){
    /*seed is an integer number that should be different for each process 
    * that call this funtion in order to generate different random string
    */
	char *charset="abcdefghijklmnopqrstuvwxyz";
	srand(seed);
	for(int i=0;i<(size-1);i++){
		s[i]=charset[rand()%strlen(charset)];
	}
	s[strlen(s)]='\0';
}

void capitalize(char *s){
	for(int i=0;i<strlen(s);i++){
		s[i]=s[i]-32;
	}
}