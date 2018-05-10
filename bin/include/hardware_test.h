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
    struct device_detect *input;
    struct rtc_detect *rtc;
    struct uart_us100 *COM1;
    struct uart_us100 *COM2;
    // struct usb_udisk_detect *udisk;

    Json::Value root_json;
    Json::Value data_json;
    Json::Value gpio_json;
    Json::Value eeprom_json;
    Json::Value input_json;
    Json::Value rtc_json;
    Json::Value COM1_json;
    Json::Value COM2_json;

    Hardware_test() {
        eeprom = eeprom_detect_init();
        input  = device_detect_init();
        rtc    = rtc_detect_init();
        COM1   = uart_us100_init(TTY_NODE1);
        COM2   = uart_us100_init(TTY_NODE2);

        gpio_json["status"] = "error";
        eeprom_json["status"] = "error";
        input_json["status"] = "error";
        rtc_json["status"] = "error";
        COM1_json["status"] = "error";
        COM2_json["status"] = "error";
    }

    ~Hardware_test() {
        eeprom->release(eeprom);
        input->release(input);
        rtc->release(rtc);
        COM1->release(COM1);
        COM2->release(COM2);
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

        /*
        pid_t pid = fork();
        if (pid == 0) {
            creat_daemon();
        }
        */
        int gpio_fd = 0;
        int gpio_relay[7] = {
            RELAY_R,
            RELAY_Y,  
            RELAY_G,  
            RELAY_STOP,
            SENSOROUT1,
            SENSOROUT2,
            SENSOROUT3
        };

        int gpio_input_output[] = {
            GPIO_24,
            GPIO_25,
            GPIO_26,
            GPIO_27,
            GPIO_28,
            GPIO_29,
            GPIO_30,
            GPIO_31
        };

        gpio_fd = open(GPIO_DEV_NAME, O_RDWR|O_NOCTTY|O_NDELAY);
        if (gpio_fd < 0)
        {
            perror("open device node error.");
            return ;
        }

        int i = 0;
        int value = 0;
        int count = 0;  // get set count 
        for (; i < 7; i++) {
            gpio_output(gpio_fd, gpio_relay[i], 1);
            /*
            usleep(500 * 1000);
            gpio_get_value(gpio_fd, DIS_IN1, &value);
            // printf("TY_IN+ DIS_IN1 value: %d.\r\n", value);
            if (value == 1)
                count++;
            gpio_get_value(gpio_fd, DIS_IN3, &value);
            // printf("FN_IN DIS_IN3 value: %d.\r\n", value);
            if (value == 1)
                count++;
            */
        }
        usleep(1000 * 1000);

        for (i = 0; i < 7; i++) {
            gpio_output(gpio_fd, gpio_relay[i], 0);
            usleep(500 * 1000);
            gpio_get_value(gpio_fd, DIS_IN1, &value);
            // printf("TY_IN+ DIS_IN1 value: %d.\r\n", value);
            if (value == 0)
                count++;
            gpio_get_value(gpio_fd, DIS_IN3, &value);
            // printf("FN_IN DIS_IN3 value: %d.\r\n", value);
            if (value == 0)
                count++;

            gpio_output(gpio_fd, gpio_relay[i], 1);
            usleep(500 * 1000);
            gpio_get_value(gpio_fd, DIS_IN1, &value);
            // printf("TY_IN+ DIS_IN1 value: %d.\r\n", value);
            if (value == 1)
                count++;
            gpio_get_value(gpio_fd, DIS_IN3, &value);
            // printf("FN_IN DIS_IN3 value: %d.\r\n", value);
            if (value == 1)
                count++;
        }

        for (i = 0; i < 4; i++) {
            gpio_output(gpio_fd, gpio_input_output[i], 0);
            usleep(500 * 1000);
            gpio_input(gpio_fd, gpio_input_output[i + 4]);
            gpio_get_value(gpio_fd, gpio_input_output[i + 4], &value);
            if (value == 0)
                count++;
            // printf("GPIO Input value: %d.\r\n", value);
            
            gpio_output(gpio_fd, gpio_input_output[i], 1);
            usleep(500 * 1000);
            gpio_input(gpio_fd, gpio_input_output[i + 4]);
            gpio_get_value(gpio_fd, gpio_input_output[i + 4], &value);
            if (value == 1)
                count++;
            // printf("GPIO Input value: %d.\r\n", value);
        }

        close(gpio_fd);

        gpio_json["name"] = "MIO_8_GPIO";
        gpio_json["index"] = "9";
        gpio_json["descriptor"] = "gpio";
        gpio_json["range"] = "";
        gpio_json["value"] = count;
        if (count == ((7 * 4) + (4 * 2))) {
            gpio_json["status"] = "ok";
        } else {
            gpio_json["status"] = "error";
        }
    }

    void buzzer_test() {
        system("./buzzer /dev/buzzer &");
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
        eeprom_json["index"] = "11";
        eeprom_json["descriptor"] = "i2c";
        eeprom_json["range"] = "";
        eeprom_json["value"] = "";
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

        tmp = COM1->read(COM1);

        if (tmp > 0)
            COM1_json["status"] = "ok";
        else
            COM1_json["status"] = "error";

        COM1_json["name"] = "DB9_RS232_COM1";
        COM1_json["index"] = "6";
        COM1_json["descriptor"] = "uart";
        COM1_json["range"] = "";
        COM1_json["value"] = tmp;

        tmp = COM2->read(COM2);

        if (tmp > 0)
            COM2_json["status"] = "ok";
        else
            COM2_json["status"] = "error";

        COM2_json["name"] = "DB9_RS232_COM2";
        COM2_json["index"] = "6";
        COM2_json["descriptor"] = "uart";
        COM2_json["range"] = "";
        COM2_json["value"] = tmp;
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
        value["index"] = "5";
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

    void json_string() {
        data_json["gpio"] = gpio_json;
        data_json["eeprom"] = eeprom_json;
        data_json["input"] = input_json;
        data_json["rtc"] = rtc_json;
        data_json["COM1"] = COM1_json;
        data_json["COM2"] = COM2_json;
        root_json["data"] = data_json;

        root_json["categories"] = "hardware_test";

        Json::StyledWriter writer;
        string outputJsonstring = writer.write(root_json);

        cout << outputJsonstring;
    }

};

#endif // __HARDWARE_TEST_H__
