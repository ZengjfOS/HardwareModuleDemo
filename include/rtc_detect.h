#ifndef __TIME_DETECT_H__
#define __TIME_DETECT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define RTC_DEVICE  "/dev/rtc0"

#define MIN_TO_SEC  60
#define HOUR_TO_SEC  (MIN_TO_SEC*60)
#define DAY_TO_SEC   (HOUR_TO_SEC*24);

struct rtc_detect
{
    char rtc_device[32];
    struct rtc_time rtc_tm;

    int (* read)(struct rtc_detect *rtc_det);
    void (* release)(struct rtc_detect *rtc_det);
    unsigned long (* read_timestamp)(void);
    void (* display)(struct rtc_detect *rtc_det);
};

/* Alloc and init rtc_detect structure  */
struct rtc_detect *rtc_detect_init(void);
/* Read rtc data   */
int rtc_detect_read(struct rtc_detect *rtc_det);
/* return timestamp */
unsigned long rtc_detect_read_timestamp(void);
/* Display time  */
void rtc_detect_display(struct rtc_detect *rtc_det);
/* release function */
void rtc_detect_release(struct rtc_detect *rtc_det);

#endif /* __TIME_DETECT_H__ */

