#include <iostream>
#include <includes.h>

using namespace std;
using namespace GPIO;

class Hardware_test *context;

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

int main(int argc, char** argv) 
{
    Json::Value root;
    Json::Value data;
    root["categories"] = "hardware_test";

    // fork new process to test gpio
    if (fork() == 0) {  // child process
        creat_daemon();
    } else {

        context = (class Hardware_test *)(malloc(sizeof(class Hardware_test)));

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

        exit(0);
    }
}
