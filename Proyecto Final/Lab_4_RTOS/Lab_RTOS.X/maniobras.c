#include "maniobras.h"
#include "freeRTOS/include/semphr.h"
#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"     
#include "leds.h"
#include <stdint.h>

float dato;
xSemaphoreHandle xAccel;

void Accel_Testing(void *p_param) {
    uint8_t accelstate;

    for (;;) {
        if (xSemaphoreTake(xAccel, portMAX_DELAY) == pdTRUE) {
            if (ACCEL_Mod(&dato) == true) {
                accelstate = velocity_Tester(&dato);
                LEDS_ALERT(&accelstate); //prendo leds segun estado de manejo
                //if (accelstate == 1 || accelstate == 2) { //si es manejo brusco o choque guardo asincronicamente
                // guardarDatos(&dato, &accelstate); //guardo datos manualmente, paso la acceleracion y el estado;
                //}
            }
            xSemaphoreGive(xAccel);
            vTaskDelay(pdMS_TO_TICKS(100)); //Testeo cada 500ms, ver si testear cada menos o mas despues
        }
    }
}

uint8_t velocity_Tester(float *dato) {
    if (*dato < 2) {
        return 0;
    } else if (*dato >= 2 && *dato < 4) {
        return 1;
    } else if (*dato >= 4) {
        return 2;
    }
    return 0;
}


