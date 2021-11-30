/* ************************************************************************** */
/** Utilities

  @File Name
    utils.h

  @Description
    Este archivo provee funciones de utilidad de lenguage C, de manera
    independiente de la plataforma que se esté utilizando (a excepción de
    UT_delayms)
 */
/* ************************************************************************** */

#ifndef _UTILS_H    /* Guard against multiple inclusion */
#define _UTILS_H

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

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

/** Estados posibles para UT_delayms

  @Description
    La función UT_delayms tiene una estructura de máquina de estados y funciona
    de manera no bloqueante. Este enum provee las etiquetas de los posibles
    estados de dicha máquina
 */
typedef enum {
    UT_TMR_DELAY_INIT,
    UT_TMR_DELAY_WAIT
} UT_TMR_DELAY_STATE;

/** Estructura "timer" para utilizar UT_delayms

  @Description
    Cada variable de este tipo funciona a modo de "objeto" que mantiene el
    contexto de cada uso de la función UT_delayms
 */
typedef struct {
    uint32_t startValue; // Valor del timer al momento de iniciar el delay
    UT_TMR_DELAY_STATE state; // Estado en el que se encuentra la máquina
} ut_tmrDelay_t;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/**
  @Function
    bool UT_delayms(ut_tmrDelay_t *p_timer, uint32_t p_ms)

  @Summary
    Permite realizar un delay en cantidad de milisegundos

  @Description
    Esta función funciona de manera no bloqueante. Trabaja en función de un
    contexto (pasado a través de p_timer) y chequea si el tiempo especificado
    transcurrió o no

  @Precondition
    El periférico Timer 2 del microcontrolador debe estár configurado en el
    MCC (Microchip Code Configurator) y seteado con un período de 1 milisegundo
    y las interrupciones del Timer 2 deben estár habilitadas.
    Además, el elemento "count" de la estructura "TMR_OBJ" del archivo tmr2.c
    generado por el MCC debe ser del tipo "uint32_t". La función
    "TMR2_SoftwareCounterGet" de ese mismo archivo debe retornar "uint32_t"

  @Parameters
    @param p_timer  Puntero a variable que mantiene el contexto del delay deseado

    @param p_ms     Cantidad de milisegundos que se desea esperar

  @Returns
    <ul>
      <li>true  Transcurrió el tiempo especificado
      <li>false Aún no transcurrió el tiempo especificado
    </ul>

  @Example
    @code
    static ut_tmrDelay_t exampleTimer = { .state = UT_TMR_DELAY_INIT };

    while(1) {
        // Encender LED
        while( !UT_delayms( &exampleTimer, 500 ) );
        // Apagar LED
        while( !UT_delayms( &exampleTimer, 1000 ) );
    }
 */
bool UT_delayms(ut_tmrDelay_t *p_timer, uint32_t p_ms);

/**
  @Function
    bool UT_validateDate(int p_day, int p_mon, int p_year)

  @Summary
    Verifica que la fecha pasada como parámetro sea válida

  @Description
    Verifica que la fecha pasada como parámetro sea válida según el calendario
    gregoriano

  @Precondition
    Ninguna

  @Parameters
    @param p_day  Día del mes (del 1 al 31)

    @param p_mon  Mes del año (del 1 al 12)

    @param p_year Año (en formato AAAA, ej.: 2021)

  @Returns
    <ul>
      <li>true  La fecha es válida
      <li>false La fecha no es válida
    </ul>

  @Remarks
    Esta función fue obtenida (y adaptada) de la siguiente URL:
    https://www.includehelp.com/c-programs/validate-date.aspx

  @Example
    @code
    struct tm dt;

    sscanf( exampleBufferDate, "%u/%u/%u", &(dt.tm_mday), &(dt.tm_mon), &(dt.tm_year) );
    sscanf( exampleBufferTime, "%u:%u", &(dt.tm_hour), &(dt.tm_min) );

    if( UT_validateDate(dt.tm_mday, dt.tm_mon, dt.tm_year) && UT_validateTime(dt.tm_hour, dt.tm_min) ) {
        // Almacenar hora en RTC
    }
 */
bool UT_validateDate(int p_day, int p_mon, int p_year);

/**
  @Function
    bool UT_validateTime(int p_hour, int p_min)

  @Summary
    Verifica que la hora pasada como parámetro sea válida

  @Description
    Verifica que la hora pasada como parámetro sea válida

  @Precondition
    Ninguna

  @Parameters
    @param p_hour   Hora (en formato 24hs, de 0 a 23)

    @param p_min    Minuto (de 0 a 59)

  @Returns
    <ul>
      <li>true  La hora es válida
      <li>false La hora no es válida
    </ul>

  @Example
    @code
    struct tm dt;

    sscanf( exampleBufferDate, "%u/%u/%u", &(dt.tm_mday), &(dt.tm_mon), &(dt.tm_year) );
    sscanf( exampleBufferTime, "%u:%u", &(dt.tm_hour), &(dt.tm_min) );

    if( UT_validateDate(dt.tm_mday, dt.tm_mon, dt.tm_year) && UT_validateTime(dt.tm_hour, dt.tm_min) ) {
        // Almacenar hora en RTC
    }
 */
bool UT_validateTime(int p_hour, int p_min);

/**
  @Function
    void UT_setRTCC(struct tm p_time)

  @Summary
    Configura la fecha y hora en el periférico RTCC

  @Description
    El formato estándar para almacenar fechas en un struct tm es con el mes
    entre 0 y 11 y el año contando desde el 1900. Las funciones que provee el
    Microchip Code Configurator (MCC) utilizan el mes entre 1 y 12 y el año
    contando desde el 2000. Está función hace de interfaz con la función que
    provee el RTCC para que la estructura obtenida esté en el formato estándar

  @Precondition
    El periférico RTCC tiene que estar configurado en el Microchip Code
    Configurator (MCC)

  @Parameters
    @param p_time   Estructura que se desea almacenar, con el mes y año en
                    en formato estándar

  @Returns
    Ninguno

  @Example
    @code
    struct tm hardcodedTime;

    // Se configura la fecha y hora 20:15 del 6 de mayo de 2021
    hardcodedTime.tm_min = 15;
    hardcodedTime.tm_hour = 20;
    hardcodedTime.tm_mday = 6;
    hardcodedTime.tm_mon = 4;
    hardcodedTime.tm_year = 2021 - 1900;

    UT_setRTCC(hardcodedTime);
    }
 */
void UT_setRTCC(struct tm p_time);

/**
  @Function
    void UT_getRTCC(struct tm *p_time)

  @Summary
    Obtiene la fecha y hora del periférico RTCC

  @Description
    El formato estándar para almacenar fechas en un struct tm es con el mes
    entre 0 y 11 y el año contando desde el 1900. Las funciones que provee el
    Microchip Code Configurator (MCC) utilizan el mes entre 1 y 12 y el año
    contando desde el 2000. Está función hace de interfaz con la función que
    provee el RTCC para que la estructura que se obtenga esté en el formato
    estándar

  @Precondition
    El periférico RTCC tiene que estar configurado en el Microchip Code
    Configurator (MCC)

  @Parameters
    @param p_time   Puntero a la estructura donde se va a escribir la fecha y
                    hora obtenida

  @Returns
    Ninguno

  @Example
    @code
    struct tm hardcodedTime;

    UT_getRTCC(&hardcodedTime);
    }
 */
void UT_getRTCC(struct tm *p_time);

#endif /* _UTILS_H */

/* *****************************************************************************
 End of File
 */
