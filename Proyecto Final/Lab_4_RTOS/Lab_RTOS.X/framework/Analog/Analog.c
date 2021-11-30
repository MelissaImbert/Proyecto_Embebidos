/* ************************************************************************** */
/** Analog Input

  @File Name
    analog.h

  @Description
    Provee funcionalidad a nivel framework para el manejo del potenciometro
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */


#include "Analog.h"
#include <stdbool.h>
#include "../../mcc_generated_files/adc1.h"
#include "../../freeRTOS/include/FreeRTOS.h"
#include "../../freeRTOS/include/task.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/** Resultado de conversión

  @Description
    Contiene el último valor leído del ADC
 */
static uint16_t conversionResult;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/**
  @Function
    void ANALOG_convert( void *p_param )

  @Description
    Tarea de freeRTOS que se encarga de estar constantemente leyendo el valor
    del ADC
 */
void ANALOG_convert( void *p_param ) {
    while( 1 ) {
        ADC1_ChannelSelect(channel_POT);
        ADC1_Start();
        vTaskDelay(pdMS_TO_TICKS(5));
        ADC1_Stop();
        while( !ADC1_IsConversionComplete() ) {
            ADC1_Tasks();
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        conversionResult = ADC1_ConversionResultGet();
    }
}

/**
  @Function
    uint16_t ANALOG_getResult(void)

  @Description
    Obtiene el valor que se obtuvo del ADC
 */
uint16_t ANALOG_getResult( void ) {
    return conversionResult;
}


/* *****************************************************************************
 End of File
 */
