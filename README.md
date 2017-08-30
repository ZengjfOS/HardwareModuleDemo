# Hardware Test Module Progam Demo

* 添加jsoncpp作为json数据合成方法，编译json数据转换输出；
* GPIO软件测试采用fork出新进程进行处理；
* 使用namespace对class命名空间进行范围约束；
* 输出信息格式：
    ```
    [root ~]# ./hardware_test
    {
       "categories" : "hardware_test",
       "data" : {
          "GPIO" : {
             "status" : "ok"
          }
       }
    }
    
    [root ~]#
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
