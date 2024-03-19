#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Command form ./l4p1 nume_fisier_sursa nume_fisier_destinatie\n");
        return 1;
    }

    int fdFirstFile = open(argv[1], O_RDONLY);
    int fdSecondFile = open(argv[2], O_WRONLY);

    if(fdFirstFile == -1 || fdSecondFile == -1) {
        printf("Invalid file\n");
        return 3;
    }

    off_t size = lseek(fdFirstFile, 0, SEEK_END);
    
    for(int i = 0; i < size; i++) {
        char c;
        lseek(fdFirstFile, size - i - 1, SEEK_SET);
        if(read(fdFirstFile, &c, 1) != 1) {
            printf("Reading error\n");
            return 4;
        }

        if(write(fdSecondFile, &c, 1) != 1) {
            printf("Writing error\n");
            return 5;
        }
    }

    return 0;   
}