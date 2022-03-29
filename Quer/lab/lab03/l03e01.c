/*
A parent process P generates two children processes C1 and C2.
C1 and P communicate through a pipe p1 and C2 and P communicate
through a pipe p2.
- Process C1:
  every WAIT_TIME_1 seconds generates a string of STR_SIZE small alphabetic
  letters and write it into pipe p1.
  Overall C1 generates and writes on pipe p1, STR_NUM strings.
- Process C2:
  does the same things done by C1 but it waits for WAIT_TIME_2
  seconds, and it writes the strings into pipe p2.
- Process P:
  reads the strings coming from the two pipes (p1 and p2), converts
  them in capital letters, and displays them on standard output.
Note that WAIT_TIME_1, WAIT_TIME_2, STR_NUM, and STR_SIZE are predefined
constant values.
Strings are randomly generated (composed by only small alphabetic
letters).
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WAIT_TIME_1 1
#define WAIT_TIME_2 2
#define STR_SIZE 10+1
#define NUM_STR 10

void randomString(char *s, int size);
void capitalize(char *s);
int main(){
	int n;
	int p1[2], p2[2];
	pid_t pid1,pid2;

	//Starting pipe for C1
	if( pipe(p1) == 0){
		pid1=fork();
		if(pid1==-1){
			fprintf(stderr,"Fork failure");
			exit(EXIT_FAILURE);
		}

		if(pid1==0){
			//Child C1 writes on p1
			//Child has pipe p1 shared among his father
			//(But also p2 but he never use it)
			int count=0;
			
			close(p1[0]); //Closing the read-end. C1 onli write on p1
			while(count<=NUM_STR){
				sleep(WAIT_TIME_1);
				char *s=(char*)malloc(STR_SIZE*sizeof(char));
				randomString(s,STR_SIZE);
				n = write(p1[1],s,STR_SIZE*sizeof(char));
				printf("scritti %d bytes\n",n);
				free(s);
				
				count++;
			}

		}else{
			//Parent reads string and capitalize letters
			close(p1[1]);
			
			for(int i=0;i<NUM_STR;i++){
				char *s=(char*)malloc(STR_SIZE*sizeof(char));				
				n = read(p1[0],s,STR_SIZE*sizeof(char));
				capitalize(s);
				printf("%s\n",s);
				free(s);
			}		
		}
	}
}

void randomString(char *s, int size){
	int i;
	char *charset="abcdefghijklmnopqrstuvwxyz";
	char c;
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