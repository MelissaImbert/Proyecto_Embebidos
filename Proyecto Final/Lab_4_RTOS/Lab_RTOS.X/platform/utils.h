/* ************************************************************************** */
/** Utilities

  @File Name
    utils.h

  @Description
    Este archivo provee funciones de utilidad de lenguage C, de manera
    independiente de la plataforma que se est� utilizando (a excepci�n de
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
    La funci�n UT_delayms tiene una estructura de m�quina de estados y funciona
    de manera no bloqueante. Este enum provee las etiquetas de los posibles
    estados de dicha m�quina
 */
typedef enum {
    UT_TMR_DELAY_INIT,
    UT_TMR_DELAY_WAIT
} UT_TMR_DELAY_STATE;

/** Estructura "timer" para utilizar UT_delayms

  @Description
    Cada variable de este tipo funciona a modo de "objeto" que mantiene el
    contexto de cada uso de la funci�n UT_delayms
 */
typedef struct {
    uint32_t startValue; // Valor del timer al momento de iniciar el delay
    UT_TMR_DELAY_STATE state; // Estado en el que se encuentra la m�quina
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
    Esta funci�n funciona de manera no bloqueante. Trabaja en funci�n de un
    contexto (pasado a trav�s de p_timer) y chequea si el tiempo especificado
    transcurri� o no

  @Precondition
    El perif�rico Timer 2 del microcontrolador debe est�r configurado en el
    MCC (Microchip Code Configurator) y seteado con un per�odo de 1 milisegundo
    y las interrupciones del Timer 2 deben est�r habilitadas.
    Adem�s, el elemento "count" de la estructura "TMR_OBJ" del archivo tmr2.c
    generado por el MCC debe ser del tipo "uint32_t". La funci�n
    "TMR2_SoftwareCounterGet" de ese mismo archivo debe retornar "uint32_t"

  @Parameters
    @param p_timer  Puntero a variable que mantiene el contexto del delay deseado

    @param p_ms     Cantidad de milisegundos que se desea esperar

  @Returns
    <ul>
      <li>true  Transcurri� el tiempo especificado
      <li>false A�n no transcurri� el tiempo especificado
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
    Verifica que la fecha pasada como par�metro sea v�lida

  @Description
    Verifica que la fecha pasada como par�metro sea v�lida seg�n el calendario
    gregoriano

  @Precondition
    Ninguna

  @Parameters
    @param p_day  D�a del mes (del 1 al 31)

    @param p_mon  Mes del a�o (del 1 al 12)

    @param p_year A�o (en formato AAAA, ej.: 2021)

  @Returns
    <ul>
      <li>true  La fecha es v�lida
      <li>false La fecha no es v�lida
    </ul>

  @Remarks
    Esta funci�n fue obtenida (y adaptada) de la siguiente URL:
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
    Verifica que la hora pasada como par�metro sea v�lida

  @Description
    Verifica que la hora pasada como par�metro sea v�lida

  @Precondition
    Ninguna

  @Parameters
    @param p_hour   Hora (en formato 24hs, de 0 a 23)

    @param p_min    Minuto (de 0 a 59)

  @Returns
    <ul>
      <li>true  La hora es v�lida
      <li>false La hora no es v�lida
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
    Configura la fecha y hora en el perif�rico RTCC

  @Description
    El formato est�ndar para almacenar fechas en un struct tm es con el mes
    entre 0 y 11 y el a�o contando desde el 1900. Las funciones que provee el
    Microchip Code Configurator (MCC) utilizan el mes entre 1 y 12 y el a�o
    contando desde el 2000. Est� funci�n hace de interfaz con la funci�n que
    provee el RTCC para que la estructura obtenida est� en el formato est�ndar

  @Precondition
    El perif�rico RTCC tiene que estar configurado en el Microchip Code
    Configurator (MCC)

  @Parameters
    @param p_time   Estructura que se desea almacenar, con el mes y a�o en
                    en formato est�ndar

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
    Obtiene la fecha y hora del perif�rico RTCC

  @Description
    El formato est�ndar para almacenar fechas en un struct tm es con el mes
    entre 0 y 11 y el a�o contando desde el 1900. Las funciones que provee el
    Microchip Code Configurator (MCC) utilizan el mes entre 1 y 12 y el a�o
    contando desde el 2000. Est� funci�n hace de interfaz con la funci�n que
    provee el RTCC para que la estructura que se obtenga est� en el formato
    est�ndar

  @Precondition
    El perif�rico RTCC tiene que estar configurado en el Microchip Code
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
