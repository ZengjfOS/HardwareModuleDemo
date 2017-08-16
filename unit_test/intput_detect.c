#include "../include/input_detect.h"

int main(void)
{
    int result = 0;

    struct device_detect *input_device;

    input_device = device_detect_init();

    result = input_device->detect_usb_keyboard(input_device);
    if (result)
        printf(" Detect keyboard ---\n");
    else
        printf(" No keyboard ---\n");

    result = 0;
    result = input_device->detect_usb_mouse(input_device);
    if (result)
        printf(" Detect mouse ---\n");
    else
        printf(" No usb mouse ---\n");

    result = 0;
    result = input_device->detect_touch_screen(input_device);
    if (result)
        printf(" Detect touch screen ---\n");
    else
        printf(" No touch screen ---\n");

    input_device->release(input_device);

    return 0;
}

