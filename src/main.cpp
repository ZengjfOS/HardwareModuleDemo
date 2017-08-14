#include <iostream>
#include <gpio_led.h>
#include <json/json.h>

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
