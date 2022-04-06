/*
*   Lab03 exercise 01 version non blocking I/O
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>

#define WAIT_TIME_1 1
#define WAIT_TIME_2 2
#define STR_SIZE 5+1
#define NUM_STR 2

void randomString(char *s, int size, int seed);
void capitalize(char *s);
void set_fcntl(int fd,int flags);
void clr_fcntl(int fd, int flags);

int main(){
    pid_t pid1,pid2;
    int p1[2],p2[2];

    if(pipe(p1)==0 && pipe(p2)==0){
        //Pipes are initialized correctly
        pid1=fork(); //Generating of child C1

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
            //Parent of C1
            pid2=fork(); //Generating of child C2

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
                //Common parent P of C1 and C2
                //P must read with a non-blocking read in order to avoid starvation
                close(p1[1]);
				close(p2[1]);
                set_fcntl(p1[0],O_NONBLOCK); //p1 read-end is set as NON BLOCKING function
                set_fcntl(p2[0],O_NONBLOCK); //p1 read-end is set as NON BLOCKING function
                int nToReadP1, nToReadP2;
                int nReadP1, nReadP2;
                char s1[STR_SIZE];
                char s2[STR_SIZE];
                char *s1_pointer;
                char *s2_pointer;

                s1_pointer=s1;
                s2_pointer=s2;

                for(int i=0;i<NUM_STR;i++){
                    nToReadP1=STR_SIZE * sizeof(char);
                    nToReadP2=STR_SIZE * sizeof(char);
                    while(nToReadP1>0 || nToReadP2>0){
                        // Leggo

                        nReadP1 = read(p1[0],s1_pointer,STR_SIZE*sizeof(char));
                        nReadP2 = read(p2[0],s2_pointer,STR_SIZE*sizeof(char));
                        
                        //fprintf(stdout,"Bytes read from C1 = %d\n",nReadP1);
                        //fprintf(stdout,"Bytes read from C2 = %d\n",nReadP2);
                        
                        if(nReadP1>0){
                            s1_pointer += nReadP1;
                            nToReadP1 -= nReadP1;  
                        }
                        if(nReadP2>0){
                            s2_pointer += nReadP2;
                            nToReadP2 -= nReadP2;  
                        }

                        if(nReadP1>0 && nToReadP1<=0){
                            capitalize(s1);
                            fprintf(stdout,"From C1: %s\n",s1);
                        }
                        if(nReadP2>0 && nToReadP2<=0){
                            capitalize(s2);
                            fprintf(stdout,"From C2: %s\n",s2);
                        }
                    }
                    s1_pointer-=STR_SIZE * sizeof(char);
                    s2_pointer-=STR_SIZE * sizeof(char);
                }
                clr_fcntl(p1[0],O_NONBLOCK);
                clr_fcntl(p2[0],O_NONBLOCK);
                
                waitpid(pid1,(int *)0,0);
                waitpid(pid2,(int *)0,0);
            }
        }


    }else{
        //Error on inizializing pipes
        fprintf(stderr,"Pipe failure\n");
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

void set_fcntl(int fd,int flags){
    int val;
    if((val=fcntl(fd,F_GETFL,0))<0){
        fprintf(stderr,"fnclt failure: Unable to get flags\n");
        exit(EXIT_FAILURE);
    }

    val|=flags;

    if(fcntl(fd,F_SETFL,val)<0){
        fprintf(stderr,"fnclt failure: Unable to set flags\n");
        exit(EXIT_FAILURE);
    }

}

void clr_fcntl(int fd, int flags){
    int val;
    if((val=fcntl(fd,F_GETFL,0))<0){
        fprintf(stderr,"fnclt failure: Unable to get flags\n");
        exit(EXIT_FAILURE);
    }

    val&= ~flags;

    if(fcntl(fd,F_SETFL,val)<0){
        fprintf(stderr,"fnclt failure: Unable to set flags\n");
        exit(EXIT_FAILURE);
    }
}