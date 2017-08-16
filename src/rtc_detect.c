#include "../include/rtc_detect.h"

struct rtc_detect *rtc_detect_init(void)
{
    struct rtc_detect *rtc_det;

    rtc_det = (struct rtc_detect *)malloc(sizeof(struct rtc_detect));
    if (rtc_det == NULL)
        return NULL;

    bzero(rtc_det, sizeof(struct rtc_detect));

    strcpy(rtc_det->rtc_device, RTC_DEVICE);

    rtc_det->read = rtc_detect_read;
    rtc_det->display = rtc_detect_display;
    rtc_det->read_timestamp = rtc_detect_read_timestamp;
    rtc_det->release = rtc_detect_release;

    return rtc_det;
}

int rtc_detect_read(struct rtc_detect *rtc_det)
{
    int fd, retval;

    fd = open(rtc_det->rtc_device, O_RDONLY);
    if (fd < 0)
    {
        perror("open rtc error");
        return -1;
    }

    retval = ioctl(fd, RTC_RD_TIME, &(rtc_det->rtc_tm));
    if (retval < 0)
    {
        perror("ioctl rtc error");
    }

    close(fd);

    return retval;
}


void rtc_detect_display(struct rtc_detect *rtc_det)
{
    printf("RTC date/time: %d/%d/%d  %02d:%02d:%02d\n",
            rtc_det->rtc_tm.tm_mday, rtc_det->rtc_tm.tm_mon + 1, rtc_det->rtc_tm.tm_year + 1900,
            rtc_det->rtc_tm.tm_hour, rtc_det->rtc_tm.tm_min, rtc_det->rtc_tm.tm_sec);
}

void rtc_detect_release(struct rtc_detect *rtc_det)
{
    free(rtc_det);
}

unsigned long rtc_detect_read_timestamp()
{
    system("hwclock -s");

    return time(NULL);
}

