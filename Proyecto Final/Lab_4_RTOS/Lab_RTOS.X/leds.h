#ifndef _LEDS_H_    /* Guard against multiple inclusion */
#define _LEDS_H_

#include <time.h>
#include <stdint.h>

#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/semphr.h"

#define LED_QTY_IN_ARRAY 8    

void LEDS_ALERT(uint8_t *patron);    
void Array_Colors (void);
void blinkLED_YELLOW(void *p_param);
void blinkLED_RED(void *p_param);
#endif