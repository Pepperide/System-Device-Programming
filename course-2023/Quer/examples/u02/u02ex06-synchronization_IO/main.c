#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void *sum(void * arg);

struct threadData{
    FILE* fp;
    int sum;
    int line;
    int id;
};

sem_t sem;
int main(int argc, char** argv) {
    int n,total=0,lines=0;
    pthread_t *threads;
    struct threadData *td;
    FILE* fp;

    if(argc!=3){
        printf("Error, wrong parameters");
        exit(1);
    }
    n=atoi(argv[1]);
    fp = fopen(argv[2],"r"); //File pointer must be shared among all the thread. It must be unique

    if(fp==NULL){
        fprintf(stderr,"Error opening the file");
        exit(1);
    }
    threads= (pthread_t *)malloc(n * sizeof (pthread_t));
    td = (struct threadData *)malloc(n * sizeof(struct threadData));
    sem_init(&sem,0,1);

    for(int i=0;i<n;i++){
        td[i].id =  i;
        td[i].sum = 0;
        td[i].line = 0;
        td[i].fp = fp;
        pthread_create(&threads[i],NULL,sum,(void *)&td[i]);
    }

    for(int i=0;i<n;i++){
        pthread_join(threads[i],NULL);
        total+=td[i].sum;
        lines+=td[i].line;
    }
    fprintf(stdout,"Total: Sum=%d #Line=%d\n",total,lines);

    sem_destroy(&sem);
    fclose(fp);
    free(threads);
    free(td);
    return 0;
}

void *sum(void * arg){
    struct threadData *td;
    int r,ret;
    td=(struct threadData *) arg;

    do{
        sem_wait(&sem);
        ret=fscanf(td->fp,"%d",&r);
        sem_post(&sem);
        if(ret!=EOF){
            td->sum+=r;
            td->line ++;
        }
    }while(ret != EOF);
    fprintf(stdout,"Thread %d: Sum=%d #Line=%d\n",td->id,td->sum,td->line);
    pthread_exit((void *)1);
}