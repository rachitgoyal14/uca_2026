#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {

    struct stat fileInfo;

    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &fileInfo) != 0) {
        perror("stat");
        return 1;
    }

    printf("=== File Attributes for: %s ===\n", argv[1]);

    // File type
    if (S_ISREG(fileInfo.st_mode))
        printf("File Type:            Regular File\n");
    else if (S_ISDIR(fileInfo.st_mode))
        printf("File Type:            Directory\n");
    else if (S_ISLNK(fileInfo.st_mode))
        printf("File Type:            Symbolic Link\n");
    else if (S_ISCHR(fileInfo.st_mode))
        printf("File Type:            Character Device\n");
    else if (S_ISBLK(fileInfo.st_mode))
        printf("File Type:            Block Device\n");
    else if (S_ISFIFO(fileInfo.st_mode))
        printf("File Type:            FIFO/Pipe\n");
    else if (S_ISSOCK(fileInfo.st_mode))
        printf("File Type:            Socket\n");
    else
        printf("File Type:            Unknown\n");

    printf("Permissions:          %04o\n", fileInfo.st_mode & 0777);
    printf("File Size:            %lld bytes\n", (long long)fileInfo.st_size);
    printf("Hard Links Count:     %lld\n", (long long)fileInfo.st_nlink);
    printf("Owner (UID):          %u\n", fileInfo.st_uid);
    printf("Group (GID):          %u\n", fileInfo.st_gid);

    printf("Last Access Time:     %s", ctime(&fileInfo.st_atime));
    printf("Last Modification:    %s", ctime(&fileInfo.st_mtime));
    printf("Status Change Time:   %s", ctime(&fileInfo.st_ctime));

    return 0;
}
