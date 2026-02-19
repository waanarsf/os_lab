#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    int fd;
    char *myfifo = "/tmp/myfifo";
    int numbers[4];
    mkfifo(myfifo, 0666);
    printf("Producer: Enter 4 integers:\n");
    for(int i = 0; i < 4; i++) {
        scanf("%d", &numbers[i]);
    }
    fd = open(myfifo, O_WRONLY);
        write(fd, numbers, sizeof(numbers));
    printf("Producer: Data sent to FIFO.\n");
    close(fd);
    return 0;
}