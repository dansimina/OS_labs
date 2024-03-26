#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


void listRec(const char *path, const char *string, const char *original_path, int *cnt)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    char fullPath[512];
    struct stat statbuf;

    dir = opendir(path);
    if(dir == NULL) {
        perror("Could not open directory");
        return;
    }
    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(fullPath, 512, "%s/%s", path, entry->d_name);
            if(lstat(fullPath, &statbuf) == 0) {
                if(S_ISDIR(statbuf.st_mode)) {
                    listRec(fullPath, string, original_path, cnt);
                }
                else if(S_ISREG(statbuf.st_mode)) {
                    int fd = open(fullPath, O_RDONLY);
                    if(fd != -1) {
                        char buf[4096];
                        int size = lseek(fd, 0, SEEK_END);
                        
                        lseek(fd, 0, SEEK_SET);
                        read(fd, buf, size);

                        buf[size + 1] = 0;

                        if(strstr(buf, string) != NULL) {
                            char linkPath[512];
                            (*cnt)++;
                            snprintf(linkPath, 512, "%s/found.%d", original_path, *cnt);
                            link(fullPath, linkPath);
                        }

                        close(fd);
                    }
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char **argv)
{
    if(argc < 3) {
        fprintf(stderr, "ERROR");
        return 1;
    }
    int cnt = 0;
    listRec(argv[1], argv[2], argv[1], &cnt);
    return 0;
}