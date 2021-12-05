/* ************************************************************************** */
#include "data_save.h"
#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"
#include "freeRTOS/include/semphr.h"
#include "leds.h"
#include "maniobras.h"
#include <stdint.h>
#include "time.h"
#include "framework/GPS.h"
#include "framework/SIM808.h"
#include "platform/utils.h"
#include "mcc_generated_files/rtcc.h"
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#define RTCC_ACTUALIZATION 60000
/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
static GPSPosition_t GPSpos;
static struct tm GPStime;
static ut_tmrDelay_t timer = {.state = UT_TMR_DELAY_INIT};

void data_saving(void *p_param) {
    for (;;) {
        //data_GPS();
        //Aca se guardaria los datos pero me falta la el buffer jej
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void data_GPS(void) {
    static uint8_t tramaGPS[110];
    xSemaphoreTake(c_semGPSIsReady, portMAX_DELAY);
    if (SIM808_getNMEA(tramaGPS)) {
        if (SIM808_validateNMEAFrame(tramaGPS)) {
            GPS_getPosition(&GPSpos, tramaGPS);
            GPS_getUTC(&GPStime, tramaGPS);
            if (UT_delayms(&timer, RTCC_ACTUALIZATION)) {
                // Si pasó el tiempo especificado, actualizo RTCC con los datos del gps
                RTCC_TimeSet(&GPStime);
            }
        } else {
            RTCC_TimeGet(&GPStime);
            GPSpos.latitude = 500;
            GPSpos.longitude = 500;
        }
    } else {
        RTCC_TimeGet(&GPStime);
        GPSpos.latitude = 500;
        GPSpos.longitude = 500;
    }
}


/*
  TAMAÑO DE DATOS:
 * Latitude: double (8 bytes)
 * Longitud: double (8 bytes)
 * Time: unsigned long (4 bytes)
 * Patron: uint8_t (indicara 0,1 o 2 siendo manejo normal, brusco y choque respectivamente) 
 * Por cada guardado necesito 21 bytes. 
 */
void datalog(void) {

}
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

