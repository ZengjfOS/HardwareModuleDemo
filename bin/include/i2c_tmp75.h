#ifndef __APLEX_I2C_TMP75__
#define __APLEX_I2C_TMP75__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define TMP75_OUTPUT_DEV  "/sys/bus/i2c/devices/2-004c/hwmon/hwmon0/temp1_input"
#define TMP75_SLAVE_REG   0x4c
#define TMP75_I2C_DEV     "/dev/i2c-2"

/*
 * structure i2c_tmp75
 * temperature : tmp75 temperature.
 * slave_register tmp75 i2c slave_register.
 * i2c_dev : tmp75 i2c device name .
 * tmp75_output_dev : tmp75 driver output name .
 */

struct i2c_tmp75
{
    float temperature;
    int slave_register;
    char i2c_dev[128];
    char tmp75_output_dev[128];

    struct i2c_tmp75 *(* init)(void);
    float (* read)(struct i2c_tmp75 *);
    void (* release)(struct i2c_tmp75 *);
};

/* creare An i2c_tmp75 temperature structure and init it */
struct i2c_tmp75 *tmp75_init(void);
/* read the temperature than return it */
float tmp75_read(struct i2c_tmp75 *);
/* free i2c_tmp75  */
void tmp75_release(struct i2c_tmp75 *);

#endif /* __APLEX_I2C_TMP75__  */
