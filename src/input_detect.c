#include "../include/input_detect.h"

struct device_detect *device_detect_init(void)
{
    struct device_detect *input_detect;

    input_detect = (struct device_detect *)malloc(sizeof(struct device_detect));
    if (!input_detect)
        return NULL;

    memset(input_detect, 0, sizeof(struct device_detect));

    input_detect->usb_keyboard_name_size = USB_KEYBOARD_NAME_SIZE;
    input_detect->usb_mouse_name_size = USB_MOUSE_NAME_SIZE;
    input_detect->touch_screen_name_size = TOUCH_SCREEN_NAME_SIZE;

    strcpy(input_detect->usb_keyboard_name, USB_KEYBOARD_NAME);
    strcpy(input_detect->usb_mouse_name, USB_MOUSE_NAME);
    strcpy(input_detect->touch_screen_name, TOUCH_SCREEN_NAME);
    strcpy(input_detect->detect_path, INPUT_DEVICE);

    input_detect->init = device_detect_init;
    input_detect->detect_usb_keyboard = detect_usb_keyboard;
    input_detect->detect_usb_mouse = detect_usb_mouse;
    input_detect->detect_touch_screen = detect_touch_screen;
    input_detect->detect_spe_device = detect_spe_device;
    input_detect->release = detect_release;

    return input_detect;
}

int detect_spe_device(char *device_name, char *path, int device_name_size)
{
    char tmp[BUF_SIZE], *tmp_buf = tmp;
    int fd, retval, detect_num = 0;


    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open ");
        return -1;
    }

    retval = read(fd, tmp, BUF_SIZE);
    if (retval < 0)
    {
        perror("read ");
        close(fd);
        return -1;
    }

    while (*tmp_buf++ != '\0')
    {
        if(tmp_buf[0] == device_name[0])
        {
            if ((strncasecmp(tmp_buf, device_name, device_name_size)) == 0)
            {
                detect_num = 1;
                break;
            }
        }
    }

    close(fd);

    return detect_num;
}

int detect_usb_keyboard(struct device_detect *input_detect)
{
    return detect_spe_device(input_detect->usb_keyboard_name, input_detect->detect_path, input_detect->usb_keyboard_name_size);
}

int detect_usb_mouse(struct device_detect *input_detect)
{
    return detect_spe_device(input_detect->usb_mouse_name, input_detect->detect_path, input_detect->usb_mouse_name_size);
}

int detect_touch_screen(struct device_detect *input_detect)
{
    return detect_spe_device(input_detect->touch_screen_name, input_detect->detect_path, input_detect->touch_screen_name_size);
}

void detect_release(struct device_detect *input_detect)
{
    free(input_detect);
}
