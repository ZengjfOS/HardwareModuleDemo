#include "../include/eeprom_detect.h"

struct eeprom_detect *eeprom_detect_init()
{
    struct eeprom_detect *eeprom_det;

    eeprom_det = (struct  eeprom_detect *)malloc(sizeof(struct eeprom_detect));
    if (eeprom_det == NULL)
        return NULL;

    memset(eeprom_det, 0, sizeof(struct eeprom_detect));

    strcpy(eeprom_det->write_data, WRITE_DATA);
    strcpy(eeprom_det->eeprom_device, EEPROM_DEVICE);

    eeprom_det->readorwrite = eeprom_detect_readorwrite;
    eeprom_det->read = eeprom_detect_read;
    eeprom_det->write = eeprom_detect_write;
    eeprom_det->result = eeprom_detect_result;
    eeprom_det->release = eeprom_detect_release;

    return eeprom_det;
}

int eeprom_detect_readorwrite(struct eeprom_detect *eeprom_det, int readorwrite)
{
    int eeprom_fd, retval = 0;

    eeprom_fd = open(eeprom_det->eeprom_device, O_RDWR);
    if (eeprom_fd < 0)
    {
        perror("open device error");
        return -1;
    }

    if (readorwrite)
    {
        retval = read(eeprom_fd, eeprom_det->read_data, sizeof(eeprom_det->read_data));
        if (retval < 0)
        {
            perror("read error");
        }
    }
    else
    {
        retval = write(eeprom_fd, eeprom_det->write_data, sizeof(eeprom_det->write_data));
        if (retval < 0)
        {
            perror("write error");
        }
    }

    close(eeprom_fd);

    return 0;
}

int eeprom_detect_read(struct eeprom_detect *eeprom_det)
{
    return eeprom_detect_readorwrite(eeprom_det, 1);
}

int eeprom_detect_write(struct eeprom_detect *eeprom_det)
{
    return eeprom_detect_readorwrite(eeprom_det, 0);
}

int eeprom_detect_result(struct eeprom_detect *eeprom_det)
{
    return strcmp(eeprom_det->read_data, eeprom_det->write_data);
}

void eeprom_detect_release(struct eeprom_detect *eeprom_det)
{
    free(eeprom_det);
}

