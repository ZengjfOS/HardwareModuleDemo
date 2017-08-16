#ifndef __USB_UDISK_DETECT_H__
#define __USB_UDISK_DETECT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define USB_UDISK1_FILE     "/media/sda1/detect.txt"
#define USB_UDISK2_FILE     "/media/sdb1/detect.txt"
#define USB_UDISK_STR      "usb_udisk_device"

struct usb_udisk_detect
{
    char usb_udisk1_detect_file[32];
    char usb_udisk2_detect_file[32];
    char usb_udisk_detect_str[32];

    int (* usb1_result)(struct usb_udisk_detect *usb_udisk);
    int (* usb2_result)(struct usb_udisk_detect *usb_udisk);
    int (* release)(struct usb_udisk_detect *usb_udisk);
};

/* Alloc usb_udisk_detect structure  */
struct usb_udisk_detect *usb_udisk_detect_init(void);
/* return usb udisk1 detect result  */
int usb_udisk1_detect_result(struct usb_udisk_detect *usb_udisk);
/* return usb udisk1 detect result  */
int usb_udisk2_detect_result(struct usb_udisk_detect *usb_udisk);
/* release function  */
void usb_udisk_detect_release(struct usb_udisk_detect *usb_udisk);

#endif  /* __USB_UDISK_DETECT_H__  */
