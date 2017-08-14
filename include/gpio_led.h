#ifndef __GPIO_LED_H__
#define __GPIO_LED_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#define GPIO_COUNT 8
#define GPIO_LED_1     44
#define GPIO_LED_2     45
#define GPIO_LED_3     46
#define GPIO_LED_4     47
#define GPIO_LED_5     110
#define GPIO_LED_6     111
#define GPIO_LED_7     112
#define GPIO_LED_8     113

using namespace std;

namespace GPIO {

    class GPIO_LED
    {

    public:
        int u_sleep_time;
        int all_led_time;
        char buf[128] = {0};
        int pin_map[GPIO_COUNT] = {
            GPIO_LED_1, 
            GPIO_LED_2, 
            GPIO_LED_3, 
            GPIO_LED_4, 
            GPIO_LED_5, 
            GPIO_LED_6, 
            GPIO_LED_7, 
            GPIO_LED_8
        };

        GPIO_LED() {
            this->u_sleep_time = 200000;
            this->all_led_time = 2000000;
        }

        bool file_directory_exist(char* buf) {
            if (access(buf, F_OK) == 0) 
                return true; 
            else
                return false;
        }

        void init() {
            int i = 0;
            for (; i < GPIO_COUNT; i++) {
                _export(pin_map[i]);
                output(pin_map[i]);
            }
        }

        void release() {
            int i = 0;
            for (; i < GPIO_COUNT; i++) 
                un_export(pin_map[i]);

        }

        void _export(int pin_number) {
            bzero(buf, sizeof(buf));
            sprintf(buf, "/sys/class/gpio/gpio%d", pin_number);
            if (file_directory_exist(buf))
                return ;

            bzero(buf, sizeof(buf));
            sprintf(buf, "echo %d > /sys/class/gpio/export", pin_number);
            system(buf);
        }

        void un_export(int pin_number) {
            bzero(buf, sizeof(buf));
            sprintf(buf, "/sys/class/gpio/gpio%d", pin_number);
            if (!file_directory_exist(buf))
                return ;

            bzero(buf, sizeof(buf));
            sprintf(buf, "echo %d > /sys/class/gpio/unexport", pin_number);
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

            for (; i < GPIO_COUNT + 1; i++) {
                usleep(u_sleep_time);
                
                if (i != 0) 
                    set_value(pin_map[i - 1], 0);

                if (i != GPIO_COUNT)
                    set_value(pin_map[i], 1);
            }
        }

        void right_to_left() {
            int i = 0;

            for (; i < GPIO_COUNT + 1; i++) {
                usleep(u_sleep_time);
                
                if (i != 0) 
                    set_value(pin_map[GPIO_COUNT - i], 0);

                if (i != GPIO_COUNT) 
                    set_value(pin_map[(GPIO_COUNT - 1) - i], 1);
            }
        }

        void all_light() {
            int i = 0;
            for (; i < GPIO_COUNT; i++) 
                set_value(pin_map[i], 1);
        }
    };

}

#endif /* __GPIO_LED_H__ */
