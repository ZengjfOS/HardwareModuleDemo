
#include <stdio.h>

#include "gpio.h"

int gpio_input(int fd, int gpio_index)
{
	GPIO_T gpio_arg;

	gpio_arg.gpio_index = gpio_index;
	
	return ioctl(fd, GPIO_INPUT, &gpio_arg);	
}

int gpio_output(int fd, int gpio_index, int value)
{
	GPIO_T gpio_arg;

	gpio_arg.gpio_index = gpio_index;
	gpio_arg.value = value;
	
	return ioctl(fd, GPIO_OUTPUT, &gpio_arg);	
}

int gpio_set_value(int fd, int gpio_index, int value)
{
	GPIO_T gpio_arg;

	gpio_arg.gpio_index = gpio_index;
	gpio_arg.value = value;
	
	return ioctl(fd, GPIO_SET, &gpio_arg);	
}

int gpio_get_value(int fd, int gpio_index, int *value)
{
    int ret;
	GPIO_T gpio_arg;

	gpio_arg.gpio_index = gpio_index;
	
    ret = ioctl(fd, GPIO_GET, &gpio_arg);
    if (ret == -1)
        return -1;
    *value = gpio_arg.value;
    return 0;
}

int gpio_init(int fd) 
{
	int ret = 0;
    ret = gpio_output(fd, RELAY_R, 0);
    return ret;
}
