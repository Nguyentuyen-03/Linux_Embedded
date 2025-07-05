#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;
    if (lstat(argv[1], &file_stat) == -1) {
        perror("lstat failed");
        return 1;
    }

    //in thông tin cơ bản
    printf("File Path: %s\n", argv[1]);

    //in loại tệp
    printf("File Type: ");
    if (S_ISREG(file_stat.st_mode))
        printf("Regular File\n");
    else if (S_ISDIR(file_stat.st_mode))
        printf("Directory\n");
    else if (S_ISLNK(file_stat.st_mode))
        printf("Symbolic Link\n");
    else
        printf("Other\n");

        
    //in kích thước tệp
    printf("Size: %ld bytes\n", file_stat.st_size);

    char *mod_time = ctime(&file_stat.st_mtime);
    printf("Last Modified: %s", mod_time);

    return 0;
}
