#include "eeprom_detect.h"

int main(void)
{
    struct eeprom_detect *eeprom_det;
    int retval;

    eeprom_det = eeprom_detect_init();

    eeprom_det->write(eeprom_det);

    eeprom_det->read(eeprom_det);

    retval = eeprom_det->result(eeprom_det);
    if (!retval)
        printf(" detect eeprom ok\n");
    else
        printf(" detect eeprom errno ...\n");

    eeprom_det->release(eeprom_det);

    return 0;
}
