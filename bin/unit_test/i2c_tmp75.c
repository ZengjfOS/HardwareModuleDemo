#include "../include/i2c_tmp75.h"

int main(void)
{
    float tmp = 0;
    struct i2c_tmp75 *tmp75;

    tmp75 = tmp75_init();
    tmp = tmp75->read(tmp75);
    tmp75->release(tmp75);

    printf("temperature : %f\n", tmp);

    return 0;
}
