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

#ifndef _USERINTERFACE_H    /* Guard against multiple inclusion */
#define _USERINTERFACE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files       */
#include <stdint.h>
#include "../freeRTOS/include/FreeRTOS.h"
#include "../freeRTOS/include/task.h"
#include "../freeRTOS/include/semphr.h"
#include "../mcc_generated_files/pin_manager.h"
/* ************************************************************************** */
/* ************************************************************************** */
extern SemaphoreHandle_t xpuedoEnviar;
extern SemaphoreHandle_t xpuedoRecibir;
extern SemaphoreHandle_t xopenInterface;

typedef enum {
    DOWNLOAD,
    THRESHOLDS,
    PERIOD,
    LEAVE
} MENU_STATES;

typedef enum {
    CHOQUE,
    BRUSCO
} MENU_STATES2;

/* This section lists the other files that are included in this file.
 */
void _puedoEnviar(void *p_param);
void puedoRecibir(void *p_param);
void interface(void);
void initInterface(void *p_param);
/* TODO:  Include other files here if needed. */


#endif 