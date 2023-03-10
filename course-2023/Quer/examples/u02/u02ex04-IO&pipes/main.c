#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define N 132

void p1(int p_read,int p_write, char* filename);
void p2(int p_read,int p_write,  char* filename);
void read_file(char *name,char *filename);
void write_file(char* name, char *filename);

int main(int argc, char **argv) {
    int p12[2],p21[2]; //pipe
    int pid;
    int fd;

    pipe(p12);
    pipe(p21);
    pid=fork();

    if(pid==0){
        close(p12[0]);
        close(p21[1]);
        p1(p21[0],p12[1],argv[1]);

    }else{
        close(p12[1]);
        close(p21[0]);
        p2(p12[0],p21[1],argv[1]);
    }

    return 0;
}

void p1(int p_read,int p_write, char* filename){
    char c;

    while(1){
        printf("P1 write\n");
        write_file("P1",filename);
        write(p_write,&c,sizeof(char)); // Allows P2 to access the file
        read(p_read,&c,sizeof(char));
        printf("P1 read\n");
        read_file("P1",filename);
    }
}

void p2(int p_read,int p_write,  char* filename){
    char c;

    while(1){
        read(p_read,&c,sizeof(char));
        printf("P2 read\n");
        read_file("P2",filename);

        printf("P2 write\n");
        write_file("P2",filename);
        write(p_write,&c,sizeof(char)); // Allows P2 to access the file
    }
}

void read_file(char *name,char *filename){
    FILE* fp;
    char str[N];

    fp = fopen(filename,"r");
    while(fscanf(fp,"%s",str)!=EOF){
        if(strcmp(str,"end")==0 || strcmp(str,"END")==0)
            printf("\t%s\n",str);
        else
            printf("%s\n",str);
    }
    fclose(fp);
    return;
}

void write_file(char* name, char *filename){
    FILE* fp;
    char str[N];

    fp= fopen(filename,"w");
    do{
        scanf("%s",str);

        fprintf(fp,"%s\n",str);
    }while(strcmp(str,"end")!=0 && strcmp(str,"END")!=0);

    fclose(fp);
    return;
}