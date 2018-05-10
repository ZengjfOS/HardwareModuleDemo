#include "../include/rtc_detect.h"

int main(void)
{
    struct rtc_detect *rtc_det;
    int retval;

    rtc_det = rtc_detect_init();
    retval = rtc_det->read(rtc_det);
    if (retval < 0)
        return -1;
    rtc_det->display(rtc_det);
    printf("timestamp : %lu \n", rtc_det->read_timestamp());
    rtc_det->release(rtc_det);

    return 0;
}
