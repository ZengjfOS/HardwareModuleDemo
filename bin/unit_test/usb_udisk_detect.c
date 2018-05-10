#include "../include/usb_udisk_detect.h"

int main(void)
{
    struct usb_udisk_detect *usb_disk;

    usb_disk = usb_udisk_detect_init();

    if (usb_disk->usb1_result(usb_disk) == 0)
        printf("usb1 udisk1 detect ok\n");
    else
        printf("usb1 udisk1 detect fail \n");

    if (usb_disk->usb2_result(usb_disk) == 0)
        printf("usb1 udisk2 detect ok\n");
    else
        printf("usb1 udisk2 detect fail \n");

    return 0;
}
