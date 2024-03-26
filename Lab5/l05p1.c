#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct _list{
    int ino;
    struct _list *next;
}list;

list* create (int key) {
    list* node = (list*) malloc(sizeof(list));
    node->ino = key;
    node->next = NULL;

    return node;
}

void insert_first(list **first, int key) {
    if(*first == NULL) {
        *first = create(key);
        return;
    }

    list* node = create(key);
    node->next = *first;
    (*first) = node;
}

void free_list(list **first) {
    while(*first != NULL) {
        list* node = *first;
        *first = (*first)->next;
        free(node);
    }
}

list* is_key(list *first, int key) {
    for(list* i = first; i != NULL; i = i->next) {
        if(i->ino == key)
            return i;
    }

    return NULL;
}

off_t dirSize(const char* dirPath, list** list) {
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
                if(S_ISDIR(statbuf.st_mode)) {
                    size += dirSize(fullPath, list);
                }
                else if(statbuf.st_nlink == 0 || is_key(*list, statbuf.st_ino) == NULL) {
                    size += statbuf.st_size;
                    insert_first(list, statbuf.st_ino);
                }
            }
        }
    }

    closedir(dir);
    return size;
}

int main(int argc, char **argv) {
    if(argc >= 2) {
        list *first = NULL;
        printf("Size: %ld\n", dirSize(argv[1], &first));
        free_list(&first);
    }
    else {
        list *first = NULL;
        for(int i = 1; i <= 10; i++) {
            insert_first(&first, i);
        }

        for(list* i = first; i != NULL; i = i->next) {
            printf("%d ", i->ino);
        }

        list* node = is_key(first, 4);
        if(node != NULL)
            printf("\n%d\n", node->ino);

        free_list(&first);
    }
    return 0;
}