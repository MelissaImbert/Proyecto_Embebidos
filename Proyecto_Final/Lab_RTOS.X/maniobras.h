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

#ifndef _MANIOBRAS_H    /* Guard against multiple inclusion */
#define _MANIOBRAS_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files   */
#include <stdint.h>
#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"
#include "framework/Accelerometer/Accelerometer.h"
#include "freeRTOS/include/semphr.h"
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
extern float dato;
extern xSemaphoreHandle xAccel;
/* TODO:  Include other files here if needed. */

void Accel_Testing(void *p_param);
uint8_t velocity_Tester(float *dato);
#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
