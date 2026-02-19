#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    int fd;
    char *myfifo = "/tmp/myfifo";
    int received_numbers[4];
    fd = open(myfifo, O_RDONLY);
    read(fd, received_numbers, sizeof(received_numbers));
    printf("Consumer: Received the following integers:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d ", received_numbers[i]);
    }
    printf("\n");
    close(fd);
    unlink(myfifo);
    return 0;
}