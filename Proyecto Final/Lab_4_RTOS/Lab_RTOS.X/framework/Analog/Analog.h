/* ************************************************************************** */
/** Analog Input

  @File Name
    analog.h

  @Description
    Provee funcionalidad a nivel framework para el manejo del potenciometro
 */
/* ************************************************************************** */

#ifndef _ANALOG_H    /* Guard against multiple inclusion */
#define _ANALOG_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/**
  @Function
    void ANALOG_convert( void *p_param )

  @Description
    Tarea de freeRTOS que se encarga de estar constantemente leyendo el valor
    del ADC

  @Precondition
    La entrada del ADC a leer debe ser configurada en el MCC y ser nombrada channel_POT

  @Parameters
    @param p_param  No se utiliza, pero se precisa para poder crear una tarea a
                    partir de esta tarea

  @Returns
    Ninguno

  @Remarks
    Ninguno

  @Example
    @code
    xTaskCreate( ANALOG_convert, "ADC convert", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL );
 */
void ANALOG_convert(void *p_param);

/**
  @Function
    uint16_t ANALOG_getResult(void)

  @Description
    Obtiene el valor que se obtuvo del ADC

  @Precondition
    La entrada del ADC a leer debe ser configurada en el MCC, ser nombrada
    channel_POT y debe haber una tarea definida y corriendo periódicamente a
    partir de la función ANALOG_convert

  @Parameters
    Ninguno

  @Returns
    Valor leído del ADC (entre 0 y 1023)

  @Remarks
    Ninguno

  @Example
    @code
    uint16_t potValue;
    potValue = ANALOG_getResult();
 */
uint16_t ANALOG_getResult(void);

#endif /* _ANALOG_H */

/* *****************************************************************************
 End of File
 */
