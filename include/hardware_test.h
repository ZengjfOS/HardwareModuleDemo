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
    // GPIO_LED gpio;
    struct eeprom_detect *eeprom;
    struct i2c_tmp75 *tmp75;
    struct device_detect *input;
    struct rtc_detect *rtc;
    struct uart_us100 *us100;
    struct usb_udisk_detect *udisk;

    Json::Value root_json;
    Json::Value data_json;
    Json::Value gpio_json;
    Json::Value eeprom_json;
    Json::Value tmp75_json;
    Json::Value input_json;
    Json::Value rtc_json;
    Json::Value us100_json;
    Json::Value udisk_json;

    Hardware_test() {
        eeprom = eeprom_detect_init();
        tmp75  = tmp75_init();
        input  = device_detect_init();
        rtc    = rtc_detect_init();
        us100   = uart_us100_init();
        udisk  = usb_udisk_detect_init();

        gpio_json["status"] = "error";
        eeprom_json["status"] = "error";
        tmp75_json["status"] = "error";
        input_json["status"] = "error";
        rtc_json["status"] = "error";
        us100_json["status"] = "error";
        udisk_json["status"] = "error";
    }

    ~Hardware_test() {
        eeprom->release(eeprom);
        tmp75->release(tmp75);
        input->release(input);
        rtc->release(rtc);
        us100->release(us100);
        udisk->release(udisk);
    }

    // refer to http://www.cnblogs.com/zengjfgit/p/7374516.html
    void creat_daemon(void)
    {
        pid_t pid;
        GPIO_LED gpio_led;

        pid = fork();
        if ( pid == -1)
            printf("fork error");

        if (pid > 0 )
            exit(EXIT_SUCCESS);

        if (setsid() == -1)
            printf("SETSID ERROR");

        chdir("/");

        int i;
        for (i = 0; i < 3; ++i) {
            close(i);
            open("/dev/null", O_RDWR);
            dup(0);
            dup(0);
        }

        umask(0);

        gpio_led.init();
        while (1) {
            gpio_led.left_to_right();
            gpio_led.right_to_left();
            gpio_led.all_light();
        }
        gpio_led.release();

        exit(0);

        return;
    }

    void gpio_test() {
        pid_t pid = fork();
        if (pid == 0) {
            creat_daemon();
        }

        gpio_json["name"] = "MIO_8_GPIO";
        gpio_json["index"] = "10";
        gpio_json["descriptor"] = "gpio";
        gpio_json["range"] = "";
        gpio_json["value"] = "";
        gpio_json["status"] = "ok";
    }

    void eeprom_test() {
        int ret = 0;
        eeprom->write(eeprom);
        eeprom->read(eeprom);
        ret = eeprom->result(eeprom);
        if (!ret)
            eeprom_json["status"] = "ok";
        else
            eeprom_json["status"] = "error";

        eeprom_json["name"] = "EEPROM";
        eeprom_json["index"] = "12";
        eeprom_json["descriptor"] = "i2c";
        eeprom_json["range"] = "";
        eeprom_json["value"] = "";
    }

    void tmp75_test() {
        float tmp = 0;

        tmp = tmp75->read(tmp75);

        if (tmp != -1)
            tmp75_json["status"] = "ok";
        else
            tmp75_json["status"] = "error";

        tmp75_json["name"] = "CON3_I2C";
        tmp75_json["index"] = "8";
        tmp75_json["descriptor"] = "i2c";
        tmp75_json["range"] = "";
        tmp75_json["value"] = tmp;
    }

    void rtc_test() {
        int tmp = 0;

        tmp = rtc->read(rtc);

        if (tmp != -1)
            rtc_json["status"] = "ok";
        else
            rtc_json["status"] = "error";

        rtc_json["name"] = "rtc";
        rtc_json["index"] = "3";
        rtc_json["descriptor"] = "i2c";
        rtc_json["range"] = "";
        rtc_json["value"] = tmp;
    }

    void us100_test() {
        int tmp = 0;

        tmp = us100->read(us100);

        if (tmp != -1)
            us100_json["status"] = "ok";
        else
            us100_json["status"] = "error";

        us100_json["name"] = "DB9_RS232";
        us100_json["index"] = "6";
        us100_json["descriptor"] = "uart";
        us100_json["range"] = "";
        us100_json["value"] = tmp;
    }

    void input_test() {
        Json::Value value;
        int result = 0;

        result = input->detect_usb_keyboard(input);
        if (result)
            value["status"] = "ok";
        else
            value["status"] = "error";

        value["name"] = "keyboard";
        value["index"] = "4";
        value["descriptor"] = "usb";
        value["range"] = "";
        value["value"] = "";

        input_json["keyboard"] = value;

        result = input->detect_usb_mouse(input);
        if (result)
            value["status"] = "ok";
        else
            value["status"] = "error";

        value["name"] = "mouse";
        value["index"] = "4";
        value["descriptor"] = "usb";
        value["range"] = "";
        value["value"] = "";

        input_json["mouse"] = value;

        result = input->detect_touch_screen(input);
        if (result)
            value["status"] = "ok";
        else
            value["status"] = "error";

        value["name"] = "touch";
        value["index"] = "4";
        value["descriptor"] = "usb";
        value["range"] = "";
        value["value"] = "";

        input_json["touch"] = value;
    }

    void udisk_test() {
        Json::Value value;

        if (udisk->usb1_result(udisk) == 0)
            value["status"] = "ok";
        else
            value["status"] = "error";

        value["name"] = "MIO_USB";
        value["index"] = "11";
        value["descriptor"] = "usb";
        value["range"] = "";
        value["value"] = "";

        udisk_json["usb1"] = value;

        if (udisk->usb2_result(udisk) == 0)
            value["status"] = "ok";
        else
            value["status"] = "error";

        value["name"] = "CON3_USB";
        value["index"] = "13";
        value["descriptor"] = "usb";
        value["range"] = "";
        value["value"] = "";

        udisk_json["usb2"] = value;
    }

    void json_string() {
        data_json["gpio"] = gpio_json;
        data_json["eeprom"] = eeprom_json;
        data_json["tmp75"] = tmp75_json;
        data_json["input"] = input_json;
        data_json["rtc"] = rtc_json;
        data_json["us100"] = us100_json;
        data_json["udisk"] = udisk_json;
        root_json["data"] = data_json;

        root_json["categories"] = "hardware_test";

        Json::StyledWriter writer;
        string outputJsonstring = writer.write(root_json);

        cout << outputJsonstring;
    }

};

#endif // __HARDWARE_TEST_H__
