#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define WAIT_TIME_1 1
#define WAIT_TIME_2 2
#define STR_SIZE 10+1
#define NUM_STR 3

void randomString(char *s, int size);
void capitalize(char *s);

int main(){
    pit_t pid1,pid2;
    int p1[2],p2[2];

    if(pipe(p1)==0 && pipe(p2)==0){
        //Pipes are initialized correctly
        pid1=fork(); //Generating of child C1

        if(pid1==0){
            //C1
            int count=0;			
			close(p1[0]); //Closing the read-end. C1 onli write on p1

			while(count<=NUM_STR){
                //Write NUM_STR on the pipe p1 every WAIT_TIME_1 secs
				char *s=(char*)malloc(STR_SIZE*sizeof(char));
				
                randomString(s,STR_SIZE);
				write(p1[1],s,STR_SIZE*sizeof(char)); //Blocking write
				free(s);
				
				count++;
				sleep(WAIT_TIME_1);
			}

        }else{
            //Parent of C1
            pid2=fork(); //Generating of child C2

            if(pid2==0){
                //C2

            }else{
                //Common parent P of C1 and C2
                //P must read with a non-blocking read in order to avoid starvation
                close(p1[1]);
				close(p2[1]);
                set_fnctl(p1[0],O_NONBLOCK); //p1 read-end is set as NON BLOCKING function
                int nToReadP1 = STR_SIZE;
                int nReadP1;
                char s1[STR_SIZE];
                char *s1_pointer;

                s1_pointer=s1;
                while(nToReadP1>0){
                    // Leggo

                    nReadP1 = read(p1,s1,STR_SIZE*sizeof(char));
                    
                    if(nReadP1>0){
                        
                    }
                }

            }
        }


    }else{
        //Error on inizializing pipes
        fprintf(stderr,"Pipe failure\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void randomString(char *s, int size){
	char *charset="abcdefghijklmnopqrstuvwxyz";
	srand(time(NULL));
	for(int i=0;i<size;i++){
		s[i]=charset[rand()%strlen(charset)];
	}
	s[strlen(s)]='\0';
}

void capitalize(char *s){
	for(int i=0;i<strlen(s);i++){
		s[i]=s[i]-32;
	}
}