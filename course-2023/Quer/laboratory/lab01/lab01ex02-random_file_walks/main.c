#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct Record{
    int line;
    long id;
    char name[31];
    char surname[31];
    int mark;
};

int main(int argc, char** argv) {
    char cmd;
    int row;
    int fd;
    off_t off, end_of_file;
    struct Record record;

    fd = open(argv[1], O_RDWR | O_CREAT);
    end_of_file = lseek(fd,0,SEEK_END); //Current end of the file
    do{
        printf("> ");
        scanf("\n%c",&cmd);
        
        if(cmd!='E'){
            lseek(0,1*sizeof(char),SEEK_CUR); // Set the stdout cursor back to the correct position
            scanf("%d",&row);
        }

        off = (row-1) * sizeof(struct Record);

        switch(cmd){
            case 'R':
                if(off < end_of_file){
                    lseek(fd,off,SEEK_SET);
                    read(fd,&record,sizeof(struct Record));
                    printf("%d %ld %s %s %d\n",record.line,record.id,record.name,record.surname,record.mark);
                }
                else{
                    printf("Record is not present. Last record is #%ld\n",end_of_file / sizeof(struct Record));
                }
                break;
            case 'W':
                printf("Data: ");
                scanf("%d %ld %s %s %d",&record.line,&record.id,record.name,record.surname,&record.mark);
                if(off < end_of_file)
                    lseek(fd,off,SEEK_SET);
                else
                    lseek(fd,0,SEEK_END);

                write(fd,&record,sizeof(struct Record));
                end_of_file = lseek(fd,0,SEEK_END); // Update end of the file
                break;
            case 'E':
                break;
            default:
                printf("Command not implemented\n");
                break;
        }
    }while(cmd!='E');

    return 0;
}
