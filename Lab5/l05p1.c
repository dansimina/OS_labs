#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

off_t dirSize(const char* dirPath) {
    off_t size = 0;

    DIR* dir = NULL;
    struct dirent *entry = NULL;
    struct stat statbuf;
    char fullPath[1024];

    dir = opendir(dirPath);
    if(dir == NULL) {
        printf("Could not open the directory");
        return 0;
    }

    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(fullPath, 1024, "%s/%s", dirPath, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0) {
                if(S_ISREG(statbuf.st_mode)) {
                    size += statbuf.st_size; 
                }
                else if(S_ISDIR(statbuf.st_mode)) {
                    size += dirSize(fullPath);
                }
            }
        }
    }

    closedir(dir);
    return size;
}

int main(int argc, char **argv) {
    if(argc >= 2) {
        printf("Size: %ld\n", dirSize(argv[1]));
    }
    return 0;
}