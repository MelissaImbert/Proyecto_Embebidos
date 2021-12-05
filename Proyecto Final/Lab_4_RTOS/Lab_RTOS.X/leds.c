#include "leds.h"
#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"
#include "platform/WS2812.h"
#include "freeRTOS/include/semphr.h"
#include "framework/umbrales.h"

static ws2812_t ledArray[LED_QTY_IN_ARRAY];
static ws2812_t ledArray_Black[LED_QTY_IN_ARRAY];
static ws2812_t ledArray_Green[LED_QTY_IN_ARRAY];
static ws2812_t ledArray_Yellow[LED_QTY_IN_ARRAY];
static ws2812_t ledArray_Red[LED_QTY_IN_ARRAY];


void Array_Colors(void) {
    for (int i = 0; i <= LED_QTY_IN_ARRAY; i++) {
        ledArray_Black[i] = BLACK;
    }
    for (int i = 0; i <= LED_QTY_IN_ARRAY; i++) {
        ledArray_Green[i] = GREEN;
    }
    for (int i = 0; i <= LED_QTY_IN_ARRAY; i++) {
        ledArray_Yellow[i] = YELLOW;
    }
    for (int i = 0; i <= LED_QTY_IN_ARRAY; i++) {
        ledArray_Red[i] = RED;
    }
    return;
}

void LEDS_ALERT(uint8_t *patron) {
    struct tm currentTime;

    //hay quue chequear si El índice velocidad es valido?

    switch (*patron) {
        case 0:
            WS2812_send(ledArray_Green, LED_QTY_IN_ARRAY); //pongo rgb en verde
            break;

        case 1:
            xTaskCreate(blinkLED_YELLOW, "task_parpadeo_brusco", 100, NULL, tskIDLE_PRIORITY + 3, NULL);
            //Creo tarea para parpadear 3 veces rgb's en amarillo
            break;

        case 2:
            xTaskCreate(blinkLED_RED, "task_parpadeo_choque", 100, NULL, tskIDLE_PRIORITY + 3, NULL);
            //Creo tarea para parpadear RGBS's 3 veces en rojo
            break;

        default:
            return;
    }


    /* Almacena los datos como el último evento de modificación de LED RGB
    led_lastEvent.index = p_index;
    led_lastEvent.color = p_color;
    RTCC_TimeGet(&currentTime);
    currentTime.tm_mon -= 1; // RTCC_TimeGet devuelve el mes entre 1 y 12, mktime lo espera entre 0 y 12
    currentTime.tm_year += 100; // RTCC_TimeGet devuelve el año desde el 2000, mktime lo espera desde el 1900
    led_lastEvent.time = mktime(&currentTime);*/

}

void blinkLED_YELLOW(void *p_param) {
    for (;;) {
        if(xSemaphoreTake(xAccel, portMAX_DELAY)== pdTRUE){
        WS2812_send(ledArray_Black, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Yellow, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Black, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Yellow, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Black, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Yellow, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));
        
        xSemaphoreGive(xAccel);
        vTaskDelete(NULL);
        }
    }
}


void blinkLED_RED(void *p_param) {
    for (;;) {
        if(xSemaphoreTake(xAccel, portMAX_DELAY)== pdTRUE){
        WS2812_send(ledArray_Black, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Red, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Black, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Red, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Black, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));

        WS2812_send(ledArray_Red, LED_QTY_IN_ARRAY);
        vTaskDelay(pdMS_TO_TICKS(150));
        
        xSemaphoreGive(xAccel);
        vTaskDelete(NULL);
        }
    }
}
