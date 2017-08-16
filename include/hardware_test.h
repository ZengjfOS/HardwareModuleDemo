#ifndef __HARDWARE_TEST_H__
#define __HARDWARE_TEST_H__

#include <gpio_led.h>
#include <json/json.h>
#include <i2c_tmp75.h>
#include <input_detect.h>
#include <rtc_detect.h>
#include <uart_us100.h>
#include <eeprom_detect.h>
#include <usb_udisk_detect.h>

using namespace GPIO;

class Hardware_test {

public:
    GPIO_LED gpio;
    struct eeprom_detect *eeprom;
    struct i2c_tmp75 *tmp75;
    struct device_detect *input;
    struct rtc_detect *rtc;
    struct uart_us100 *uart;
    struct usb_udisk_detect *udisk;

    Hardware_test() {
        eeprom = eeprom_detect_init();
        tmp75  = tmp75_init();
        input  = device_detect_init();
        rtc    = rtc_detect_init();
        uart   = uart_us100_init();
        udisk  = usb_udisk_detect_init();
    }

    ~Hardware_test() {
        eeprom->release(eeprom);
        tmp75->release(tmp75);
        input->release(input);
        rtc->release(rtc);
        uart->release(uart);
        udisk->release(udisk);
    }
};

#endif // __HARDWARE_TEST_H__
