#include "UserInterface.h"
#include "usb_framework.h"
#include "../mcc_generated_files/usb/usb.h"
#include "../mcc_generated_files/usb/usb_device_cdc.h"
#include "umbrales.h"
#include <stdlib.h>

SemaphoreHandle_t xpuedoEnviar;
SemaphoreHandle_t xpuedoRecibir;
//SemaphoreHandle_t xopenInterface;

void puedoRecibir(void *p_param) {
    for (;;) {
        if (USB_isReady()) {
            if (USB_recieve() > 0) {
                xSemaphoreGive(xpuedoRecibir);
                vTaskDelete(NULL);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void _puedoEnviar(void *p_param) {
    for (;;) {
        if (USB_isReady()) {
            if (USBUSARTIsTxTrfReady()) {
                xSemaphoreGive(xpuedoEnviar);
                vTaskDelete(NULL);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void initInterface(void *p_param) {
    for (;;) {
        //xSemaphoreTake(xopenInterface, portMAX_DELAY);
        if (USB_isReady()) {
            if (USB_recieve() > 0) {
                xTaskCreate(interface, "task3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
                vTaskDelete(NULL);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void interface(void *p_param) {
    MENU_STATES state;
    MENU_STATES2 umbral;
    MENU_STATES2 umbral_aux;
    for (;;) {
        xTaskCreate(_puedoEnviar, "task4", 100, NULL, 2, NULL);
        if (xSemaphoreTake(xpuedoEnviar, portMAX_DELAY) == pdTRUE) {
            USB_sendString("\n\nMENÚ PRINCIPAL - Ingrese la opción deseada\n"
                    "1 - Descargar datos\n"
                    "2 - Configurar umbrales\n"
                    "3 - Configurar periodo de captura de datos\n");

        }
        xTaskCreate(puedoRecibir, "task4", 100, NULL, 2, NULL);
        if (xSemaphoreTake(xpuedoRecibir, portMAX_DELAY) == pdTRUE) {
            state = atoi(USB_getRxBuffer()) - 1;
            switch (state) {
                case DOWNLOAD:
                    xTaskCreate(_puedoEnviar, "task4", 100, NULL, 2, NULL);
                    if (xSemaphoreTake(xpuedoEnviar, portMAX_DELAY) == pdTRUE) {
                        USB_sendString("\n\nLISTA DE DATOS DEL GPS\n");
                    }
                    break;
                case THRESHOLDS:
                    xTaskCreate(_puedoEnviar, "task4", 100, NULL, 2, NULL);
                    if (xSemaphoreTake(xpuedoEnviar, portMAX_DELAY) == pdTRUE) {
                        USB_sendString("\n\nCONFIGURACIÓN DE UMBRALES - Seleccione el umbral que desea configurar\n"
                                "1 - Movimiento brusco\n"
                                "2 - Choque\n"
                                );

                    }
                    xTaskCreate(puedoRecibir, "task4", 100, NULL, 2, NULL);
                    if (xSemaphoreTake(xpuedoRecibir, portMAX_DELAY) == pdTRUE) {
                        umbral = atoi(USB_getRxBuffer()) - 1;

                        switch (umbral) {
                            case BRUSCO:
                              /*  xTaskCreate(_puedoEnviar, "task4", 100, NULL, 2, NULL);
                                if (xSemaphoreTake(xpuedoEnviar, portMAX_DELAY) == pdTRUE) {
                                    USB_sendString("\n\nConfiguración del umbral para movimiento brusco\n"
                                            "Gire la perilla del dispositivo hasta el valor que desee, y apriete el botón S2 para indicar que finalizó la configuración\n"
                                            );

                                }*/
                                definirUmbral();
                                //Umbral =  definirUmbral(); 
                                break;
                            case CHOQUE:
                                /*xTaskCreate(_puedoEnviar, "task4", 100, NULL, 2, NULL);
                                if (xSemaphoreTake(xpuedoEnviar, portMAX_DELAY) == pdTRUE) {
                                    USB_sendString("\n\nConfiguración del umbral para choque\n"
                                            "Gire la perilla del dispositivo hasta el valor que desee, y apriete el botón S2 para indicar que finalizó la configuración\n"
                                            );

                                }*/
                                definirUmbral();
                                //Umbral =  definirUmbral();
                                break;

                        }
                    }


                    break;
                case PERIOD:
                    xTaskCreate(_puedoEnviar, "task4", 100, NULL, 2, NULL);
                    if (xSemaphoreTake(xpuedoEnviar, portMAX_DELAY) == pdTRUE) {
                        USB_sendString("\n\nIngrese el período de logeo del gps (en milisegundos)\n");

                    }
                    xTaskCreate(puedoRecibir, "task4", 100, NULL, 2, NULL);
                    if (xSemaphoreTake(xpuedoRecibir, portMAX_DELAY) == pdTRUE) {
                        //periodo = atoi(USB_getRxBuffer());
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
