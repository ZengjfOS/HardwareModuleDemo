#ifndef __GPIO_LED_H__
#define __GPIO_LED_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

class GPIO_LED
{

public:
    int u_sleep_time;
    int all_led_time;
    char buf[128] = {0};
    int pin_map[8] = {44, 45, 46, 47, 110, 111, 112, 113};

    void GPIO() {
        this->u_sleep_time = 200000;
        this->all_led_time = 2000000;
    }

    void init() {
        int i = 0;
        for (; i < sizeof(pin_map); i++) {
            _export(pin_map[i]);
            output(pin_map[i]);
        }
    }

    void release() {
        int i = 0;
        for (; i < sizeof(pin_map); i++) 
            un_export(pin_map[i]);
    }

    void _export(int pin_number) {
        bzero(buf, sizeof(buf));
        sprintf(buf, "echo %d > /sys/class/gpio/_export", pin_number);
        system(buf);
    }

    void un_export(int pin_number) {
        bzero(buf, sizeof(buf));
        sprintf(buf, "echo %d > /sys/class/gpio/un_export", pin_number);
        system(buf);
    }

    void output(int pin_number) {
        bzero(buf, sizeof(buf));
        sprintf(buf, "echo out > /sys/class/gpio/gpio%d/direction", pin_number);
        system(buf);
    }

    void set_value(int pin_number, int value) {
        bzero(buf, sizeof(buf));
        sprintf(buf, "echo %d > /sys/class/gpio/gpio%d/value", value, pin_number);
        system(buf);
    }

    void left_to_right() {
        int i = 0;

        for (; i < sizeof(pin_map) + 1; i++) {
            usleep(u_sleep_time);
            
            if (i != 0) 
                set_value(pin_map[i - 1], 0);

            if (i != (sizeof(pin_map) - 1)) 
                set_value(pin_map[i], 1);
        }
    }

    void right_to_left() {
        int i = 0;

        for (; i < sizeof(pin_map) + 1; i++) {
            usleep(u_sleep_time);
            
            if (i != 0) 
                set_value(pin_map[sizeof(pin_map) - i], 0);

            if (i != (sizeof(pin_map) - 1)) 
                set_value(pin_map[(sizeof(pin_map) - 1) - i], 1);
        }
    }

    void all_light() {
        int i = 0;
        for (; i < sizeof(pin_map); i++) 
            set_value(pin_map[i], 1);
    }
};

#endif /* __GPIO_LED_H__ */
