#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

 int get_line(int fd, int lineNr, char *line, int maxLength) {
    lseek(fd, 0, SEEK_SET);
    char c;
    int lineCounter = 0, pos = 0, lineLength = 0, i = 0;
    for(i = 0; i < maxLength; i++) {
        if(read(fd,&c,1) != 1) {
            printf("Eror in function get_line!\n");
            return -1;
        }

        if(c == '\n') {
            lineCounter++;

            if(lineCounter == lineNr) {
                break;
            }
            else {
                pos = lseek(fd, 0, SEEK_CUR);
            }
        }
    }

    if(i == maxLength)
        lineCounter++;

    if(lineCounter != lineNr) {
        return -1;
    }

    lineLength = lseek(fd, 0, SEEK_CUR) - pos;
    line = (char *) malloc(sizeof(char) * lineLength);
    lseek(fd, pos, SEEK_SET);

    for(int i = 0; i < lineLength; i++) {
        read(fd,&line[i],1);
    }

    printf("%s ", line);
    
    return 0;
 }

int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Command form ./l4p1 numefisier numar_linie\n");
        return 1;
    }


    int lineNr = 0;
    for(int i = 0; i < strlen(argv[2]); i++) {
        if(argv[2][i] >= '0' && argv[2][i] <= '9') {
            lineNr = lineNr * 10 + argv[2][i] - '0';
        }
        else {
            printf("Invalid line number\n");
            return 2;
        }
    }

    int fd = open(argv[1], O_RDONLY);

    if(fd == -1) {
        printf("Invalid file\n");
        return 3;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    char *line = NULL;
    
    if(get_line(fd, lineNr, line, size) >= 0) {
        if(line != NULL)
            printf("Linia este: \n%s", line);
    }

    return 0;   
}