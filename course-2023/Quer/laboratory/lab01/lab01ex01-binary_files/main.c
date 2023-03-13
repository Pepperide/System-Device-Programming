#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define N 31

struct Line{
    int line;
    long id;
    char surname[N];
    char name[N];
    int mark;
};
int main(int argc, char **argv) {
    FILE* fp1,*fp3;
    int fd2; // File descriptor in an integer if we are going to use standard POSIX
    struct Line l;
    int n_read,n_write;

    /* Checking the arguments from the CLI */
    if(argc!=4){
        fprintf(stderr,"Error, wrong parameters!");
        exit(1);
    }

    /* Read file_1 using standard C libraries */
    if((fp1 = fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"Error opening the first file");
        exit(1);
    }
    if((fd2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR))==-1){
        fprintf(stderr,"Error opening file_2");
        exit(1);
    }
    while(fscanf(fp1,"%d %ld %s %s %d",&l.line,&l.id,l.surname,l.name,&l.mark)!=EOF){
        /* Write data on the second file by using standard POSIX */
        n_write = write(fd2,&l,sizeof(struct Line));
        printf("Written: %d bytes\n",n_write);
        if(n_write == -1){
            fprintf(stderr,"Error writing the file");
            exit(1);
        }
    }
    close(fd2);
    fclose(fp1);

    /* Reading of file_2 and restore the information in file_3 */
    if((fd2 = open(argv[2],O_RDONLY))==-1){
        fprintf(stderr,"Error opening file_2");
        exit(1);
    }
    if((fp3= fopen(argv[3],"w"))==NULL){
        fprintf(stderr,"Error opening the third file");
        exit(1);
    }
    /* The new file will differ from the first one by a \n at the end*/
    while((n_read = read(fd2,&l,sizeof(struct Line)))>0){
        fprintf(fp3,"%d %ld %s %s %d\n",l.line,l.id,l.surname,l.name,l.mark);
    }
    fclose(fp3);
    close(fd2);
    return 0;
}
