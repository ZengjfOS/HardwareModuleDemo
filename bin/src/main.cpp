#include <iostream>
#include <includes.h>

using namespace std;
using namespace GPIO;

class Hardware_test *context;


int main(int argc, char** argv) 
{
    // context = (class Hardware_test *)(malloc(sizeof(class Hardware_test)));
    context = new Hardware_test();

    context->gpio_test();
    // context->buzzer_test();
    // context->eeprom_test();
    context->rtc_test();
    context->us100_test();
    context->input_test();
    // context->udisk_test();
    context->json_string();

    exit(0);
}
