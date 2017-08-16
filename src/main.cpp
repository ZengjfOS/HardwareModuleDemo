#include <iostream>
#include <includes.h>

using namespace std;
using namespace GPIO;

int main(int argc, char** argv) 
{
    GPIO_LED gpio_led;

    Json::Value root;
    Json::Value data;
    root["categories"] = "hardware_test";

    // fork new process to test gpio
    if (fork() == 0) {  // child process
        gpio_led.init();
        gpio_led.left_to_right();
        gpio_led.right_to_left();
        gpio_led.all_light();
        gpio_led.release();

        exit(0);
    } else {

        float tmp = 0;
        struct i2c_tmp75 *tmp75;

        tmp75 = tmp75_init(TMP75_SLAVE_REG, TMP75_I2C_DEV, TMP75_OUTPUT_DEV);
        tmp = tmp75->read(tmp75);
        tmp75->exit(tmp75);

        Json::Value gpio;
        // set gpio hardware test status
        gpio["status"] = "ok";

        // set gpio value to data
        data["GPIO"] = gpio;

        // set data value to root
        root["data"] = data;

        Json::StyledWriter writer;
        string outputJsonstring = writer.write(root);

        cout << outputJsonstring << endl;
    }
}
