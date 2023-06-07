#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

FILE *fp;

void *READ(void *args){
    char *c = (char *)args;
    *c = fgetc(fp);
}
void *TRANSFORM(void *args){
    char *c = (char *)args;
    *c = toupper(*c);
}
void *PRINT(void *args){
    char *c = (char *)args;
    printf("%c",*c);
}

int main(int argc, char **argv) {
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    char next, this, last;

    if(argc!=2){
        fprintf(stderr,"Error, Wrong number of arguments");
        exit(1);
    }

    fp = fopen(argv[1],"r");

    next = ' ';
    this = ' ';
    last = ' ';

    while(next!=EOF){
        pthread_create(&t1,NULL,READ,&next);
        pthread_create(&t2,NULL,TRANSFORM,&this);
        pthread_create(&t3,NULL,PRINT,&last);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        pthread_join(t3,NULL);
        last = this;
        this = next;
    }
    fclose(fp);
    return 0;
}
