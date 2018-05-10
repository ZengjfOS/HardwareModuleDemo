#include "../include/gpio_led.h"

int main(void)
{
    struct iot_gpio *gpio_led;
    int io_count = 8;
    int gpio_num[8] = {44, 45, 46, 47, 110, 111, 112, 113};
    int sleep_one_run = 300000;
    int sleep_all_run = 2000000;

    gpio_led = gpio_led_init(io_count, gpio_num, sleep_one_run, sleep_all_run);

    gpio_led->run(gpio_led);
    gpio_led->exit(gpio_led);

    return 0;
}
