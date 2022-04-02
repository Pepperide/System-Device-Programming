/*
*   Lab03 exercise 01 version I/O Multiplexing
*/
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
                fd_set readSet;
                int nToReadP1,nToReadP2;
                int nReadP1, nReadP2;
                char s1[STR_SIZE], s2[STR_SIZE];
                char *s1_pointer,*s2_pointer;
                struct timeval tvptr;

                tvptr.tv_sec=0;
                tvptr.tv_usec=0;
                close(p1[1]);
			    close(p2[1]);
                

                FD_ZERO(&readSet); // Put all bit to zero of the read set

                s1_pointer=s1;
                s2_pointer=s2;
                for(int i=0;i<NUM_STR;i++){
                    nToReadP1=STR_SIZE * sizeof(char);
                    nToReadP2=STR_SIZE * sizeof(char);
                    FD_SET(p1[0],&readSet); // Set the corresponding bit of p1[0]
                    FD_SET(p2[0],&readSet); // Set the corresponding bit of p2[0]
                    
                    while(nToReadP1>0 || nToReadP2>0){                       
                        if(select(FD_SETSIZE,&readSet,NULL,NULL,&tvptr)>0){
                            if(FD_ISSET(p1[0],&readSet)){
                                //P1[0] can be read
                                nReadP1 = read(p1[0],s1_pointer,STR_SIZE*sizeof(char));
                                s1_pointer+=nReadP1;
                                nToReadP1-=nReadP1;
                                
                                if(nToReadP1<=0){
                                    capitalize(s1);
                                    fprintf(stdout,"From C1: %s\n",s1);
                                    FD_CLR(p1[0],&readSet);
                                }
                            }
                            else if(FD_ISSET(p2[0],&readSet)){
                                //P1[0] can be read
                                nReadP2 = read(p2[0],s2_pointer,STR_SIZE*sizeof(char));
                                s2_pointer+=nReadP2;
                                nToReadP2-=nReadP2;

                                if(nToReadP2<=0){
                                    capitalize(s2);
                                    fprintf(stdout,"From C2: %s\n",s2);
                                    FD_CLR(p2[0],&readSet);
                                }
                            }
                        }

                    }
                    s1_pointer-=STR_SIZE*sizeof(char);
                    s2_pointer-=STR_SIZE*sizeof(char);
                }
                
                waitpid(pid1,(int *)0,0);
                waitpid(pid2,(int *)0,0);
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