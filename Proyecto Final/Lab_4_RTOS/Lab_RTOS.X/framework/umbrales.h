/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _UMBRALES_H    /* Guard against multiple inclusion */
#define _UMBRALES_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    *
 **/
#include <stdint.h>
#include <stdbool.h>
#include "../freeRTOS/include/FreeRTOS.h"
#include "../freeRTOS/include/task.h"
#include "../freeRTOS/include/semphr.h"
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
extern uint8_t UMBRAL_BRUSCO;
extern uint8_t UMBRAL_CHOQUE;
extern xSemaphoreHandle xAccel;
extern xTaskHandle AccelHandle;
/* TODO:  Include other files here if needed. */
void definirUmbral(uint8_t umbral_set);
void leds_setting(uint8_t numero_de_leds);

#endif 
