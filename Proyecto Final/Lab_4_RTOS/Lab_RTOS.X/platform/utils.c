/* ************************************************************************** */
/** Utilities

  @File Name
    utils.c

  @Description
    Este archivo provee funciones de utilidad de lenguage C, de manera
    independiente de la plataforma que se esté utilizando (a excepción de
    UT_delayms)
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "utils.h"
#include "../mcc_generated_files/tmr2.h"
#include "../mcc_generated_files/rtcc.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */



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
    bool UT_delayms(ut_tmrDelay_t *p_timer, uint32_t p_ms)

  @Summary
    Permite realizar un delay en cantidad de milisegundos
 */
bool UT_delayms( ut_tmrDelay_t *p_timer, uint32_t p_ms ) {

    switch( p_timer->state ) {

            /* Estado inicial, en donde se toma el valor del Timer 2 al momento
             de comenzar el delay */
        case UT_TMR_DELAY_INIT:
            p_timer->startValue = TMR2_SoftwareCounterGet();
            p_timer->state = UT_TMR_DELAY_WAIT;
            break;

            /* En este estádo se chequea que el tiempo transcurrido desde el
             comienzo del delay sea igual o mayor que el tiempo especificado*/
        case UT_TMR_DELAY_WAIT:
            if( (TMR2_SoftwareCounterGet() - p_timer->startValue) >= p_ms ) {
                /* Se resetea la variable de estado para estar listo para la
                 nueva llamada del  delay */
                p_timer->state = UT_TMR_DELAY_INIT;
                return true; // Ya transcurrió el tiempo especificado
            }
            break;

        default:
            /* Si por error la máquina de estados cae en default, se resetea la
             variable de estado para que el delay comience nuevamente */
            p_timer->state = UT_TMR_DELAY_INIT;
    }
    return false; // Aún no transcurrió el tiempo especificado
}

/**
  @Function
    bool UT_validateDate(int p_day, int p_mon, int p_year)

  @Summary
    Verifica que la fecha pasada como parámetro sea válida
 */
bool UT_validateDate( int p_day, int p_mon, int p_year ) {
    // Chequea el año
    if( p_year >= 1900 && p_year <= 9999 ) {
        // Chequea el mes
        if( p_mon >= 1 && p_mon <= 12 ) {
            // Chequea el día
            if( (p_day >= 1 && p_day <= 31) && (p_mon == 1 || p_mon == 3 || p_mon == 5 || p_mon == 7 || p_mon == 8 || p_mon == 10 || p_mon == 12) )
                return true;
            else if( (p_day >= 1 && p_day <= 30) && (p_mon == 4 || p_mon == 6 || p_mon == 9 || p_mon == 11) )
                return true;
            else if( (p_day >= 1 && p_day <= 28) && (p_mon == 2) )
                return true;
            else if( p_day == 29 && p_mon == 2 && (p_year % 400 == 0 || (p_year % 4 == 0 && p_year % 100 != 0)) )
                return true;
            else
                return false;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

/**
  @Function
    bool UT_validateTime(int p_hour, int p_min)

  @Summary
    Verifica que la hora pasada como parámetro sea válida
 */
bool UT_validateTime( int p_hour, int p_min ) {
    // Chequea la hora
    if( p_hour >= 0 && p_hour < 24 ) {
        // Chequea los minutos
        if( p_min >= 0 && p_min < 60 ) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

/**
  @Function
    void UT_setRTCC(struct tm p_time)

  @Summary
    Configura la fecha y hora en el periférico RTCC
 */
void UT_setRTCC( struct tm p_time ) {
    p_time.tm_year -= 100;
    p_time.tm_mon += 1;

    RTCC_TimeSet(&p_time);
}

/**
  @Function
    void UT_getRTCC(struct tm *p_time)

  @Summary
    Obtiene la fecha y hora del periférico RTCC
 */
void UT_getRTCC( struct tm *p_time ) {
    RTCC_TimeGet(p_time);

    p_time->tm_year += 100;
    p_time->tm_mon -= 1;
}

/* *****************************************************************************
 End of File
 */
