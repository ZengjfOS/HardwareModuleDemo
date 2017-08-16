#include "../include/i2c_tmp75.h"

struct i2c_tmp75 *tmp75_init(void)
{
    struct i2c_tmp75 *tmp75;

    tmp75 = (struct i2c_tmp75 *)malloc(sizeof(struct i2c_tmp75));
    if (!tmp75)
        return NULL;

    memset(tmp75, 0, sizeof(struct i2c_tmp75));

    tmp75->temperature = 0;
    tmp75->slave_register = TMP75_SLAVE_REG;
    strcpy(tmp75->i2c_dev, TMP75_I2C_DEV);
    strcpy(tmp75->tmp75_output_dev, TMP75_OUTPUT_DEV);

    tmp75->init = tmp75_init;
    tmp75->read = tmp75_read;
    tmp75->release = tmp75_release;

    return tmp75;
}

float tmp75_read(struct i2c_tmp75 *tmp75)
{
    int fd, i, n = 1;
    char tmp[5];

    fd = open(tmp75->tmp75_output_dev, O_RDONLY);
    if (fd < 0)
    {
        perror("open device error");
        return -1;
    }

    read(fd, tmp, 5);

    for (i = 4; i >=0; i--)
    {
        tmp75->temperature += ((float )(tmp[i] - '0')) / 1000 * n;
        n *= 10;
    }

    close(fd);

    return tmp75->temperature;
}

void tmp75_release(struct i2c_tmp75 *tmp75)
{
    free(tmp75);
}

