/* ************************************************************************** */
#include "data_save.h"
#include "leds.h"
#include "maniobras.h"
#include <stdint.h>
#include "time.h"
#include "framework/GPS.h"
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
static  GPSPosition_t GPSpos; 
static struct tm GPStime;

void data_GPS(void){
    static uint8_t tramaGPS[110];
    if (xSemaphoreTake(c_semGPSIsReady, portMAX_DELAY)== pdTRUE){
        if(SIM808_getNMEA(tramaGPS)){
            if(SIM808_validateNMEAFrame(tramaGPS)){
                GPS_getPosition(&GPSpos, tramaGPS);
                GPS_getUTC(&GPStime, tramaGPS);
                //Ver cuando setear RTCC
                xSemaphoreGive(c_semGPSIsReady);
            } else {
                //Ver que hago cuando no recibo nada
            }
        }
    }
}

void datalog(void){
    uint8_t googlemaps[300];
    GPS_generateGoogleMaps( googlemaps, GPSpos );
    
}
/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

