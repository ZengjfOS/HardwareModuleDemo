#include <iostream>
#include <gpio_led.h>

int main(int argc, char** argv) 
{
    GPIO_LED gpio_led;
    gpio_led.init();
    gpio_led.left_to_right();
    gpio_led.right_to_left();
    gpio_led.all_light();
    gpio_led.release();
}
