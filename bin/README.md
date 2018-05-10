# Hardware Test Module Progam Demo

* 添加jsoncpp作为json数据合成方法，编译json数据转换输出；
* GPIO软件测试采用fork出新进程进行处理；
* 使用namespace对class命名空间进行范围约束；
* 输出信息格式：
    ```JSON
    {
       "categories" : "hardware_test",
       "data" : {
          "eeprom" : {
             "descriptor" : "i2c",
             "index" : "11",
             "name" : "EEPROM",
             "range" : "",
             "status" : "ok",
             "value" : ""
          },
          "gpio" : {
             "descriptor" : "gpio",
             "index" : "9",
             "name" : "MIO_8_GPIO",
             "range" : "",
             "status" : "ok",
             "value" : ""
          },
          "input" : {
             "keyboard" : {
                "descriptor" : "usb",
                "index" : "4",
                "name" : "keyboard",
                "range" : "",
                "status" : "error",
                "value" : ""
             },
             "mouse" : {
                "descriptor" : "usb",
                "index" : "5",
                "name" : "mouse",
                "range" : "",
                "status" : "error",
                "value" : ""
             },
             "status" : "error",
             "touch" : {
                "descriptor" : "usb",
                "index" : "4",
                "name" : "touch",
                "range" : "",
                "status" : "ok",
                "value" : ""
             }
          },
          "rtc" : {
             "descriptor" : "i2c",
             "index" : "3",
             "name" : "rtc",
             "range" : "",
             "status" : "ok",
             "value" : 0
          },
          "tmp75" : {
             "descriptor" : "i2c",
             "index" : "8",
             "name" : "CON3_I2C",
             "range" : "",
             "status" : "ok",
             "value" : 27.125
          },
          "udisk" : {
             "status" : "error",
             "usb1" : {
                "descriptor" : "usb",
                "index" : "10",
                "name" : "MIO_USB",
                "range" : "",
                "status" : "error",
                "value" : ""
             },
             "usb2" : {
                "descriptor" : "usb",
                "index" : "7",
                "name" : "CON3_USB",
                "range" : "",
                "status" : "error",
                "value" : ""
             }
          },
          "us100" : {
             "descriptor" : "uart",
             "index" : "6",
             "name" : "DB9_RS232",
             "range" : "",
             "status" : "ok",
             "value" : 506
          }
       }
    }
    ```
* 输出信息使用参考：
  * [PHPConfigDemo json解析部分](https://github.com/ZengjfOS/PHPConfigDemo/blob/master/json.php)
* [PHP Web Server Linker](https://github.com/ZengjfOS/HardwareModuleDemo/tree/Hardware_Test_Demo_Functions)

## GPIO LED Module代码参考

### 原先GPIO LED Module代码参考

* [io_program/gpio_led.h](io_program/gpio_led.h)
* [io_program/gpio_led.c](io_program/gpio_led.c)

### C++ class GPIO LED Module代码参考

* [include/gpio_led.h](include/gpio_led.h)
* [src/main.cpp](src/main.cpp)

### 总结

除了使用class的方式写，起始另外采用struct来写这种结构性的程序也是一样的，请参考[《EEPROMData》](https://github.com/ZengjfOS/EEPROMData)。
