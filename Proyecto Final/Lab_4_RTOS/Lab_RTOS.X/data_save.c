/* ************************************************************************** */
#include "data_save.h"
#include "leds.h"
#include "maniobras.h"
#include <stdint.h>
#include "time.h"
#include "framework/GPS.h"
#include "platform/utils.h"
#include "mcc_generated_files/rtcc.h"
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#define RTCC_ACTUALIZATION 600000
/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
static GPSPosition_t GPSpos;
static struct tm GPStime;
static ut_tmrDelay_t timer = {.state = UT_TMR_DELAY_INIT};

void data_GPS(void) {
    static uint8_t tramaGPS[110];
    if (xSemaphoreTake(c_semGPSIsReady, portMAX_DELAY) == pdTRUE) {
        if (SIM808_getNMEA(tramaGPS)) {
            if (SIM808_validateNMEAFrame(tramaGPS)) {
                GPS_getPosition(&GPSpos, tramaGPS);
                GPS_getUTC(&GPStime, tramaGPS);
                if (UT_delayms(&timer, RTCC_ACTUALIZATION)) {
                    // Si pasó el tiempo especificado, actualizo RTCC con los datos del gps
                    RTCC_TimeSet(&GPStime);
                }
                xSemaphoreGive(c_semGPSIsReady);
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
}

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

