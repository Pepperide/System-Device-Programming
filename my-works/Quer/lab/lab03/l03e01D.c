/*
*   lab03 es 01 Version D: Asynchronous I/O
*
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <aio.h>

#define WAIT_TIME_1 1
#define WAIT_TIME_2 2
#define STR_SIZE 5+1
#define NUM_STR 2

void randomString(char *s, int size, int seed);
void capitalize(char *s);

int main(){
    pid_t pid1,pid2;
    int p1[2],p2[2];

    if(pipe(p1)==0 && pipe(p2)==0){
        pid1=fork();

        if(pid1==0){
            //C1
            int count=0;			
			close(p1[0]); //Closing the read-end. C1 only write on p1

			while(count<NUM_STR){
                //Write NUM_STR on the pipe p1 every WAIT_TIME_1 secs
				char *s1=(char*)malloc(STR_SIZE*sizeof(char));
				
                randomString(s1,STR_SIZE,count+100);
                //printf("String C1: %s\n",s1);
				write(p1[1],s1,STR_SIZE*sizeof(char)); //Blocking write
				free(s1);
				
				count++;
				sleep(WAIT_TIME_1);
			}
            printf("terminato C1\n");
            
        }else{
            pid2=fork();

            if(pid2==0){
                //C2
                int count=0;			
			    close(p2[0]); //Closing the read-end. C2 only write on p2

			    while(count<NUM_STR){
                    //Write NUM_STR on the pipe p2 every WAIT_TIME_2 secs
				    char *s=(char*)malloc(STR_SIZE*sizeof(char));

                    randomString(s,STR_SIZE,count+50);
                    //printf("String C2: %s\n",s);
				    write(p2[1],s,STR_SIZE*sizeof(char)); //Blocking write
				    free(s);
				
				    count++;
				    sleep(WAIT_TIME_2);
			    }
                printf("terminato C2\n");

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