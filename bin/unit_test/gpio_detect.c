#include "gpio.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int gpio_relay[] = {
    RELAY_R,
    RELAY_Y,  
    RELAY_G,  
    RELAY_STOP,
    SENSOROUT1,
    SENSOROUT2,
    SENSOROUT3
};

int gpio_input_output[] = {
    GPIO_24,
    GPIO_25,
    GPIO_26,
    GPIO_27,
    GPIO_28,
    GPIO_29,
    GPIO_30,
    GPIO_31
};

int main(int argc, char** argv) {


    if (argc < 4 ) {
        printf(" gpio <type> <gpio number> <value> \r\n \
        type = relay \r\n \
            0 = RELAY_R, \r\n \
            1 = RELAY_Y, \r\n \
            2 = RELAY_G, \r\n  \
            3 = RELAY_STOP, \r\n \
            4 = SENSOROUT1, \r\n \
            5 = SENSOROUT2, \r\n \
            6 = SENSOROUT3 \r\n \
        type = io\r\n \
            0 = GPIO_OUT1 = GPIO_24, \r\n \
            1 = GPIO_OUT2 = GPIO_25, \r\n \
            2 = GPIO_OUT3 = GPIO_26, \r\n \
            3 = GPIO_OUT4 = GPIO_27, \r\n \
            4 = GPIO_IN1 = GPIO_28, \r\n \
            5 = GPIO_IN2 = GPIO_29, \r\n \
            6 = GPIO_IN3 = GPIO_30, \r\n \
            7 = GPIO_IN4 = GPIO_31  \r\n \
                    "
        );

        return -1;
    }

            
    int gpio_fd = 0;

    gpio_fd = open(GPIO_DEV_NAME, O_RDWR|O_NOCTTY|O_NDELAY);
    if (gpio_fd < 0)
    {
        perror("open device node error.");
        return -1;
    }

    int value;
    if (strcmp(argv[1], "relay") == 0) {
        gpio_output(gpio_fd, gpio_relay[atoi(argv[2])], atoi(argv[3]));

        sleep(1);

        gpio_get_value(gpio_fd, DIS_IN1, &value);
        printf("TY_IN+ DIS_IN1 value: %d.\r\n", value);
        gpio_get_value(gpio_fd, DIS_IN3, &value);
        printf("FN_IN DIS_IN3 value: %d.\r\n", value);

    } else if (strcmp(argv[1], "io") == 0) {
        gpio_output(gpio_fd, gpio_input_output[atoi(argv[2])], atoi(argv[3]));
        sleep(1);
        int value;
        gpio_input(gpio_fd, gpio_input_output[atoi(argv[2]) + 4]);
        gpio_get_value(gpio_fd, gpio_input_output[atoi(argv[2]) + 4], &value);
        printf("GPIO Input value: %d.\r\n", value);
    }

    close(gpio_fd);
}

