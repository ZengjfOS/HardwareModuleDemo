#ifndef _GPIO_H_
#define _GPIO_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

/* gpio设备节点名称 */
#define		GPIO_DEV_NAME		"/dev/gpio"

#define		TYPE			'A'
#define		GPIO_INPUT		_IOWR(TYPE, 0, int)
#define		GPIO_OUTPUT		_IOWR(TYPE, 1, int)
#define		GPIO_SET		_IOWR(TYPE, 2, int)
#define		GPIO_GET		_IOWR(TYPE, 3, int)

#define     IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))
#define     RELAY_R         IMX_GPIO_NR(1, 15)      //GPIO_0
#define     RELAY_Y         IMX_GPIO_NR(1, 14)      //GPIO_1
#define     RELAY_G         IMX_GPIO_NR(1, 13)      //GPIO_2
#define     RELAY_STOP      IMX_GPIO_NR(1, 12)      //GPIO_3

#define     SENSOROUT1      IMX_GPIO_NR(2, 0)       //SEN_A1+,SEN_A1-   //GPIO_4
#define     SENSOROUT2      IMX_GPIO_NR(2, 1)       //SEN_A2+,SEN_A2-   //GPIO_5
#define     SENSOROUT3      IMX_GPIO_NR(2, 2)       //SEN_B1+,SEN_B1-   //GPIO_6
#define     LAMP1           IMX_GPIO_NR(2, 3)       //GPIO_7
#define     LAMP2           IMX_GPIO_NR(2, 4)       //GPIO_8
#define     LAMP3           IMX_GPIO_NR(2, 5)       //GPIO_9
#define     LAMP4           IMX_GPIO_NR(2, 6)       //GPIO_10
#define     LAMP5           IMX_GPIO_NR(2, 7)       //GPIO_11

#define     TP2             IMX_GPIO_NR(3, 16)      //GPIO_12
#define     EXOUT           IMX_GPIO_NR(3, 17)      //继电器    //GPIO_13
#define     TP5             IMX_GPIO_NR(3, 18)      //GPIO_14
#define     TP7             IMX_GPIO_NR(3, 19)      //GPIO_15

#define     DIS_IN1         IMX_GPIO_NR(3, 23)      //SEN_A+,SEN_A- //GPIO_16
#define     DIS_IN2         IMX_GPIO_NR(3, 28)      //TP8,TP9           //GPIO_17
#define     DIS_IN3         IMX_GPIO_NR(3, 30)      //SEN_B+,SEN_B- //GPIO_18
#define     DIS_IN4         IMX_GPIO_NR(3, 31)      //TP10,TP11     //GPIO_19

#define     TP1             IMX_GPIO_NR(1, 4)       //GPIO_20
#define     TP3             IMX_GPIO_NR(1, 5)       //GPIO_21

#define     TP4             IMX_GPIO_NR(7, 11)      //GPIO_22
#define     TP6             IMX_GPIO_NR(7, 12)      //GPIO_23

#define     GPIO_24         IMX_GPIO_NR(5, 30)      //GPIO_24
#define     GPIO_25         IMX_GPIO_NR(5, 31)      //GPIO_25
#define     GPIO_26         IMX_GPIO_NR(6, 0)       //GPIO_26
#define     GPIO_27         IMX_GPIO_NR(6, 1)       //GPIO_27
#define     GPIO_28         IMX_GPIO_NR(6, 2)       //GPIO_28
#define     GPIO_29         IMX_GPIO_NR(6, 3)       //GPIO_29
#define     GPIO_30         IMX_GPIO_NR(6, 4)       //GPIO_30
#define     GPIO_31         IMX_GPIO_NR(6, 5)       //GPIO_31

#define     GPIO_32         IMX_GPIO_NR(4, 8)
#define     GPIO_33         IMX_GPIO_NR(4, 9)

#define     GPIO_34         IMX_GPIO_NR(4, 14)
#define     GPIO_35         IMX_GPIO_NR(4, 15)

typedef struct gpio_arg {
	unsigned int gpio_index;
	unsigned int value;
}GPIO_T;

int gpio_input(int fd, int gpio_index);

int gpio_output(int fd, int gpio_index, int value);

int gpio_set_value(int fd, int gpio_index, int value);

int gpio_get_value(int fd, int gpio_index, int *value);

#endif
