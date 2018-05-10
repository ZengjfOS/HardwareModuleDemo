#include "../include/usb_udisk_detect.h"

struct usb_udisk_detect *usb_udisk_detect_init(void)
{
    struct usb_udisk_detect *usb_udisk;

    usb_udisk = (struct usb_udisk_detect *)malloc(sizeof(struct usb_udisk_detect));
    if (usb_udisk == NULL)
        return NULL;

    memset(usb_udisk, 0, sizeof(struct usb_udisk_detect));

    strcpy(usb_udisk->usb_udisk1_detect_file, USB_UDISK1_FILE);
    strcpy(usb_udisk->usb_udisk2_detect_file, USB_UDISK2_FILE);
    strcpy(usb_udisk->usb_udisk_detect_str, USB_UDISK_STR);

    usb_udisk->usb1_result = usb_udisk1_detect_result;
    usb_udisk->usb2_result = usb_udisk2_detect_result;

    return usb_udisk;
}

int usb_udisk_detect_result(struct usb_udisk_detect *usb_udisk, char *usb_udisk_file)
{
    int usb_udisk_fd;
    char tmp[32];

    usb_udisk_fd = open(usb_udisk_file, O_RDONLY);
    if(usb_udisk_fd < 0)
    {
        perror("open usb device");
        return -1;
    }

    read(usb_udisk_fd, tmp, sizeof(tmp));

    close(usb_udisk_fd);

    if(strncmp(usb_udisk->usb_udisk_detect_str, tmp, 16) == 0)
        return 0;
    else
        return 1;
}

int usb_udisk1_detect_result(struct usb_udisk_detect *usb_udisk)
{
    return usb_udisk_detect_result(usb_udisk, usb_udisk->usb_udisk1_detect_file);
}

int usb_udisk2_detect_result(struct usb_udisk_detect *usb_udisk)
{
    return usb_udisk_detect_result(usb_udisk, usb_udisk->usb_udisk2_detect_file);
}

void usb_udisk_detect_release(struct usb_udisk_detect *usb_udisk)
{
    free(usb_udisk);
}

