#include "umbrales.h"
#include "Analog/Analog.h"
#include "../leds.h"
#include "../platform/WS2812.h"
#include "task.h"
#include <string.h>
#include "../mcc_generated_files/pin_manager.h"
#include "UserInterface.h"
#include "usb_framework.h"
//#define LED_QTY_IN_ARRAY 8

static ws2812_t ledArray[LED_QTY_IN_ARRAY];

uint8_t UMBRAL_BRUSCO = 0;
uint8_t UMBRAL_CHOQUE = 0;
xSemaphoreHandle xAccel;
xTaskHandle AccelHandle;

void definirUmbral(uint8_t umbral_set) {
    uint16_t numero_de_leds;

    do {
        uint16_t value = ANALOG_getResult();
        numero_de_leds = value / 128;
        switch (umbral_set) {
            case 0:
                if (numero_de_leds > UMBRAL_BRUSCO) {
                    leds_setting(numero_de_leds);
                    UMBRAL_CHOQUE = numero_de_leds;
                } else {
                    UMBRAL_CHOQUE = UMBRAL_BRUSCO + 1;
                    leds_setting(UMBRAL_CHOQUE);
                }
                break;
            case 1:
                if (numero_de_leds < UMBRAL_CHOQUE) {
                    leds_setting(numero_de_leds);
                    UMBRAL_BRUSCO = numero_de_leds;
                } else {
                    UMBRAL_BRUSCO = UMBRAL_CHOQUE - 1;
                    leds_setting(UMBRAL_BRUSCO);
                }
                break;
            default:
                leds_setting(9);
                break;
        }
    } while (!BTN1_GetValue());
}

void leds_setting(uint8_t numero_de_leds) {
    switch (numero_de_leds) {
        case 0:
            ledArray[0] = BLUE;
            ledArray[1] = BLACK;
            ledArray[2] = BLACK;
            ledArray[3] = BLACK;
            ledArray[4] = BLACK;
            ledArray[5] = BLACK;
            ledArray[6] = BLACK;
            ledArray[7] = BLACK;
            break;
        case 1:
            ledArray[0] = BLUE;
            ledArray[1] = BLUE;
            ledArray[2] = BLACK;
            ledArray[3] = BLACK;
            ledArray[4] = BLACK;
            ledArray[5] = BLACK;
            ledArray[6] = BLACK;
            ledArray[7] = BLACK;
            break;
        case 2:
            ledArray[0] = BLUE;
            ledArray[1] = BLUE;
            ledArray[2] = BLUE;
            ledArray[3] = BLACK;
            ledArray[4] = BLACK;
            ledArray[5] = BLACK;
            ledArray[6] = BLACK;
            ledArray[7] = BLACK;
            break;
        case 3:
            ledArray[0] = BLUE;
            ledArray[1] = BLUE;
            ledArray[2] = BLUE;
            ledArray[3] = BLUE;
            ledArray[4] = BLACK;
            ledArray[5] = BLACK;
            ledArray[6] = BLACK;
            ledArray[7] = BLACK;
            break;
        case 4:
            ledArray[0] = BLUE;
            ledArray[1] = BLUE;
            ledArray[2] = BLUE;
            ledArray[3] = BLUE;
            ledArray[4] = BLUE;
            ledArray[5] = BLACK;
            ledArray[6] = BLACK;
            ledArray[7] = BLACK;
            break;
        case 5:
            ledArray[0] = BLUE;
            ledArray[1] = BLUE;
            ledArray[2] = BLUE;
            ledArray[3] = BLUE;
            ledArray[4] = BLUE;
            ledArray[5] = BLUE;
            ledArray[6] = BLACK;
            ledArray[7] = BLACK;
            break;
        case 6:
            ledArray[0] = BLUE;
            ledArray[1] = BLUE;
            ledArray[2] = BLUE;
            ledArray[3] = BLUE;
            ledArray[4] = BLUE;
            ledArray[5] = BLUE;
            ledArray[6] = BLUE;
            ledArray[7] = BLACK;
            break;
        case 7:
            ledArray[0] = BLUE;
            ledArray[1] = BLUE;
            ledArray[2] = BLUE;
            ledArray[3] = BLUE;
            ledArray[4] = BLUE;
            ledArray[5] = BLUE;
            ledArray[6] = BLUE;
            ledArray[7] = BLUE;
            break;
        default:
            ledArray[0] = BLACK;
            ledArray[1] = BLACK;
            ledArray[2] = BLACK;
            ledArray[3] = BLACK;
            ledArray[4] = BLACK;
            ledArray[5] = BLACK;
            ledArray[6] = BLACK;
            ledArray[7] = BLACK;
            break;
    }
    WS2812_send(ledArray, LED_QTY_IN_ARRAY);
    vTaskDelay(pdMS_TO_TICKS(10));
}