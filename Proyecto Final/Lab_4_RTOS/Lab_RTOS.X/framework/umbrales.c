#include "umbrales.h"
#include "Analog/Analog.h"
#include "../leds.h"
#include "../platform/WS2812.h"
#include "task.h"
#include <string.h>
#include "../freeRTOS/include/FreeRTOS.h"
#include "../freeRTOS/include/task.h"
//#define LED_QTY_IN_ARRAY 8

static ws2812_t ledArray[LED_QTY_IN_ARRAY];

void definirUmbral(void){
    uint16_t numero_de_leds;
    do{
        uint16_t value = ANALOG_getResult();
        numero_de_leds = value/128;
        switch(numero_de_leds){
            case 0:
            ledArray[0]=BLUE;
            ledArray[1]=BLACK;
            ledArray[2]=BLACK;
            ledArray[3]=BLACK;
            ledArray[4]=BLACK;
            ledArray[5]=BLACK;
            ledArray[6]=BLACK;
            ledArray[7]=BLACK;
            break;
        case 1:
            ledArray[0]=BLUE;
            ledArray[1]=BLUE;
            ledArray[2]=BLACK;
            ledArray[3]=BLACK;
            ledArray[4]=BLACK;
            ledArray[5]=BLACK;
            ledArray[6]=BLACK;
            ledArray[7]=BLACK;
            break;
        case 2:
            ledArray[0]=BLUE;
            ledArray[1]=BLUE;
            ledArray[2]=BLUE;
            ledArray[3]=BLACK;
            ledArray[4]=BLACK;
            ledArray[5]=BLACK;
            ledArray[6]=BLACK;
            ledArray[7]=BLACK;
            break;
        case 3:
            ledArray[0]=BLUE;
            ledArray[1]=BLUE;
            ledArray[2]=BLUE;
            ledArray[3]=BLUE;
            ledArray[4]=BLACK;
            ledArray[5]=BLACK;
            ledArray[6]=BLACK;
            ledArray[7]=BLACK;
            break;
        case 4:
            ledArray[0]=BLUE;
            ledArray[1]=BLUE;
            ledArray[2]=BLUE;
            ledArray[3]=BLUE;
            ledArray[4]=BLUE;
            ledArray[5]=BLACK;
            ledArray[6]=BLACK;
            ledArray[7]=BLACK;
            break;    
        case 5:
            ledArray[0]=BLUE;
            ledArray[1]=BLUE;
            ledArray[2]=BLUE;
            ledArray[3]=BLUE;
            ledArray[4]=BLUE;
            ledArray[5]=BLUE;
            ledArray[6]=BLACK;
            ledArray[7]=BLACK;            
            break;
        case 6:
            ledArray[0]=BLUE;
            ledArray[1]=BLUE;
            ledArray[2]=BLUE;
            ledArray[3]=BLUE;
            ledArray[4]=BLUE;
            ledArray[5]=BLUE;
            ledArray[6]=BLUE;
            ledArray[7]=BLACK;
            break;    
        case 7:
            ledArray[0]=BLUE;
            ledArray[1]=BLUE;
            ledArray[2]=BLUE;
            ledArray[3]=BLUE;
            ledArray[4]=BLUE;
            ledArray[5]=BLUE;
            ledArray[6]=BLUE;
            ledArray[7]=BLUE;
            break;  
        default:
            ledArray[0]=BLACK;
            ledArray[1]=BLACK;
            ledArray[2]=BLACK;
            ledArray[3]=BLACK;
            ledArray[4]=BLACK;
            ledArray[5]=BLACK;
            ledArray[6]=BLACK;
            ledArray[7]=BLACK;
            break;
        }
        WS2812_send(ledArray, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(10));
    } while(1);
}