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
/* Section: Included Files                                                    */
#include <stdint.h>
#include "Analog/Analog.h"
#include "../leds.h"
#include <stdbool.h>

/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

/* Provide C++ Compatibility */
int dividir_umbrales(uint16_t valor);
void definir_umbral(void);
void relacion_adc_acelerometro_brusco(void);
void relacion_adc_acelerometro_choque(void);
void UMBRAL(int param);
#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
