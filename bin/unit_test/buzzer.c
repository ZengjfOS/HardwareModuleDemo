#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUZZER_DEV_NAME "/dev/buzzer"


int main(int argc, char** argv) {

    int buzzer_fd = open(argv[1], O_RDWR|O_NOCTTY|O_NDELAY);
    if (buzzer_fd < 0)
    {
        perror("open device node error.");
        return -1;
    }

    int frq = 2000;
    if (argc == 3) {
        frq = atoi(argv[2]);
    }

    int i = 0;
    for (i; i < 3; i++) {
        ioctl(buzzer_fd, 1, frq * (i + 1));
        sleep(1);
    }

    close(buzzer_fd);
}

