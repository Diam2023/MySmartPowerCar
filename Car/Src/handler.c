#include "handler.h"
#include <string.h>
#include <memory.h>

extern DRIVER *driver;

void ReceivedMessageHandler(void *recivedData)
{
    if (recivedData == NULL)
    {
        return;
    }

    RecivedStruct_t *recived = (RecivedStruct_t *)recivedData;

    double rotateValue   = ((short)((recived->rotate - 100.0) / 10)) / 10.0;
    double straightValue = ((short)((recived->straight - 100.0) / 10)) / 10.0;
    DriverCar(driver, rotateValue, straightValue);

    memset(recived, 0, sizeof(RecivedStruct_t));

    free(recived);
}
