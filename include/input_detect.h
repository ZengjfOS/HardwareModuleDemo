#ifndef __INPUT_DETECT_H__
#define __INPUT_DETECT_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_DEVICE  "/proc/bus/input/devices"
#define BUF_SIZE  2048

#define USB_KEYBOARD_NAME       "Keyboard"
#define USB_KEYBOARD_NAME_SIZE  8
#define USB_MOUSE_NAME          "MOUSE"
#define USB_MOUSE_NAME_SIZE     5
#define TOUCH_SCREEN_NAME       "ti-tsc"
#define TOUCH_SCREEN_NAME_SIZE  6

struct device_detect
{
    char usb_keyboard_name[32];
    int usb_keyboard_name_size;
    char usb_mouse_name[32];
    int usb_mouse_name_size;
    char touch_screen_name[32];
    int touch_screen_name_size;
    char detect_path[32];

    struct device_detect *(* init)(void);
    int (* detect_usb_keyboard)(struct device_detect *);
    int (* detect_usb_mouse)(struct device_detect *);
    int (* detect_touch_screen)(struct device_detect *);
    int (* detect_spe_device)(char *device_name, char *path, int device_name_size);
    void (* release)(struct device_detect *);
};

/* Alloc An device_detect structure  */
struct device_detect *device_detect_init(void);
/* detect specific device  */
int detect_spe_device(char *device_name, char *path, int device_name_size);
/* detect usb keyboard */
int detect_usb_keyboard(struct device_detect *input_detect);
/* detect usb mouse */
int detect_usb_mouse(struct device_detect *input_detect);
/* detect touch screen  */
int detect_touch_screen(struct device_detect *input_detect);
/* release function  */
void detect_release(struct device_detect *input_detect);

#endif /* __INPUT_DETECT_H__ */
