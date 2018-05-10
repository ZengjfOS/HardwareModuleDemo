#include "../include/gpio_led.h"

void gpio_led_start(void)
{
    int u_sleep_time = 200000, all_led_time = 2000000;

    /* Gpio init */
    system("echo 44 > /sys/class/gpio/export");
    system("echo 45 > /sys/class/gpio/export");
    system("echo 46 > /sys/class/gpio/export");
    system("echo 47 > /sys/class/gpio/export");
    system("echo 110 > /sys/class/gpio/export");
    system("echo 111 > /sys/class/gpio/export");
    system("echo 112 > /sys/class/gpio/export");
    system("echo 113 > /sys/class/gpio/export");

    /* Set Gpio output mode  */
    system("echo out > /sys/class/gpio/gpio44/direction");
    system("echo out > /sys/class/gpio/gpio45/direction");
    system("echo out > /sys/class/gpio/gpio46/direction");
    system("echo out > /sys/class/gpio/gpio47/direction");
    system("echo out > /sys/class/gpio/gpio110/direction");
    system("echo out > /sys/class/gpio/gpio111/direction");
    system("echo out > /sys/class/gpio/gpio112/direction");
    system("echo out > /sys/class/gpio/gpio113/direction");

    /* Left --> Right  */
    usleep(u_sleep_time);
    system("echo 1 > /sys/class/gpio/gpio44/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio44/value");
    system("echo 1 > /sys/class/gpio/gpio45/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio45/value");
    system("echo 1 > /sys/class/gpio/gpio46/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio46/value");
    system("echo 1 > /sys/class/gpio/gpio47/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio47/value");
    system("echo 1 > /sys/class/gpio/gpio110/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio110/value");
    system("echo 1 > /sys/class/gpio/gpio111/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio111/value");
    system("echo 1 > /sys/class/gpio/gpio112/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio112/value");
    system("echo 1 > /sys/class/gpio/gpio113/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio113/value");

    /* Right --> Left */
    usleep(u_sleep_time);
    system("echo 1 > /sys/class/gpio/gpio113/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio113/value");
    system("echo 1 > /sys/class/gpio/gpio112/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio112/value");
    system("echo 1 > /sys/class/gpio/gpio111/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio111/value");
    system("echo 1 > /sys/class/gpio/gpio110/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio110/value");
    system("echo 1 > /sys/class/gpio/gpio47/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio47/value");
    system("echo 1 > /sys/class/gpio/gpio46/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio46/value");
    system("echo 1 > /sys/class/gpio/gpio45/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio45/value");
    system("echo 1 > /sys/class/gpio/gpio44/value");
    usleep(u_sleep_time);
    system("echo 0 > /sys/class/gpio/gpio44/value");

    /* All led run   */
    usleep(u_sleep_time);
    system("echo 1 > /sys/class/gpio/gpio44/value");
    system("echo 1 > /sys/class/gpio/gpio45/value");
    system("echo 1 > /sys/class/gpio/gpio46/value");
    system("echo 1 > /sys/class/gpio/gpio47/value");
    system("echo 1 > /sys/class/gpio/gpio110/value");
    system("echo 1 > /sys/class/gpio/gpio111/value");
    system("echo 1 > /sys/class/gpio/gpio112/value");
    system("echo 1 > /sys/class/gpio/gpio113/value");
    usleep(all_led_time);

    /* exit */
    system("echo 44 >  /sys/class/gpio/unexport");
    system("echo 45 >  /sys/class/gpio/unexport");
    system("echo 46 >  /sys/class/gpio/unexport");
    system("echo 47 >  /sys/class/gpio/unexport");
    system("echo 110 > /sys/class/gpio/unexport");
    system("echo 111 > /sys/class/gpio/unexport");
    system("echo 112 > /sys/class/gpio/unexport");
    system("echo 113 > /sys/class/gpio/unexport");
}
